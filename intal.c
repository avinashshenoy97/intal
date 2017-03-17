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

#define errmsg(a) printf("Memory failure : %d\n", a);

// Creates and returns a pointer to a new intal initialized to zero.
// Initial values of i would be "+0" and n == 1.
intal* create_intal(){
	intal* i;

	i = (intal*) malloc(sizeof(intal));
	if(i == NULL) {
		errmsg(1);
		return NULL; //malloc failed
	}

	//alloc 2 chars for a null-terminated string "0".
	i->s = (char *) malloc(2 * sizeof(char));
	if(i->s == NULL) {
		errmsg(2);
		free(i);
		return NULL; //malloc failed
	}

	strcpy(i->s, "0");
	i->sign = '+'; //sets the sign to '+'.
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
	int n, j;
	char *s;

	if(i == NULL) {
		return; //use create_intal before calling read_intal
	}
	if(str == NULL) {
		return; //invalid str
	}

	n = strlen(str);
	i->s = realloc(i->s, n + 1); //one extra char for null termination
	i->n = n;

	if( (str[0] == '+') || (str[0] == '-') ) {
		//it has a sign
		i->sign = str[0];
		s = str + 1;
		(i->n)--;
		n--;
	} else {
		//it doesn't have a sign and hence it's positive
	 	i->sign = '+';
	 	s = str;
	}

	for(j = 0 ; j < n ; j++)
	 	i->s[j] = s[n-j-1];		//copy in reverse.
	 i->s[n] = 0;				//null terminating character.
	return;
}

// Prints the integer into stdout.
// It's just printf of s in intal (with format specifier %s) except that 
// it doesn't print the sign in case of positive integer.
void print_intal(intal* i){
	int j;
	if(i == NULL) {
		return; //no intal to print
	}

	if(i->s != NULL) {
		if(i->sign != '+') putchar(i->sign);

		for(j = i->n - 1 ; j >= 0 ; j--)
			printf("%c",i->s[j]);
	}
	return;
}

// Pads the intal's string with preceding 0s.
//Parameter a_p is modified and nothing is returned.
void pad(intal **a_p, int len) {
	intal *a = *a_p;
	
	a->s = (char *)realloc(a->s, len + 1);	//reallocate for padded 0s and null character.
	
	int i;
	for(i = a->n ; i < len ; i++)
		a->s[i] = '0';				//pad 0s

	a->s[len] = 0;	//null termination
	a->n = len;
	
	*a_p = a;		//assign new padded intal back to original
}

// Checks if the number is 0 and resets the string to a null terminated "+0".
//Parameter is the intal and is modified appropriately.
void checkZero(intal **a) {
	int i;
	intal *b = *a;
	for(i = b->n - 1 ; i >= 0 ; i--) 	//parse number till first non-zero character/digit.
		if(*(b->s + i) != '0')
			break;

	b->n = i + 1;
	b->s[b->n] = 0;			//insert terminating null character.

	*a = b;				//assign back into original.
}

//Creates a copy of the intal i.
//Paramter copy is not modified.
intal *copy(intal *i) {
	intal *ret = create_intal();
	char *s = (char *)malloc(sizeof(char) * (i->n + 1));
	if(s == NULL) errmsg(8);

	int j;
	for(j = 0 ; j < i->n ; j++)
		s[j] = i->s[j];

	ret->n = i->n;
	free(ret->s);
	ret->s = s;

	return ret;
}

// Adds two intals a and b, and returns the sum.
// Parameters a and b are not modified. Sum is a new intal.
// e = 0 implies add_intal was called for it's actual purpose. e = 1 implies it was called from subtract_intal due to unequal signs.
intal* add_intal(intal* a, intal* b, short e){
	intal *ret = create_intal(); //to return
	char *str = NULL;

	if(!e) {
		if(a->sign != b->sign) {		//forward the call to subtract if their signs are unequal
			ret = subtract_intal(a, b, 1);
			return ret;
		}
	}

	int i, s, c = 0;
	ret = (intal *)malloc(sizeof(intal));
	if(ret == NULL) errmsg(4);
	

	if(a->n > b->n) {
		ret->n = a->n + 1;
		pad(&b, a->n);
	}
	else{
		ret->n = b->n + 1;
		pad(&a, b->n);
	}
	
	str = (char *)malloc(sizeof(char) * (ret->n + 1));	//one extra for null terminated string.
	if(str == NULL) errmsg(5);


	for(i = 0 ; i < ret->n - 1 ; i++) {
		s = *(a->s + i) - '0' + *(b->s + i) - '0' + c;
		*(str + i) = (s % 10) + '0';
		c = s / 10;
	}

	if(c)
		*(str + i) = c + '0';
	else {
		ret->n -= 1;
		str = (char *)realloc(str , ret->n + 1);	//decrease length by 1 as the sum has same no of digits as operands
	}

	ret->sign = a->sign;
	free(ret->s);
	ret->s = str;

	checkZero(&a);			//unpad parameters
	checkZero(&b);

	return ret;
}

// Subtracts intal b from intal a. That is, finds a-b and returns the answer.
// Parameters a and b are not modified. a_ - b_ is a new intal. Parameter e is to specify entry.
// e = 0 implies subtract_intal was called for it's actual purpose. e = 1 implies it was called from add_intal due to unequal signs.
intal* subtract_intal(intal* a_, intal* b_, short e){
	int i, s, j;
	intal *a = NULL, *b = NULL, *ret = NULL;
	char *str = NULL;

	if(!e) {
		if(a_->sign != b_->sign) {
			ret = add_intal(a_, b_, 1);
			//sign will be same as a_ because pos - neg = pos and neg - pos = neg.
			return ret;
		}
	}

	ret = create_intal();
	if(ret == NULL) errmsg(6);

	if(a_->n > b_->n) {
		ret->n = a_->n;
		pad(&b_, a_->n);
	}
	else {
		ret->n = b_->n;
		pad(&a_, b_->n);
	}
	
	str = (char *)malloc(sizeof(char) * ret->n);
	if(str == NULL) errmsg(7);

	int a_ind = 0, b_ind = 0;	//indexes of first non-zero digit in a and b

	for(i = a_->n - 1 ; i >= 0 ; i--)
		if(a_->s[i] != '0') {
			a_ind = i;
			break;
		}

	for(i = b_->n - 1 ; i >= 0 ; i--)
		if(b_->s[i] != '0') {
			b_ind = i;
			break;
		}

	if(a_ind > b_ind) {
		a = a_;
		b = b_;
		ret->sign = a->sign;		//since a_ > b_ , result will have same sign as a_
	}
	else if(a_ind < b_ind) {
		a = b_;
		b = a_;
		ret->sign = (a_->sign == '+' ? '-' : '+');		//since a_ < b_ , result will have opposite sign of a_
	}
	else {
		for(i = a_ind ; i >= 0 ; i--)	//if both have first non-zero digit at same index
			if(a_->s[i] - b_->s[i])		//find first pair of digits such that their difference is non-zero, i.e, they are unequal
				break;

		if(i == -1) {					//if the numbers are the same, return +0
			delete_intal(&ret);
			ret = create_intal();
			return ret;
		}
		else if( a_->s[i] > b_->s[i] ) {
			a = a_;
			b = b_;
			ret->sign = a->sign;		//since a_ > b_ , result will have same sign as a_
		}
		else if( a_->s[i] < b_->s[i] ) {
			a = b_;
			b = a_;
			ret->sign = (a_->sign == '+' ? '-' : '+');		//since a_ < b_ , result will have opposite sign of a_
		}
	}

	a = copy(a);		//as a will have to change in certain cases where carry is required


	for(i = 0 ; i < ret->n ; i++) {
		s = *(a->s + i) - *(b->s + i);

		if(s < 0) {
			s += 10;
			j = i + 1;

			while(*(a->s + j) == '0')
				j++;

			*(a->s + j) -= 1;
			--j;

			while(j > i) {
				*(a->s + j) = '9';
				j--;
			}
		}

		str[i] = s + '0';
	}

	str[ret->n] = 0;
	free(ret->s);
	ret->s = str;
	checkZero(&ret);

	checkZero(&a_);			//unpad parameters
	checkZero(&b_);
	delete_intal(&a);		//delete copy of a


	return ret;
}

//multiplies the intal a by 10 to the power of p.
//Parameters a and p are not modified.
/*intal *multiply_power_ten(intal *a, int p) {
	num *n = (num *)malloc(sizeof(num));
	if(n == NULL) errmsg("multen", 1);
	n->len = a->len + p;
	n->n = (int *)malloc(sizeof(int) * n->len);
	if(n->n == NULL) errmsg("multen", 2);

	int i, j = 0;
	for(i = 0 ; i < p ; i++)
		*(n->n + i) = 0;
	for( ; i < n->len ; i++)
		*(n->n + i) = *(a->n + j++);

	checkZero(&n);

	return n;
}*/

// Multiplys two intals a and b, and returns the product.
// Parameters a and b are not modified. Product is a new intal.
intal* multiply_intal(intal* a, intal* b){
	//TODO it's a stub function. Fill in the details and delete this comment.
	return NULL;
}

// Divides intal a from intal b and returns the quotient. 
// That is, finds floor(a/b), which is aka integer division.
// Parameters a and b are not modified. Floor(a/b) is a new intal.
intal* divide_intal(intal* a, intal* b){
	//TODO it's a stub function. Fill in the details and delete this comment.
	return NULL;
}

// Finds a^b, which a to the power of b and returns the result. 
// The result could be undefined if the intal b is negative.
// Parameters a and b are not modified. The result is a new intal.
intal* pow_intal(intal* a, intal* b) {
	//TODO it's a stub function. Fill in the details and delete this comment.
	return NULL;
}
