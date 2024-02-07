#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
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

int check_matching(FILE *fp)
{
	StackType s;
	char ch, open_ch;
	init_stack(&s);         // 스택의 초기화
	int sq = 0, dq = 0, an_pre = 0, an = 0, star_an = 0, star_an_pre = 0;
	FILE* fp2 = fopen("stack.out", "w");

	while ((ch = getc(fp)) != EOF) {
		//주석 or 일반 문자
		if (ch == '/' && an_pre == 1)
			an = 1;
		else if (ch == '*' && an_pre == 1)
			star_an = 1;
		else
			an_pre = 0;

		//별 주석 해제 or 일반 문자
		if (ch == '/' && star_an_pre == 1)
			star_an = 0;
		else
			star_an_pre = 0;

		//개행
		if (ch == '\n')
			an = 0;

		//작은 따옴표
		if (ch == '\''&& sq == 0)
			sq = 1;
		else if (ch == '\'')
			sq = 0;

		//큰 따옴표
		if (ch == '"' && dq == 0)
			dq = 1;
		else if (ch == '"')
			dq = 0;

		//주석
		if (ch == '/' && an_pre == 0)
			an_pre = 1;
		if (ch == '*' && star_an == 1)
			star_an_pre = 1;

		//괄호 검사
		if (ch == '(' || ch == '[' || ch == '{')
		{
			if (sq == 0 && dq == 0 && an == 0 && star_an == 0)
			{
				push(&s, ch);
				printf("push %c\n", peek(&s));
				fprintf(fp2, "push %c\n", ch);
			}
		}

		else if (ch == ')' || ch == ']' || ch == '}')
		{
			if (sq == 0 && dq == 0 && an == 0 && star_an == 0)
			{
				if (is_empty(&s))  return 0;
				else {
					open_ch = pop(&s); 
					printf("pop %c\n", open_ch);
					fprintf(fp2, "pop %c\n", open_ch);
					if ((open_ch == '(' && ch != ')') ||
						(open_ch == '[' && ch != ']') ||
						(open_ch == '{' && ch != '}')) {
						return 0;
					}
				}
			}
		}
	}

	fclose(fp2);
	if (!is_empty(&s)) return 0; // 스택에 남아있으면 오류
	return 1;
}

int main(void)
{
	FILE* fp1 = fopen("stack.in", "r");
	if (fp1 == NULL) {
		printf("파일을 열 수 없습니다.\n");
		exit(1);
	}

	int result = check_matching(fp1);

	FILE* fp2 = fopen("stack.out", "a");
	if (result == 1) {
		printf("괄호검사 성공\n");
		fputs("괄호검사 성공\n", fp2);
	}
	else {
		printf("괄호검사 실패\n");
		fputs("괄호검사 실패\n", fp2);
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}