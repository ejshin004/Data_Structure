#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int function1(int m, int n);
int function2(int m, int n);

int main(void) {
	int m = 0;
	int n = 0;

	printf("시작 값 입력: ");
	scanf("%d", &m);

	printf("끝 값 입력: ");
	scanf("%d", &n);

	printf("\n < 과제 1-1 > \n");
	printf("%d부터 %d까지의 합: %d\n\n", m, n, function1(m, n));

	printf("\n < 과제 1-2 > \n");
	printf("%d부터 %d까지의 합: %d\n", m, n, function2(m, n));

	return 0;
}

int function1(int m, int n)
{
	int sum = 0;

	for (int i = m; i <= n; i++)
	{
		sum += i;
	}

	return sum;
}

int function2(int m, int n)
{
	if (m == n) return m;
	else return(m + function2(m + 1, n));
}