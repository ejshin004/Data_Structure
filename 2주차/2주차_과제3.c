#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct complex {
	double real;
	double imag;
}Complex;

Complex add(Complex * arr)
{
	Complex result = { 0.0, 0.0 };

	for (int i = 0; i < 10; i++)
	{
		result.real += arr[i].real;
		result.imag += arr[i].imag;
	}
	return result;
}

int main(void) {

	Complex arr[10];

	printf("< 과제 3 > \n");
	printf("복소수 10개 입력(실수부 허수부)\n");

	for (int i = 0; i < 10; i++)
	{
		printf("(%d) ", i + 1);
		scanf("%lf %lf", &arr[i].real, &arr[i].imag);
	}

	printf("\n덧셈 결과: %g + %gi\n", add(arr).real, add(arr).imag);
	return 0;
}