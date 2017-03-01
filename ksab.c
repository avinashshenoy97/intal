#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int *pad(int *a) {
	a[0]++;
	pa[0] = a[0];
	int *pa = (int *)malloc(sizeof(int) * a[0]);
	int i = 1;
	pa[i++] = 0;
	
	for(; i < a[0] ; i++)
		pa[i] = a[i-1];
		
	free(a);
	return pa;
}	

int *sum_arr(int *a, int *b) {
	int *s = (int *)malloc(sizeof(int) * (a[0]+2));
	s[0] = a[0] + 1;
	int j = a[0];
	int c = 0;
	for(; j > 0 ; j--) {
		s[j+1] = a[j] + b[j] + c;
		c = s[j+1] / 10;
		s[j+1] = s[j+1] % 10;
	}
	
	if(s[1] == 0) { {
		for(j=1 ; j < a[0]+2 ; j++)
			s[j] = s[j+1];
		s[0]--;
	}
	
	
	return s;
}

int *sub_arr(int *a, int *b) {
	int *diff = (int *)malloc(sizeof(int) * (a[0]+1));
	int i = a[0];
	
	for(; i > 0 ; i--) {
		if(a[i] < b[i]) {
			a[i-1]--;
			a[i] += 10;
		}
		
		diff[i] = a[i] - b[i];
	}
	
	int n = 0;
	i = 1;
	while(diff[i++] == 0)
		n++;

	if(n) {
		for(i = 1 ; i <= a[0] ; i++)
			diff[i] = diff[i+n];
		diff[0] = a[0] - n;
	}		
	
	return diff;
}
	
int *mul_ten(int *a, int p) {
	int *s = (int *)malloc(sizeof(int) * (a[0]+p));
	int i, j = 0;
	for(i = 0 ; i <= a[0] ; i++)
		s[i] = a[i];
		
	for(j = 0 ; j < p ; j++, i++)
		s[i] = 0;
		
	free(a);
	return s;
}

int *karatsuba(int *a, int *b) {
	printf("karatsuba\n");
	if(a[0] == 1) {
		int *s = (int *)malloc(sizeof(int) * 3);
		s[2] = a[1] * b[1];
		s[1] = s[2] % 10;
		if(s[1])
			s[2] /= 10;
		else
			s[1] = s[2];

		//free(a);
		//free(b);
		return s;
	}
		
	if(a[0] % 2) {
		a = pad(a);
		b = pad(b);
	}
	
	int m = a[0] / 2;
	
	int *a1, *a2, *b1, *b2;
	a1 = (int *)malloc(sizeof(int) * (m+1));
	a1[0] = m;
	int i;
	for(i = 0 ; i < m ; i++)
		a1[i+1] = a[i+1];
	a2 = (int *)malloc(sizeof(int) * (m+1));
	a2[0] = m;
	for(i = 1 ; i < m ; i++)
		a2[i] = a[i+m];
		
	b1 = (int *)malloc(sizeof(int) * (m+1));
	b1[0] = m;
	int i;
	for(i = 0 ; i < m ; i++)
		b1[i+1] = b[i+1];
	b2 = (int *)malloc(sizeof(int) * (m+1));
	b2[0] = m;
	for(i = 1 ; i < m ; i++)
		b2[i] = b[i+m];
		
	
	int *p1, *p2, *p3;
	p1 = karatsuba(a1, b1, m);
	p2 = karatsuba(a2, b2, m);
	p3 = karatsuba(sum_arr(a1, a2), sum_arr(b1, b2));
	
	//free(a);
	//free(b);
	
	return (sum_arr(sum_arr(mul_ten(p1, 2*m - 3, n), mul_ten(sub_arr(sub_arr(p3, p1, m), p2, m), 2*m - 1, m), m+n), p2, n+m));	
}

int main(void) {
	int n = 0, i = 1;
	char c;
	int a[1000], b[1000];
	
	while((c = getchar()) != 10) {
		a[i++] = c - '0';
		n++;
	}
	
	a[0] = n;
	
	i = 1;
	while((c = getchar()) != 10)
		b[i++] = c - '0';
		
	b[0] = n;
		
	
	int *p = karatsuba(a, b);
	for(i = 1 ; i < p[0] ; i++)
		printf("%d", p[i]);
	
	return 0;
}
