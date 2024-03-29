#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType *s)
{
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType *s)
{
	return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입함수
void push(StackType *s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

// 삭제함수
element pop(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

// 피크함수
element peek(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 

int eval(char exp[])
{
	int op1, op2, value, i = 0, cnt = 0;
	int len = strlen(exp);
	char ch;
	StackType s;

	init_stack(&s);
	for (i = 0; i < len; i++)
	{
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%' && ch != '^' && ch != '>' && ch != '<')
		{
			value = ch - '0';
			push(&s, value); ++cnt;
			printf("push %d\n", peek(&s));
		}
		else
		{
			op2 = pop(&s); printf("pop %d\n", op2); --cnt;
			op1 = pop(&s); printf("pop %d\n", op1); --cnt;
			switch (ch) {
			case '+':
				push(&s, op1 + op2); ++cnt;  break;
			case '-':
				push(&s, op1 - op2); ++cnt;  break;
			case '*':
				push(&s, op1 * op2); ++cnt;  break;
			case '/':
				push(&s, op1 / op2); ++cnt;  break;
			case '%':
				push(&s, op1 % op2); ++cnt;  break;
			case '^':
				push(&s, (int)pow(op1, op2)); ++cnt; break;
			case '>':
				push(&s, op1 > op2);  ++cnt;  break;
			case '<':
				push(&s, op1 < op2); ++cnt;  break;
			}
			printf("%d %c %d 계산 결과 push %d\n", op1, ch, op2, peek(&s));
		}

	}
	if (cnt != 1)
		return -1;

	return pop(&s);
}

/*
	712%+15*-    결과: 3
	4223^^+3-    결과: 257
	25+1-41*3^>  결과: 0

	입력오류
	2323+   연산자 수 부족
	23+++   피연산자 수 부족
	2+3     중위표기
*/

int main(void)
{
	int result = 0, sel = 0;
	char postfix[MAX_STACK_SIZE];

	while (1)
	{
		printf("후위표기 입력: ");  scanf("%s", postfix);

		result = eval(postfix);
		if (result == -1)
			printf("피연산자 수 > 연산자 수");
		else
			printf("연산결과 값은 %d\n", result);

		printf("\n1.계속  2.종료: "); scanf("%d", &sel);
		if (sel != 1)
			break;
	}

	return 0;
}