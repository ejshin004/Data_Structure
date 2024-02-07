#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define MAX_QUEUE_SIZE 20

typedef int element;
typedef struct { // 큐 타입
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// 오류 함수
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 공백 상태 검출 함수
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 원형큐 출력 함수
void queue_print(QueueType *q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

// 삽입 함수
void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 삭제 함수
element peek(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// ===== 원형큐 코드 끝 ======

int main(void)
{
	int random, m = 1, f = 1;
	QueueType mq, fq;
	init_queue(&mq);
	init_queue(&fq);

	for (int i = 0; i < 100; i++)
	{
		random = rand() % 2;
		if (random == 0)
		{
			enqueue(&mq, m);
			printf("남%d 입장 - ", m);
			m++;
		}
		else
		{
			enqueue(&fq, f);
			printf("여%d 입장 - ", f);
			f++;
		}
		if (!is_empty(&mq) && !is_empty(&fq) && mq.front == fq.front)
			printf("남%d/여%d 매칭\n", dequeue(&mq), dequeue(&fq));
		else
			printf("대기\n");

		printf("남자 큐 front: %d, rear: %d\n", mq.front, mq.rear);
		printf("여자 큐 front: %d, rear: %d\n", fq.front, fq.rear);
		printf("\n");
		Sleep(100);
	}

	return 0;
}