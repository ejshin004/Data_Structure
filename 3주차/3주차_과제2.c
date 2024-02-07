#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101

typedef struct {
	int coef;
	int expon;
}polynomial;

polynomial terms[MAX_TERMS];
int avail = 0, An = 0;

void input_poly()
{
	int i = 0, A1 = 0, A2 = 0;
	avail = 0;

	printf("항의 개수 입력: ");
	scanf("%d", &An);

	printf("\n최고차항부터 내림차순으로 입력\n");

	while (i < An)
	{
		printf("A식의 계수: ");
		scanf("%d", &A1);

		if (A1 == 0)
		{
			printf("계수가 0인 항은 저장되지 않으므로 다시 입력하세요.\n\n");
			continue;
		}

		printf("A식의 지수: ");
		scanf("%d", &A2);

		if (A2 < 0)
		{
			printf("0이상의 지수를 입력하세요\n");
			exit(1);
		}

		terms[avail].coef = A1;
		terms[avail].expon = A2;

		avail++;
		i++;
	}
	avail -= 1;
}

int calculation(int x)
{
	int k = 0, result = 0, tmp = 0;

	if (An == 1 && terms[0].expon == 0)
		return terms[0].coef;

	else
	{
		for (int i = An; i > 0; i--)
		{
			tmp = 1;

			for (int j = terms[k].expon; j > 0; j--)
			{
				tmp *= x;
			}

			result += (terms[k++].coef * tmp);
		}
		return result;
	}
}

void print_poly()
{
	printf("\nA(x) = ");

	for (int i = 0; i < avail; i++)
		printf("%dx^%d + ", terms[i].coef, terms[i].expon);

	if (terms[avail].expon == 0)
		printf("%d\n", terms[avail].coef);

	else
		printf("%dx^%d\n", terms[avail].coef, terms[avail].expon);
}

int main(void) {

	int x, num1, num2;

	while (1)
	{
		input_poly();
		print_poly();

		while (1)
		{
			x = 0, num1 = 0;

			printf("x값 입력: ");
			scanf("%d", &x);
			printf("A(%d) = %d\n", x, calculation(x));

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