//intal.c is a library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

// intal is an integer of arbitrary length. It has two fields; s and n.
// Field s stores a null-terminated string of decimal digits preceded by
// a + or sign indicating positive and negative integers.
// Field n represents the number of decimal digits excluding the sign.
// n is always greater than zero.
// Eg: Zero is represented with s as "+0" and n == 1.
// Eg: 2017 is represented with s as "+2017" and n == 4.
// Eg: -272 is represented with s as "-272" and n == 3.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

// Creates and returns a pointer to a new intal initialized to zero.
// Initial values of i would be "+0" and n == 1.
intal* create_intal(){
	intal* i;

	i = (intal*) malloc(sizeof(intal));
	if(i == NULL) {
		return NULL; //malloc failed
	}

	//alloc 3 chars for a null-terminated string "+0".
	i->s = (char *) malloc(3 * sizeof(char));
	if(i->s == NULL) {
		free(i);
		return NULL; //malloc failed
	}

	strcpy(i->s, "+0"); 
	i->n = 1;

	return i;
}

// Deletes an intal, especially the memory allocated to it.
// i is a pointer to an intal to be deleted. It also resets *i to null.
void delete_intal(intal** i){

	if (i == NULL) {
		return;
	}

	if (*i == NULL) {
		return;
	}

	if( (*i)->s != NULL ) {
		free( (*i)->s );
	}

	free(*i);
	*i = NULL;
	return;
}

// Reads an intal from str into intal struct.
// str should be a null-terminated string just like s inside intal except that
// a postive integer could start without a + sign.
// str is unmodified.
void read_intal(intal* i, char* str){
	int n;

	if(i == NULL) {
		return; //use create_intal before calling read_intal
	}
	if(str == NULL) {
		return; //invalid str
	}

	n = strlen(str);

	if( (str[0] == '+') || (str[0] == '-') ) {
		//it has a sign
	 	i->s = realloc(i->s, n + 1); //one extra char for null termination
	 	strcpy(i->s, str);
	 	i->n = n - 1;
	} else {
		//it doesn't have a sign and hence it's positive
		i->n = n;
		n++; //one extra for the + sign
	 	i->s = realloc(i->s, n + 1); //one extra char for null termination
	 	i->s[0] = '+';
	 	strcpy(i->s + 1, str);
	}
	return;
}

// Prints the integer into stdout.
// It's just printf of s in intal (with format specifier %s) except that 
// it doesn't print the sign in case of positive integer.
void print_intal(intal* i){
	if(i == NULL) {
		return; //no intal to print
	}

	if(i->s != NULL) {
		if(i->s[0] == '+') {
			printf("%s", i->s + 1);
		} else {
			printf("%s", i->s);
		}
	}
	return;
}

//Compares 2 numbers' absolute values. Returns 1 if first paramter is greater than second and 2 if vice versa.
//Returns 0 if a is equal to.
//Parameters a and b are not modified.
int compare_intal(intal *a, intal *b) {
	intal *loca = create_intal(), *locb = create_intal();

	read_intal(loca, a->s);			//make local copies of parameters.
	read_intal(locb, b->s);
	check_zero_intal(&loca);
	check_zero_intal(&locb);


	if(a->n > b->n) {
		delete_intal(&loca);
		delete_intal(&locb);
		return 1;
	}
	else if(a->n < b->n) {
		delete_intal(&loca);
		delete_intal(&locb);
		return 2;
	}

	int i = 0;
	int aind = 0, bind = 0;

	i = 1;
	while(i <= a->n) {
		if(a->s[i] != '0')
			break;

		i++;
	}
	aind = i;


	i = 1;
	while(i <= b->n) {
		if(b->s[i] != '0')
			break;

		i++;
	}
	bind = i;
	

	if(aind < bind)
		return 1;
	else if(bind < aind)
		return 2;
	else {
		for(i = aind ; i <= a->n && i <= b->n ; i++)
			if(a->s[i] - b->s[i])
				break;

		if( (i-1) == a->n && (i-1) != b->n)		//loop terminated because it reached end of a, hence a is smaller than b.
			return 2;
		else if( (i-1) == b->n && (i-1) != a->n )		//loop terminated because it reached end of b, hence b is smaller than a.
			return 1;
		else {
			if(a->s[i] > b->s[i])
				return 1;
			else if(a->s[i] < b->s[i])
				return 2;
			else
				return 0;
		}
	}


	delete_intal(&loca);
	delete_intal(&locb);

	return 0;
}

//checks if number is 0, also removes padding.
//changes i to contain reference of unpadded number.
void check_zero_intal(intal **i) {
	intal *a = *i, *ret = NULL;
	char *s = NULL;
	long j = 1, k = 1;

	for(j = 1 ; j <= a->n ; j++)
		if(a->s[j] != '0')
			break;

	ret = create_intal();
	if(j > a->n) {
		*i = ret;
		return;
	}
	else if(j == 1)
		return;
	

	s = (char *)malloc(sizeof(char) * (a->n - j + 1 + 2));	//+2 for sign and null

	s[0] = a->s[0];				//copy sign.
	for( ; j <= a->n ; j++)
		s[k++] = a->s[j];			//copy number.
	s[k] = 0;			//set terminating null character.

	read_intal(a, s);			//read copy into structure.
								//return it by reference.
	free(s);					//free temporary string.
	delete_intal(&ret);
}

// Adds two intals a and b, and returns the sum.
// Parameters a and b are not modified. Sum is a new intal.
intal* add_intal(intal* a, intal* b){
	intal *ret = create_intal();
	char *str = NULL;
	int s = 0, c = 0;
	long i = 0, j = 0, k = 0;
	char asign = 0, bsign = 0;
	short t = 0;

	if(a->n > b->n)
		ret->n = a->n + 1;			//result can have at most one digit more than the longer number.
	else
		ret->n = b->n + 1;

	if(a->s[0] == b->s[0]) {
		str = (char *)malloc(sizeof(char) * (ret->n + 2));	//one extra for terminating null char and one for sign.
		str[ret->n + 1] = 0;
		str[0] = a->s[0];		//taking care of sign of result.

		i = a->n;			//loop variables. Parsing numbers from their respective 1's place.
		j = b->n;
		k = ret->n;

		while(i > 0 && j > 0) {
			s = a->s[i] - '0' + b->s[j] - '0' + c;
			str[k--] = (s % 10) + '0';
			c = s / 10;

			i--;
			j--;
		}

		for( ; i > 0 ; i--) {
			s = a->s[i] - '0' + c;
			str[k--] = (s % 10) + '0';
			c = s / 10;
		}
		
		for( ; j > 0 ; j--) {
			s = b->s[j] - '0' + c;
			str[k--] = (s % 10) + '0';
			c = s / 10;
		}

		for( ; k > 0 ; k--) {
			str[k] = c + '0';
			c /= 10;
		}
		
		read_intal(ret, str);		//putting answer in returning structure;
		free(str);
	}
	else {
		t = compare_intal(a, b);
		if(t == 0) {
			return ret;
		}
		asign = a->s[0];			//Saving signs.
		bsign = b->s[0];

		a->s[0] = b->s[0] = '+';		//making signs positive.

		delete_intal(&ret);
		ret = subtract_intal(a, b);

		a->s[0] = asign;					//restoring signs.
		b->s[0] = bsign;

		switch(t) {
			case 1 :
				ret->s[0] = a->s[0];
				break;

			case 2 :
				ret->s[0] = b->s[0];
				break;		
		}
	}

	check_zero_intal(&ret);				//unpad 0s.
	return ret;
}

// Subtracts intal b from intal a. That is, finds a-b and returns the answer.
// Parameters a and b are not modified. a-b is a new intal.
intal* subtract_intal(intal* a, intal* b){
	intal *ret = NULL;
	intal *big = NULL, *small = NULL;
	char *str = NULL;
	short t = 0, bo = 0, s = 0;
	long i = 0, j = 0, k = 0;
	char asign = 0, bsign = 0;

	if(a->s[0] == b->s[0]) {
		ret = create_intal();
		t = compare_intal(a, b);

		switch(t) {				//taking care of sign of result, and allocating memory.
			case 0 :
				return ret;

			case 1 :
				str = (char *)malloc(sizeof(char) * (a->n + 2));
				str[a->n + 1] = 0;
				str[0] = a->s[0];
				k = a->n;
				big = a;
				small = b;
				break;

			case 2 :
				str = (char *)malloc(sizeof(char) * (b->n + 2));
				str[b->n + 1] = 0;
				str[0] = (a->s[0] == '+' ? '-' : '+');
				k = b->n;
				big = b;
				small = a;
				break;
		}

		i = big->n;
		j = small->n;

		while(i > 0 && j > 0) {
			s = big->s[i] - small->s[j] - bo;

			if(s < 0) {
				s += 10;
				bo = 1;
			}
			else 
				bo = 0;
			
			str[k--] = s + '0';

			i--;
			j--;
		}

		for( ; i > 0 ; i--) {
			s = big->s[i] - '0' - bo;
			
			if(s < 0) {
				s += 10;
				bo = 1;
			}
			else
				bo = 0;

			str[k--] = s + '0';
		}

		for( ; k > 0 ; k--)
			str[k] = '0';

		read_intal(ret, str);
		free(str);
	}
	else {					//if they have unequal signs, they must be added.
		asign = a->s[0];	//save signs.
		bsign = b->s[0];

		a->s[0] = b->s[0] = '+';	//make both positive.

		ret = add_intal(a, b);		//add the two numbers.

		ret->s[0] = asign;			//result will have same sign as a.

		a->s[0] = asign;			//restore signs.
		b->s[0] = bsign;
	}

	check_zero_intal(&ret);
	return ret;
}

//Pad's the number with 0s so that it's length, excluding sign, is len.
//Parameters are not changed but contents referred to by a may change.
void pad(intal **a, int len) {
	intal *b = *a;

	int j = 0, z = 0, k = 0;
	if(b->n == len)
		return;
	

	z = len - b->n;							//number of zeros
	char *s = (char *)malloc(sizeof(char) * (len + 2));		//space for sign and null char.
	s[0] = b->s[0];						//copying sign.

	for(j = 1 ; j <= z ; j++)		//padding.
		s[j] = '0';

	k = 1;
	for( ; b->s[k] ; k++)			//copying.
		s[j++] = b->s[k];

	s[j] = 0;

	read_intal(b, s);				//reading into original.
	free(s);						//free temporary string.
}

//splits given number into two halves and places their references in a1 and a2 and returns the length of each half.
//Parameter a is not modified. a1 and a2 contain the two halves.
int split_intal(intal *a, intal **a1, intal **a2) {
	int j = 1, k = 1;
	int m = a->n / 2;
	intal *b1 = create_intal(), *b2 = create_intal();
	char *s1 = (char *)malloc(sizeof(char) * (m + 2));
	char *s2 = (char *)malloc(sizeof(char) * (m + 2));

	s1[0] = s2[0] = a->s[0];		//copy sign.

	
	for(j = 1 ; j <= m ; j++)		//copy first half.
		s1[k++] = a->s[j];
	
	k = 1;
	for( ; j <= a->n ; j++)			//copy second half.
		s2[k++] = a->s[j];

	s1[m + 1] = s2[m + 1] = 0;			//set terminating nulls.

	read_intal(b1, s1);			//read into returning structures.
	read_intal(b2, s2);

	*a1 = b1;			//return by referance.
	*a2 = b2;

	free(s1);			//free temp strings.
	free(s2);

	return m;
}

//Multiplies a number by a power of ten, p, and returns it. (p >= 1)
//Parameters are not changed.
intal *multiply_intal_powten(intal *a, int p) {
	intal *ret = create_intal();
	char *s = (char *)malloc(sizeof(char) * (a->n + 2 + p));	//number + 0s + sign + null char.

	int i = 0, j = 0;
	for(i = 0 ; a->s[i] ; i++)		//copy entire number with sign.
		s[i] = a->s[i];

	for(j = 0 ; j < p ; j++)
		s[i++] = '0';

	s[a->n + p + 1] = 0;			//set null char.
	read_intal(ret, s);				//read into returning structure.
	free(s);						//free temporary string.

	return ret;
}

// Multiplys two intals a and b, and returns the product.
// Parameters a and b are not modified. Product is a new intal.
intal* multiply_intal(intal* a, intal* b){
	intal *ret = NULL;
	int p = 0, m = 0;
	char *s = NULL;

	intal *a1 = NULL, *a2 = NULL;
	intal *b1 = NULL, *b2 = NULL;
	intal *p1 = NULL, *p2 = NULL, *p3 = NULL;
	intal *t1 = NULL, *t2 = NULL, *t3 = NULL;

	check_zero_intal(&a);
	check_zero_intal(&b);

	if(a->n == 1 && b->n == 1) {
		p = (a->s[1] - '0') * (b->s[1] - '0');
		s = (char *)malloc(sizeof(char) * 4);		//2 digits + null + sign.

		s[0] = (a->s[0] == b->s[0] ? '+' : '-');	//set sign.
		s[3] = 0;									//set terminating null char.

		s[2] = (p % 10) + '0';
		p = p / 10;
		s[1] = (p % 10) + '0';

		ret = create_intal();
		read_intal(ret, s);
		free(s);
		check_zero_intal(&ret);

		return ret;
	}

	(a->n) > (b->n) ? pad(&b, a->n) : pad(&a, b->n) ;	//make their lengths equal.


	if(a->n % 2) {			//make their lengths even.
		pad(&b, b->n + 1);
		pad(&a, a->n + 1) ;
	}


	m = split_intal(a, &a1, &a2);
	split_intal(b, &b1, &b2);


	p1 = multiply_intal(a1, b1);		//p1 = a1 * b1
	p2 = multiply_intal(a2, b2);		//p2 = a2 * b2


	t1 = add_intal(a1, a2);				//t1 = a1 + a2
	t2 = add_intal(b1, b2);				//t2 = b1 + b2

	p3 = multiply_intal(t1, t2);		//p3 = (a1 + a2) * (b1 + b2)

	
	//delete_intal(&t1);
	t1 = multiply_intal_powten(p1, a->n);	//t1 = p1 * 10^n
	

	//delete_intal(&t2);
	t2 = subtract_intal(p3, p1);		//t2 = p3 - p1	
	t3 = subtract_intal(t2, p2);		//t3 = p3 - p1 - p2
	
	//delete_intal(&t2);
	t2 = add_intal(t1, p2);			//t2 = p1*10^n + p2

	//delete_intal(&t1);
	t1 = multiply_intal_powten(t3, m);		//t1 = (p3-p1-p2)*10^m
	

	ret = add_intal(t2, t1);				//ret = p1*10^n + p2 + (p3-p1-p2)*10^m


	delete_intal(&p1);
	delete_intal(&p2);
	delete_intal(&p3);
	delete_intal(&t1);
	delete_intal(&t2);
	delete_intal(&t3);
	delete_intal(&a1);
	delete_intal(&b1);
	delete_intal(&a2);
	delete_intal(&b2);

	check_zero_intal(&ret);				//remove padding.
	check_zero_intal(&a);
	check_zero_intal(&b);
	
	return ret;
}

//Appends number t to the end of a.
//Parameter t is not modified.
void strapp(intal *a, intal *t) {
	a->s = (char *)realloc(a->s, (a->n + 2 + t->n));

	int i = 0, j = 1;
	for(i = a->n ; t->s[j] ; i++)
		a->s[i] = t->s[j++];

	a->s[i] = 0;
	a->n = i;
}

// Divides intal a from intal b and returns the quotient. 
// That is, finds floor(a/b), which is aka integer division.
// Parameters a and b are not modified. Floor(a/b) is a new intal.
intal* divide_intal(intal* a, intal* b){
	check_zero_intal(&a);
	check_zero_intal(&b);
	
	intal *tempa = create_intal(), *tempb = create_intal();
	short tempc = 0;
	intal *ret = create_intal(), *adder = create_intal();
	intal *temp = NULL, *t = NULL, *mulc = create_intal();
	read_intal(adder, "1");


	if(compare_intal(b, ret) == 0) {
		printf("Division by 0. Invalid.\n");
		return NULL;
	}

	if(compare_intal(b, adder) == 0) {
		read_intal(ret, a->s);
		return ret;
	}


	read_intal(tempa, a->s);
	read_intal(tempb, b->s);

	check_zero_intal(&tempa);
	check_zero_intal(&tempb);

	if(a->s[0] != b->s[0])
		ret->s[0] = '-';
	else
		ret->s[0] = '+';


	while(compare_intal(tempa, tempb) < 2) {
		temp = multiply_intal_powten(tempb, 1);
		delete_intal(&tempb);
		tempb = temp;

		temp = add_intal(mulc, adder);
		delete_intal(&mulc);
		mulc = temp;
	}

	tempb->s[tempb->n] = 0;
	(tempb->n)--;


	temp = subtract_intal(mulc, adder);
	delete_intal(&mulc);
	mulc = temp;


	while(1) {
		t = create_intal();

		while(compare_intal(tempa, tempb) < 2) {
			temp = subtract_intal(tempa, tempb);
			delete_intal(&tempa);
			tempa = temp;

			temp = add_intal(t, adder);
			delete_intal(&t);
			t = temp;
		}

		strapp(ret, t);


		tempc = compare_intal(b, tempb);

		if(tempc == 0 || tempc == 2) {
			tempb->s[tempb->n] = 0;
			(tempb->n)--;

			temp = subtract_intal(mulc, adder);
			delete_intal(&mulc);
			mulc = temp;
		}

		if(compare_intal(b, tempb) == 1)
			break;

		delete_intal(&t);

	}

	delete_intal(&adder);
	delete_intal(&tempa);
	delete_intal(&tempb);
	delete_intal(&mulc);


	return ret;
}

// Finds a^b, which a to the power of b and returns the result. 
// The result could be undefined if the intal b is negative.
// Parameters a and b are not modified. The result is a new intal.
intal* pow_intal(intal* a, intal* b) {
	if(b->s[0] == '-') {
		printf("Negative powers not supported.\n");
		return NULL;
	}

	intal *ret = NULL;
	intal *z = create_intal();			//zero.
	intal *singular = create_intal();	
	read_intal(singular, "1");			//one.

	if(compare_intal(b, z) == 0) {		//if b = 0, return 1		
		ret = singular;
		delete_intal(&z);
		return ret;
	}

	ret = create_intal();			//copies to work with.
	read_intal(ret, a->s);
	intal *tempb = create_intal();
	read_intal(tempb, b->s);
	intal *temp = NULL;

	temp = subtract_intal(tempb, singular);		//decrease b by 1 as a is raised to power 1.
	delete_intal(&tempb);
	tempb = temp;

	while(compare_intal(tempb, z) != 0) {
		temp = multiply_intal(ret, a);
		delete_intal(&ret);
		ret = temp;

		temp = subtract_intal(tempb, singular);		//decrease b by 1.
		delete_intal(&tempb);
		tempb = temp;
	}

	delete_intal(&z);
	delete_intal(&singular);
	return ret;
}
