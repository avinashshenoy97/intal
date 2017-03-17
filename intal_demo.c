//Demo program for the "intal" library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

#include <stdio.h>
#include "intal.h"

int main() {
	intal* i1 = create_intal();
	intal* i2 = create_intal();
	intal* i3 = create_intal();
	intal* i4 = create_intal();

	char s1[20], s2[20], s3[20], s4[20];

	gets(s1);
	gets(s2);
	gets(s3);
	gets(s4);

	read_intal(i1, s1);
	read_intal(i2, s2);
	read_intal(i3, s3);
	read_intal(i4, s4);

	printf("i1 = ");
	print_intal(i1);
	printf("\n");

	printf("i2 = ");
	print_intal(i2);
	printf("\n");
	
	printf("i3 = ");
	print_intal(i3);
	printf("\n");
	
	printf("i4 = ");
	print_intal(i4);
	printf("\n");

	intal *i5 = add_intal(i2, i3, 0);
	print_intal(i5);
	printf("\n");

	printf("i1 = ");
	print_intal(i1);
	printf("\n");

	printf("i2 = ");
	print_intal(i2);
	printf("\n");
	
	printf("i3 = ");
	print_intal(i3);
	printf("\n");
	
	printf("i4 = ");
	print_intal(i4);
	printf("\n");

	delete_intal(&i5);
	i5 = subtract_intal(i2, i3, 0);
	print_intal(i5);
	printf("\n");

	printf("i1 = ");
	print_intal(i1);
	printf("\n");

	printf("i2 = ");
	print_intal(i2);
	printf("\n");
	
	printf("i3 = ");
	print_intal(i3);
	printf("\n");
	
	printf("i4 = ");
	print_intal(i4);
	printf("\n");

	delete_intal(&i1);
	delete_intal(&i2);
	delete_intal(&i3);
	delete_intal(&i4);

	return 0;
}
