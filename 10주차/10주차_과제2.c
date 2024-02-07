#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode { //노드 타입
	char title[50];
	char genre;
	int year;
	struct ListNode *link;
}ListNode;

//오류 처리 함수
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//삽입 함수
ListNode* insert_node(ListNode *head, char *title, char genre, int year)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));

	strcpy(newNode->title, title);
	newNode->genre = genre;
	newNode->year = year;

	if (head == NULL) //빈 노드일 경우 제일 앞에 삽입
	{
		head = newNode;
		newNode->link = NULL;
		return head;
	}

	ListNode *pre = head;
	for (ListNode *p = head; p; p = p->link) {
		if (strcmp(p->title, newNode->title) > 0) { //삽입할 영화제목이 앞일 때
			if (p == head) {
				newNode->link = head;
				head = newNode;
				return head;
			}
			else {
				newNode->link = pre->link;
				pre->link = newNode;
				return head;
			}
		}
		else {
			pre = p;
		}
	}

	pre->link = newNode; //맨 끝에 삽입
	newNode->link = NULL;
	return head;
}
/*
ListNode* delete_first(ListNode *head)
{
	ListNode *removed;
	if (head == NULL) return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

//pre가 가리키는 노드의 다음 노드를 삭제한다.
ListNode* delete(ListNode *head, ListNode *pre)
{
	ListNode *removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}
*/
int list_length(ListNode *head)
{
	int cnt = 0;
	for (ListNode *p = head; p != NULL; p = p->link)
		cnt++;
	return cnt;
}

void print_list(ListNode *head)
{
	for (ListNode *p = head; p != NULL; p = p->link)
	{
		printf("\n영화제목: %s\n", p->title);
		printf("장르: %c\n", p->genre);
		printf("개봉년도: %d\n", p->year);
	}
	printf("NULL \n");
}

int main(void)
{
	ListNode *head = NULL;
	char title[50], genre;
	int year, select = 0, i =0;

	while (1)
	{
		if (i > 0)
			printf("\n");

		i = 1;
		printf("------- MUNU -------\n");
		printf("1. 영화 정보 추가\n");
		printf("2. 영화 정보 출력\n");
		printf("3. 종료\n");
		printf("--------------------\n");
		printf("번호 선택: "); scanf("%d", &select);
		rewind(stdin);

		if (select == 1)
		{
			printf("\n영화제목: ");
			gets_s(title, sizeof(title)); rewind(stdin);
			
			while (1)
			{
				printf("장르(A, C, F, R): "); genre = getchar();
				if (genre == 'A' || genre == 'C' || genre == 'F' || genre == 'R')
					break;
				else
					rewind(stdin);
			}

			printf("개봉년도: "); scanf("%d", &year);

			head = insert_node(head, title, genre, year);
			printf("☆데이터 저장 완료☆\n");
			printf("--------------------\n");
			printf("\n저장된 영화의 개수: %d\n", list_length(head));
			print_list(head);
		}
		else if (select == 2)
		{
			printf("\n저장된 영화의 개수: %d\n", list_length(head));
			print_list(head);
		}
		else
			break;
	}

	return 0;
}