#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int findMax(int arr[], int n)
{
	if (n == 0)
		return arr[0];

	int max = findMax(arr, n - 1);

	if (max < arr[n])
		return arr[n];
	else
		return max;
}

int main(void) {

	int arr[10];

	printf("정수 10개 입력 \n");
	for (int i = 0; i < 10; i++)
	{
		printf("%d번째: ", i + 1);
		scanf("%d", &arr[i]);
	}
	printf("\n가장 큰 수: %d\n", findMax(arr, 10));

	return 0;
}