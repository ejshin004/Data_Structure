#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

typedef struct point {
	int xpos;
	int ypos;
}Point;

double function1(Point p);
Point function2(Point *p);

int main(void) {

	Point pos1;
	Point pos2[5];

	printf("< 과제 3-1 > \n");
	printf("x좌표 y좌표 입력: ");
	scanf("%d %d", &pos1.xpos, &pos1.ypos);

	printf("원점으로부터의 거리: %g \n\n", function1(pos1));

	printf("< 과제 3-2 > \n");

	printf("좌표 5개 입력\n");
	for (int i = 0; i < 5; i++)
	{
		printf("%d번째 x좌표 y좌표 입력: ", i + 1);
		scanf("%d %d", &pos2[i].xpos, &pos2[i].ypos);
	}

	printf("원점으로부터 가장 먼 좌표: (%d, %d) \n\n", function2(pos2).xpos, function2(pos2).ypos);
	return 0;
}

double function1(Point p)
{
	double distance = 0.0;
	distance = sqrt((double)((p.xpos * p.xpos) + (p.ypos * p.ypos)));
	return distance;
}

Point function2(Point *p)
{
	double distance[5];
	double farDistance = 0.0;
	int farPoint = 0;

	for (int i = 0; i < 5; i++)
	{
		distance[i] = function1(p[i]);
	}

	farDistance = distance[0];

	for (int i = 1; i < 5; i++)
	{
		if (distance[i] > farDistance)
		{
			farDistance = distance[i];
			farPoint = i;
		}
	}

	return p[farPoint];
}