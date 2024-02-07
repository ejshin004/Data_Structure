#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define MAX_TERMS 100

typedef struct {
	int row;
	int col;
	int value;
} element;

typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows;	// 행의 개수
	int cols;	// 열의 개수
	int terms; 	// 항의 개수
} SparseMatrix;

SparseMatrix change1(int m[][5], int row, int col)
{
	SparseMatrix c = { 0 };
	int k = 0, cnt = 0;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (m[i][j] != 0)
			{
				c.data[k].row = i;
				c.data[k].col = j;
				c.data[k++].value = m[i][j];
				cnt++;
			}
		}
	}

	c.rows = row;
	c.cols = col;
	c.terms = cnt;
	return c;
}

SparseMatrix change2(int m[][6], int row, int col)
{
	SparseMatrix c = { 0 };
	int k = 0, cnt = 0;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (m[i][j] != 0)
			{
				c.data[k].row = i;
				c.data[k].col = j;
				c.data[k++].value = m[i][j];
				cnt++;
			}
		}
	}

	c.rows = row;
	c.cols = col;
	c.terms = cnt;
	return c;
}

void print(SparseMatrix m)
{
	int k = 0;

	for (int i = 0; i < m.rows; i++) {
		for (int j = 0; j < m.cols; j++)
		{
			if (i == m.data[k].row && j == m.data[k].col)
			{
				printf("%2d ", m.data[k].value);
				k++;
			}

			else
				printf(" 0 ");
		}
		printf("\n");
	}
	printf("\n");
}

SparseMatrix calculation(SparseMatrix a, SparseMatrix b)
{
	SparseMatrix c = { 0 };

	if (a.rows != b.rows || a.cols != b.cols)
	{
		printf("두 행렬의 크기가 다름\n");
		exit(1);
	}

	else
	{
		c.rows = a.rows;
		c.cols = a.cols;
		c.terms = 0;
	}

	int index_a = 0, index_b = 0;
	int cnta = 0, cntb = 0, cntc = 0;

	while (cntc <= a.terms && cntb <= b.terms)
	{
		index_a = a.data[cnta].row * a.cols + a.data[cnta].col;
		index_b = b.data[cntb].row * b.cols + b.data[cntb].col;

		if (index_a == index_b)
		{
			if (a.data[cnta].value + b.data[cntb].value != 0)
			{
				c.data[cntc].row = a.data[cnta].row;
				c.data[cntc].col = a.data[cnta].col;
				c.data[cntc++].value = a.data[cnta++].value + b.data[cntb++].value;
			}

			else
			{
				cnta++; cntb++;
			}
		}

		else if (index_a < index_b)
		{
			c.data[cntc++] = a.data[cnta++];
		}

		else
		{
			c.data[cntc++] = b.data[cntb++];
		}
	}

	while (cnta < a.terms)
		c.data[cntc++] = a.data[cnta++];

	while (cntb < b.terms)
		c.data[cntc++] = b.data[cntb++];

	c.terms = cntc;

	return c;
}

int main(void)
{
	SparseMatrix SA, SB, SC, SD, result;

	int A[7][5] = { { 0, 0, 0, 0, 2 },
					  { 0, 0,-1, 0, 0 },
					  { 0, 0, 0, 0, 0 },
					  { 5, 0, 0, 0, 0 },
					  { 0, 0, 0, 0, 0 },
					  { 0, 0, 0, 0, 3 },
					  { 0, 0, 1, 0, 0 } };
	int Ar = 7; int Ac = 5;

	int B[7][5] = { { 0, 0, 0, 0, 0 },
					   { 0, 0, 1, 0, 0 },
					   { 0,-2, 0, 0, 0 },
					   { 0, 0, 0, 0, 0 },
					   { 0, 0, 0, 0, 0 },
					   { 0, 0, 0, 0, 0 },
					   { 0, 0, 5, 0, 0 } };
	int Br = 7; int Bc = 5;

	int C[5][6] = { { 0, 0, 0, 0, 0, 2 },
					   { 0, 0, 0,-1, 0, 0 },
					   { 0, 0, 0, 0, 0, 0 },
					   { 0, 5, 0, 0, 0, 0 },
					   { 0, 0, 0, 0, 3, 0 } };
	int Cr = 5; int Cc = 6;

	int D[5][6] = { { 0, 2, 0, 0, 0, 0 },
						  { 0, 0, 0, 1, 0, 0 },
						  { 0, 3, 0, 0, 0, 0 },
						  { 0, 5, 0, 0, 0, 0 },
						  { 0, 0, 0, 0,-1, 0 } };
	int Dr = 5; int Dc = 6;

	SA = change1(A, Ar, Ac);
	SB = change1(B, Br, Bc);
	SC = change2(C, Cr, Cc);
	SD = change2(D, Dr, Dc);

	char sign = 0;

	printf("====== A ======\n");
	print(SA);

	printf("====== B ======\n");
	print(SB);
	
	printf("======= C =======\n");
	print(SC);

	printf("======= D =======\n");
	print(SD);
	sign = _getch();

	result = calculation(SA, SB);
	printf("==== A + B ====\n");
	print(result);
	sign = _getch();

	for (int i = 0; i < SB.terms; i++)
	{
		SB.data[i].value *= -1;
	}
	result = calculation(SA, SB);
	printf("==== A - B ====\n");
	print(result);
	sign = _getch();

	result = calculation(SC, SD);
	printf("===== C + D =====\n");
	print(result);
	sign = _getch();

	for (int i = 0; i < SD.terms; i++)
	{
		SD.data[i].value *= -1;
	}
	result = calculation(SC, SD);
	printf("===== C - D =====\n");
	print(result);

	return 0;
}