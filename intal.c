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
	for(i = a->n ; i < len-1 ; i++)
		a->s[i] = '0';				//pad 0s

	a->s[len] = 0;	//null termination
	a->n = len;
	
	*a_p = a;		//assign new padded intal back to original
}

// Adds two intals a and b, and returns the sum.
// Parameters a and b are not modified. Sum is a new intal.
intal* add_intal(intal* a, intal* b){
	printf("before pad %d %d\n", a->n, b->n);
	intal *ret = NULL; //to return

	if(a->sign != b->sign) {		//forward the call to subtract if their signs are unequal
		ret = subtract_intal(a, b);
		return ret;
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
	
	ret->s = (char *)malloc(sizeof(char) * (ret->n + 1));	//one extra for null terminated string.
	if(ret->s == NULL) errmsg(5);


	for(i = 0 ; i < ret->n - 1 ; i++) {
		s = *(a->s + i) - '0' + *(b->s + i) - '0' + c;
		*(ret->s + i) = (s % 10) + '0';
		c = s / 10;
	}

	if(c)
		*(ret->s + i) = c + '0';
	else {
		ret->n -= 1;
		ret->s = (char *)realloc(ret->s , ret->n + 1);	//decrease length by 1 as the sum has same no of digits as operands
	}

	return ret;
	return NULL;
}

// Subtracts intal b from intal a. That is, finds a-b and returns the answer.
// Parameters a and b are not modified. a-b is a new intal.
intal* subtract_intal(intal* a, intal* b){
	//TODO it's a stub function. Fill in the details and delete this comment.
	return NULL;
}

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
