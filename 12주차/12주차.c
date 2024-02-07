#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct DListNode { //이중연결 노드 타입
	char title[30];
	char genre;
	int year;
	int time;
	struct DListNode *llink;
	struct DListNode *rlink;
}DListNode;

DListNode* current;

//이중 연결 리스트를 초기화
void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

//이중 연결 리스트를 출력
void print_dlist(DListNode* phead)
{
	if (phead->rlink == phead)
	{
		printf("\n☆저장된 영화 없음☆\n");
		return;
	}
	else {
		DListNode* p;
		for (p = phead->rlink; p != phead; p = p->rlink) {
			printf("\n영화제목: %s\n", p->title);
			printf("장르: %c\n", p->genre);
			printf("개봉년도: %d\n", p->year);
			printf("재생시간: %d\n", p->time);
		}
		printf("\n");
	}
}

//새로운 데이터를 헤드노드의 오른쪽에 삽입하는 함수
void dinsert(DListNode *head)
{
	DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));
	printf("제목: "); gets_s(newnode->title, sizeof(newnode->title));
	while (1)
	{
		printf("장르(A, C, F, R): "); newnode->genre = getchar();
		if (newnode->genre == 'A' || newnode->genre == 'C' || newnode->genre == 'F' || newnode->genre == 'R')
			break;
		else
			rewind(stdin);
	}
	printf("개봉년도: "); scanf("%d", &newnode->year);
	printf("재생시간: "); scanf("%d", &newnode->time);
	
	newnode->llink = head;
	newnode->rlink = head->rlink;
	head->rlink->llink = newnode;
	head->rlink = newnode;

	current = head->rlink;
}

//삭제 함수
void ddelete(DListNode *head)
{
	if (head->rlink == head) {
		printf("\n☆저장된 영화 없음☆\n");
		return;
	}
	else
	{
		int exist = 0;
		char x[30];
		printf("삭제할 영화 제목: "); gets_s(x, sizeof(x));

		DListNode *p;
		for (p = head->rlink; p != head; p = p->rlink)
		{
			if (strcmp(p->title, x) == 0)
			{
				exist = 1;
				p->llink->rlink = p->rlink;
				p->rlink->llink = p->llink;
				if (current == p)
					current = current->rlink;
				free(p);
				printf("\n☆데이터 삭제 완료☆\n");
				return;
			}
		}
		if(exist == 0)
			printf("☆존재하지 않는 영화임☆\n");
	}
}

//제목으로 영화 정보 검색하는 함수
void search_title(DListNode *head)
{
	if (head->rlink == head) {
		printf("\n☆저장된 영화 없음☆\n");
		return;
	}
	else {
		int exist = 0;
		char x[30];
		printf("검색할 영화 제목: "); scanf("%s", x);
		DListNode *p;
		for (p = head->rlink; p != head; p = p->rlink) {
			if (strcmp(p->title, x) == 0)
			{
				exist = 1;
				printf("\n영화제목: %s\n", p->title);
				printf("영화장르: %c\n", p->genre);
				printf("개봉년도: %d\n", p->year);
				printf("재생시간: %d\n", p->time);
			}
		}
		if (exist == 0)
			printf("☆존재하지 않음☆\n");
	}
}

//최근 개봉 영화 검색 함수
void search_recent(DListNode *head)
{
	if (head->rlink == head) {
		printf("\n☆저장된 영화 없음☆\n");
		return;
	}
	else {
		DListNode *p = head->rlink;
		int recent = p->year;
		for (; p != head; p = p->rlink)
		{
			if (recent < p->year)
				recent = p->year;
		}

		for (p = head->rlink; p != head; p = p->rlink)
		{
			if (p->year == recent)
			{
				printf("\n영화제목: %s\n", p->title);
				printf("영화장르: %c\n", p->genre);
				printf("개봉년도: %d\n", p->year);
				printf("재생시간: %d\n", p->time);
			}
		}
	}
}

//장르로 영화 정보 검색하는 함수
void search_genre(DListNode *head)
{
	if (head->rlink == head) {
		printf("\n☆저장된 영화 없음☆\n");
		return;
	}
	else {
		int exist = 0;
		char x;
		while (1)
		{
			printf("장르(A, C, F, R): "); x = getchar();
			if (x == 'A' || x == 'C' || x == 'F' || x == 'R')
				break;
			else
				rewind(stdin);
		}
		DListNode *p;
		for (p = head->rlink; p != head; p = p->rlink) {
			if (p->genre == x)
			{
				exist = 1;
				printf("\n영화제목: %s\n", p->title);
				printf("영화장르: %c\n", p->genre);
				printf("개봉년도: %d\n", p->year);
				printf("재생시간: %d\n", p->time);
			}
		}
		if(exist == 0)
			printf("☆존재하지 않음☆\n");
	}
}

//길이 함수
int list_length(DListNode *head)
{
	int cnt = 0;
	for (DListNode *p = head->rlink; p != head; p = p->rlink)
		cnt++;
	return cnt;
}

void play(DListNode* head)
{
	if (head->rlink == head)
	{
		printf("\n☆저장된 영화 없음☆\n");
		return;
	}

	printf("< %s 재생 중... >\n", current->title);
	for (int i = current->time; i > 0; i--)
	{
		printf("%d ", i);
		Sleep(1000);
	}
	printf("\n");

	current = current->rlink;
	if (current == head)
		current = current->rlink;
}

void next(DListNode* head)
{
	if (head->rlink == head)
	{
		printf("\n☆저장된 영화 없음☆\n");
		return;
	}
	current = current->rlink;
	if (current == head)
		current = current->rlink;
	play(head);
}

void previous(DListNode* head)
{
	if (head->rlink == head)
	{
		printf("\n☆저장된 영화 없음☆\n");
		return;
	}
	current = current->llink;
	if (current == head)
		current = current->llink;
	play(head);
}

void first(DListNode* head)
{
	if (head->rlink == head)
	{
		printf("\n☆저장된 영화 없음☆\n");
		return;
	}
	current = head->rlink;
	play(head);
}

void last(DListNode* head)
{
	if (head->rlink == head)
	{
		printf("\n☆저장된 영화 없음☆\n");
		return;
	}
	current = head->llink;
	play(head);
}

int main(void)
{
	DListNode* head = (DListNode *)malloc(sizeof(DListNode));
	init(head);
	char select;
	int i = 0;
	while (1)
	{
		if (i > 0)
			printf("\n");
		i++;

		printf("------- MUNU -------\n");
		printf("영화 정보 추가(1)\n");
		printf("영화 정보 출력(2)\n");
		printf("영화 제목 검색(3)\n");
		printf("영화 정보 삭제(4)\n");
		printf("저장된 영화 개수 출력(5)\n");
		printf("최근 개봉 영화 검색(6)\n");
		printf("영화 장르 검색(7)\n");
		printf("현재 영화 재생(P)\n");
		printf("다음 영화 재생(>)\n");
		printf("이전 영화 재생(<)\n");
		printf("처음 영화 재생(F/f)\n");
		printf("마지막 영화 재생(L/l)\n");
		printf("종료(0)\n");
		printf("--------------------\n");
		printf(">> ");
		scanf(" %c", &select);
		rewind(stdin);
	
		if (select == '1')
			dinsert(head);
		else if (select == '2')
			print_dlist(head);
		else if (select == '3')
			search_title(head);
		else if (select == '4')
			ddelete(head);
		else if (select == '5')
			printf("저장된 영화 개수: %d\n", list_length(head));
		else if (select == '6')
			search_recent(head);
		else if (select == '7')
			search_genre(head);
		else if (select == 'P')
			play(head);
		else if (select == '>')
			next(head);
		else if (select == '<')
			previous(head);
		else if (select == 'F' || select == 'f')
			first(head);
		else if (select == 'L' || select == 'l')
			last(head);
		else
			break;
	}
	return 0;
}