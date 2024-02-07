#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_DEGREE 101

typedef struct {
	int degree;
	int coef[MAX_DEGREE];
}polynomial;

polynomial input_poly()
{
	polynomial p;

	while (1)
	{
		printf("다항식의 최고차항: ");
		scanf("%d", &p.degree);
		if (p.degree >= 0)
			break;
		else
			printf("0이상의 수를 다시 입력하세요.\n\n");
	}

	for (int i = 0; i <= p.degree; i++)
	{
		printf("x^%d의 계수: ", p.degree - i);
		scanf("%d", &p.coef[i]);
	}

	return p;
}

void print_poly(polynomial p)
{
	printf("\nA(x) = ");
	for (int i = p.degree; i > 0; i--)
	{
		if (p.coef[p.degree - i] != 0)
			printf("%dx^%d + ", p.coef[p.degree - i], i);
	}

	printf("%d\n", p.coef[p.degree]);
}

int calculation(polynomial p, int x)
{
	int k = 0, result = 0, tmp = 0;

	if (p.degree == 0)
		return p.coef[0];

	else
	{
		for (int i = p.degree; i >= 0; i--)
		{
			tmp = 1;

			for (int j = p.degree; j > p.degree - i; j--)
			{
				tmp *= x;
			}

			result += (p.coef[k++] * tmp);
		}
		return result;
	}
}

int main(void) {

	polynomial a;
	int x, num1, num2;

	while (1)
	{
		num2 = 0;
		a = input_poly();
		print_poly(a);

		while (1)
		{
			x = 0, num1 = 0;

			printf("x값: ");
			scanf("%d", &x);

			printf("A(%d) = %d\n", x, calculation(a, x));

			printf("\n다른 x값을 대입하려면 아무 숫자(0 제외)를, 그만하려면 0을 입력하세요: ");
			scanf("%d", &num1);

			if (num1 == 0)
				break;
		}

		printf("\n다른 다항식을 입력하려면 아무 숫자(0 제외)를, 그만하려면 0을 입력하세요: ");
		scanf("%d", &num2);

		if (num2 == 0)
			break;
	}
	return 0;
}