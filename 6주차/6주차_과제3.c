#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

int palindrome(char str[])
{
	StackType s;
	init_stack(&s);
	int i = 0;
	char ch, chs;
	int len = strlen(str);

	for (i = 0; i < len; i++)
	{
		ch = str[i];

		if (ispunct(ch) != 0 || ch == ' ')
			continue;

		ch = tolower(ch);
		push(&s, ch);
	}

	for (i = 0; i < len; i++)
	{
		ch = str[i];

		if (ispunct(ch) != 0 || ch == ' ')
			continue;

		ch = tolower(ch);
		chs = pop(&s);

		if (ch != chs)
			return 0;
	}

	return 1;
}

int main(void) {

	int check = 0;
	char str[MAX_STACK_SIZE];

	printf("문자열을 입력하시오. : ");
	scanf("%[^\n]s", str);

	check = palindrome(str);

	if (check == 1)
		printf("%s은(는) 회문입니다.\n", str);
	else
		printf("%s은(는) 회문이 아닙니다.\n", str);

	return 0;
}