#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode { //노드 타입
	char title[30];
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

//삭제 함수
ListNode* delete_list(ListNode *head, char *x)
{
	if (head == NULL)
	{
		printf("\n☆저장된 영화 없음☆\n");
		return NULL;
	}
	else
	{
		ListNode *removed;
		ListNode *pre = head;
		for (ListNode *p = head; p != NULL; p = p->link)
		{
			if (strcmp(p->title, x) == 0)
			{
				removed = p;
				if (p == head)
					head = removed->link;
				else
					pre->link = removed->link;
				free(removed);
				printf("\n☆데이터 삭제 완료☆\n");
				return head;
			}
			else
				pre = p;
		}
	}
}

//제목으로 영화 정보 검색하는 함수
ListNode* search_title(ListNode *head, char *x)
{
	ListNode *p = head;
	while (p != NULL) {
		if (strcmp(p->title, x) == 0)
		{
			printf("\n영화제목: %s\n", p->title);
			printf("영화장르: %c\n", p->genre);
			printf("개봉년도: %d\n", p->year);
			return p;
		}
		p = p->link;
	}
	return NULL;
}

//최근 개봉 영화 검색 함수
void search_recent(ListNode *head)
{
	if (head == NULL)
	{
		printf("\n☆저장된 영화 없음☆\n");
		return;
	}
	ListNode *p = head;
	int recent = p->year;
	for (; p != NULL; p = p->link)
	{
		if (recent < p->year)
			recent = p->year;
	}

	for (p = head; p != NULL; p = p->link)
	{
		if (p->year == recent)
		{
			printf("\n영화제목: %s\n", p->title);
			printf("영화장르: %c\n", p->genre);
			printf("개봉년도: %d\n", p->year);
		}
	}
}

//장르로 영화 정보 검색하는 함수
void search_genre(ListNode *head, char x)
{
	if (head == NULL)
	{
		printf("\n☆저장된 영화 없음☆\n");
		return;
	}
	ListNode *p = head;
	while (p != NULL) {
		if (p->genre == x)
		{
			printf("\n영화제목: %s\n", p->title);
			printf("영화장르: %c\n", p->genre);
			printf("개봉년도: %d\n", p->year);
		}
		p = p->link;
	}
}

//길이 출력(일반) 함수
int list_length1(ListNode *head)
{
	int cnt = 0;
	for (ListNode *p = head; p != NULL; p = p->link)
		cnt++;
	return cnt;
}

//길이 출력(순환) 함수
int list_length2(ListNode *head)
{
	ListNode *p = head;
	if (p == NULL)
		return 0;
	else
		return 1 + list_length2(p->link);
}

//리스트 출력(일반) 함수
void print_list1(ListNode *head)
{
	if (head == NULL)
		return;

	ListNode *p = head;
	for (; p != NULL; p = p->link)
	{
		printf("\n영화제목: %s\n", p->title);
		printf("장르: %c\n", p->genre);
		printf("개봉년도: %d\n", p->year);
	}
	printf("NULL \n");
}

//리스트 출력(순환)
void print_list2(ListNode *head)
{
	ListNode *p = head;
	if (p == NULL)
		printf("NULL");
	else
	{
		printf("\n영화제목: %s\n", p->title);
		printf("장르: %c\n", p->genre);
		printf("개봉년도: %d\n", p->year);
		print_list2(p->link);
	}
}

//리스트 역순 출력(순환)
void print_list3(ListNode *head)
{
	ListNode *p = head;
	if (p == NULL)
		printf("NULL");
	else
	{
		print_list3(p->link);
		printf("\n영화제목: %s\n", p->title);
		printf("장르: %c\n", p->genre);
		printf("개봉년도: %d\n", p->year);
	}
}

int main(void)
{
	ListNode *head = NULL;
	char title[50], genre;
	int year, select = 0, i = 0;

	while (1)
	{
		if (i > 0)
			printf("\n");

		i = 1;
		printf("------- MUNU -------\n");
		printf("1. 영화 정보 추가\n");
		printf("2. 영화 정보 출력(일반)\n");
		printf("3. 영화 정보 출력(순환)\n");
		printf("4. 영화 정보 출력(역순 순환)\n");
		printf("5. 저장된 영화 개수 출력\n");
		printf("6. 영화 제목 검색\n");
		printf("7. 최근 개봉 영화 검색\n");
		printf("8. 영화 장르 검색\n");
		printf("9. 영화 정보 삭제\n");
		printf("0. 종료\n");
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
		}
		else if (select == 2)
			print_list1(head);
		else if (select == 3)
			print_list2(head);
		else if(select == 4)
			print_list3(head);
		else if (select == 5)
		{
			printf("저장된 영화 개수(일반): %d\n", list_length1(head));
			printf("저장된 영화 개수(순환): %d\n", list_length2(head));
		}
		else if (select == 6)
		{
			printf("검색할 영화 제목: ");
			gets_s(title, sizeof(title)); rewind(stdin);
			if (search_title(head, title) != NULL)
				printf("\n☆영화 제목 검색 완료☆\n");
			else
				printf("\n☆영화 정보 찾기 실패☆\n");
		}
		else if(select == 7)
			search_recent(head);
		else if (select == 8)
		{
			printf("검색할 영화 장르(A, C, F, R): "); genre = getchar();
			if (genre == 'A' || genre == 'C' || genre == 'F' || genre == 'R')
				search_genre(head, genre);
			else
				printf("\n☆존재하지 않는 영화 장르입니다☆\n");
		}
		else if (select == 9)
		{
			printf("삭제할 영화 제목: ");
			gets_s(title, sizeof(title)); rewind(stdin);

			if (search_title(head, title) != NULL)
				delete_list(head, title);
			else
				printf("\n☆존재하지 않는 영화 제목입니다☆\n");
		}
		else
			break;
	}
	return 0;
}