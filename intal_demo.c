//Demo program for the "intal" library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

#include <stdio.h>
#include <stdlib.h>
#include "intal.h"

int main() {
	intal* i1 = create_intal();
	intal* i2 = create_intal();
	intal *i5 = NULL;

	char *s = (char *)malloc(sizeof(char) * 1000000);
	scanf("%s", s);
	read_intal(i1, s);
	scanf("%s", s);
	read_intal(i2, s);
	free(s);

	check_zero_intal(&i1);			//removing preceding 0s from numbers.
	check_zero_intal(&i2);

	printf("i1 = ");
	print_intal(i1);
	printf("\n");

	printf("i2 = ");
	print_intal(i2);
	printf("\n");
	
	printf("Add : ");
	i5 = add_intal(i1, i2);
	print_intal(i5);
	printf("\n");

	delete_intal(&i5);
	printf("Subtract : ");
	i5 = subtract_intal(i1, i2);
	print_intal(i5);
	printf("\n");

	delete_intal(&i5);
	printf("Multiply : ");
	i5 = multiply_intal(i1, i2);
	print_intal(i5);
	printf("\n");

	delete_intal(&i5);
	printf("Divide : ");
	i5 = divide_intal(i1, i2);
	print_intal(i5);
	printf("\n");

	delete_intal(&i5);
	printf("Power : ");
	i5 = pow_intal(i1, i2);
	print_intal(i5);
	printf("\n");

	delete_intal(&i1);
	delete_intal(&i2);
	delete_intal(&i5);
	

	return 0;
}
