#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef char element;
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

int main(void) {

	char str[MAX_STACK_SIZE];

	printf("문자열을 입력하시오. : ");
	scanf_s("%s", str, sizeof(str));

	StackType s1, s2;
	init_stack(&s1);
	init_stack(&s2);
	int i = 0, count = 0;

	while (str[i] != 0)
	{
		count = 1;
		char ch = str[i++];

		while (ch == str[i] || ch + ('A' - 'a') == str[i] || ch - ('A' - 'a') == str[i])
		{
			count++;
			i++;
		}

		push(&s1, count + '0');

		if ('a' <= ch && ch <= 'z')
			push(&s1, ch);
		else
			push(&s1, ch - ('A' - 'a'));
	}

	while (!is_empty(&s1))
	{
		push(&s2, peek(&s1));
		pop(&s1);
	}

	printf("압축된 문자열 : ");
	while (!is_empty(&s2))
	{
		printf("%c", pop(&s2));
	}
	return 0;
}