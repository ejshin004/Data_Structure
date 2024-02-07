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

int check_matching(const char *in)
{
	StackType s1;
	StackType s2;
	char ch, open_ch;
	int i, n = strlen(in); // n= 문자열의 길이
	int cnt = 1;
	init_stack(&s1);         // 스택의 초기화
	init_stack(&s2);

	for (i = 0; i < n; i++)
	{
		ch = in[i];      // ch = 다음 문자
		switch (ch) {
		case '(':   case '[':    case '{':
			push(&s1, ch);
			push(&s2, cnt);
			printf("%d ", cnt);
			cnt++;
			break;
		case ')':   case ']':    case '}':
			if (is_empty(&s1) || is_empty(&s2))  return 0;
			else
			{
				open_ch = pop(&s1);
				if (open_ch == '(' && ch != ')' || open_ch == '[' && ch != ']' || open_ch == '{' && ch != '}')
					return 0;

				else
					printf("%d ", pop(&s2));

				break;
			}
		}
	}
	if (!is_empty(&s1) || !is_empty(&s2)) return 0; // 스택에 남아있으면 오류
	return 1;
}

int main(void)
{
	char str[MAX_STACK_SIZE];
	int sel = 0;
	while (1)
	{
		printf("수식: ");  scanf("%s", str);

		if (check_matching(str) == 1)
			printf("\n괄호검사 성공\n");
		else
			printf("\n괄호검사 실패\n");

		printf("\n1.계속  2.중단: "); scanf("%d", &sel);
		if (sel != 1)
			break;
	}
	return 0;
}