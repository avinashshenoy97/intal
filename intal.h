//intal.h is an header for the library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

#include <stddef.h>

// intal is an integer of arbitrary length.
// Field s stores a null-terminated string of decimal digits preceded by
// a + or sign indicating positive and negative integers.
// Field n represents the number of decimal digits excluding the sign.
// n is always greater than zero.
// Eg: Zero is represented with s as "+0" and n == 1.
// Eg: 2017 is represented with s as "+2017" and n == 4.
// Eg: -272 is represented with s as "-272" and n == 3.
typedef struct intal {
	char *s; //null terminated string of decimal digits preceded by a +/- sign
	int n; //length of the integer in terms of decimal digits
} intal;

// Creates and returns a pointer to a new intal initialized to zero.
// Initial values of i would be "+0" and n == 1.
intal* create_intal();

// Deletes an intal, especially the memory allocated to it.
// i is a pointer to an intal to be deleted. It also resets *i to null.
void delete_intal(intal** i);

// Reads an intal from str into intal struct.
// str should be a null-terminated string just like s inside intal except that
// a postive integer could start without a + sign.
// str is unmodified.
void read_intal(intal* i, char* str);

// Prints the integer into stdout.
// It's just printf of s in intal (with format specifier %s) except that 
// it doesn't print the sign in case of positive integer.
void print_intal(intal* i);

//Compares 2 numbers' absolute values. Returns 1 if first paramter is greater than second and 2 if vice versa.
//Returns 0 if a is equal to.
//Parameters a and b are not modified.
int compare_intal(intal *a, intal *b);

//checks if number is 0, also removes padding.
//changes i to contain reference of unpadded number.
void check_zero_intal(intal **i);

// Adds two intals a and b, and returns the sum.
// Parameters a and b are not modified. Sum is a new intal.
intal* add_intal(intal* a, intal* b);

// Subtracts intal b from intal a. That is, finds a-b and returns the answer.
// Parameters a and b are not modified. a-b is a new intal.
intal* subtract_intal(intal* a, intal* b);

//Pad's the number with 0s so that it's length, excluding sign, is len.
//Parameters are not changed but contents referred to by a may change.
void pad(intal **a, int len);

//splits given number into two halves and places their references in a1 and a2 and returns the length of each half.
//Parameter a is not modified. a1 and a2 contain the two halves.
int split_intal(intal *a, intal **a1, intal **a2);

//Multiplies a number by a power of ten, p, and returns it. (p >= 1)
//Parameters are not changed.
intal *multiply_intal_powten(intal *a, int p);

// Multiplys two intals a and b, and returns the product.
// Parameters a and b are not modified. Product is a new intal.
intal* multiply_intal(intal* a, intal* b);

//Appends number t to the end of a.
//Parameter t is not modified.
void strapp(intal *a, intal *t);

// Divides intal a from intal b and returns the quotient. 
// That is, finds floor(a/b), which is aka integer division.
// Parameters a and b are not modified. Floor(a/b) is a new intal.
intal* divide_intal(intal* a, intal* b);

// Finds a^b, which a to the power of b and returns the result. 
// The result could be undefined if the intal b is negative.
// Parameters a and b are not modified. The result is a new intal.
intal* pow_intal(intal* a, intal* b);
