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
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackType s;

	init_stack(&s);
	for (i = 0; i < len; i++)
	{
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%' && ch != '^' && ch != '>' && ch != '<' && ch != '&' && ch != '|')
		{
			value = ch - '0';
			push(&s, value);
			printf("push %d\n", peek(&s));
		}
		else
		{
			op2 = pop(&s); printf("pop %d\n", op2);
			op1 = pop(&s); printf("pop %d\n", op1);
			switch (ch) {
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			case '%': push(&s, op1 % op2); break;
			case '^': push(&s, (int)pow(op1, op2)); break;
			case '<': push(&s, op1 < op2); break;
			case '>': push(&s, op1 > op2); break;
			case '&': push(&s, op1 && op2); break;
			case '|': push(&s, op1 || op2); break;
			}
			printf("%d %c %d 계산 결과 push %d\n", op1, ch, op2, peek(&s));
		}
	}
	return pop(&s);
}

int num = 5;

int prec(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '&': return 1;
	case '|': return 2;
	case '>': case '<': return 3;
	case '+': case '-': return 4;
	case '*': case '/': case '%': return 5;
	case '^': return ++num;
	}
	return -1;
}

void infix_to_postfix(char *pf, char exp[])
{
	int i = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType s;

	init_stack(&s);

	for (i = 0; i < len; i++)
	{
		ch = exp[i];
		switch (ch) {
		case '+': case '-': case '*': case '/': case '%': case '^': case '<': case '>': case '&': case '|':
			//스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
			{
				if (ch == '^' && (prec(ch) < prec(peek(&s))))
					break;
				printf("pop %c\n", peek(&s));
				*pf++ = pop(&s);
			}
			push(&s, ch);
			printf("push %c\n", peek(&s));
			break;
		case '(':
			push(&s, ch);
			printf("push %c\n", peek(&s));
			break;
		case ')':
			printf("pop %c\n", peek(&s));
			top_op = pop(&s);
			//왼쪽 괄호를 만날 때까지 출력
			while (top_op != '(')
			{
				printf("pop %c\n", peek(&s));
				*pf++ = top_op;
				top_op = pop(&s);
			}
			break;
		default: //피연산자
			*pf++ = ch;
			break;
		}
	}
	while (!is_empty(&s)) //스택에 저장된 연산자들 출력
	{
		printf("pop %c\n", peek(&s));
		*pf++ = pop(&s);
	}
	*pf = '\0';
}

printf("test (((( } ")
/* ((( }} */
// (((]]]

int main(void)
{
	int result = 0, sel = 0;
	char infix[MAX_STACK_SIZE];
	char * postfix = (char *)malloc(sizeof(char) * 100);

	while (1)
	{
		printf("중위표기수식: ");  scanf("%s", infix);

		infix_to_postfix(postfix, infix);
		printf("후위표기수식: %s\n\n", postfix);

		result = eval(postfix);
		printf("결과값: %d\n", result);

		printf("\n1.계속  2.종료: "); scanf("%d", &sel);
		if (sel != 1)
			break;
	}

	free(postfix);
	return 0;
}