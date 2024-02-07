#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int function1(int arr[], int low, int high, int key)
{
	int mid = 0;

	while (low <= high)
	{
		mid = (low + high) / 2;
		printf("탐색 범위: [%d - %d]\n", low, high);
		printf("현재 arr[%d]와(과) 비교 중\n\n", mid);

		if (key == arr[mid])
			return mid;
		else if (key > arr[mid])
			low = mid + 1;
		else
			high = mid - 1;
	}

	return -1;
}

int function2(int arr[], int low, int high, int key)
{
	int mid = 0;

	if (low > high)
		return -1;

	mid = (low + high) / 2;
	printf("탐색 범위: [%d - %d]\n", low, high);
	printf("현재 arr[%d]와(과) 비교 중\n\n", mid);

	if (arr[mid] == key)
		return mid;
	else if (key < arr[mid])
		return function2(arr, low, mid - 1, key);
	else
		return function2(arr, mid + 1, high, key);
}

int main(void) {

	int size = 0, key = 0, least = 0, tmp = 0, result = 0;

	printf("입력할 수의 개수: ");
	scanf("%d", &size);

	int * arr = (int*)malloc(size * sizeof(int));

	printf("\n정수 %d개를 입력하세요\n", size);
	for (int i = 0; i < size; i++)
	{
		printf("%d번째: ", i + 1);
		scanf("%d", &arr[i]);
	}

	for (int i = 0; i < size - 1; i++) {
		least = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[least])
				least = j;
		}
		tmp = arr[i];
		arr[i] = arr[least];
		arr[least] = tmp;
	}

	printf("\n정렬 후: ");
	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);

	printf("\n찾는 값: ");
	scanf("%d", &key);

	printf("\n\n< 과제 2-1 > \n");
	result = function1(arr, 0, size - 1, key);

	if (result == -1)
		printf("%d은(는) 존재하지 않음\n", key);
	else
		printf("%d은(는) arr[%d]에 존재함\n", key, result);

	printf("\n\n< 과제 2-2 > \n");
	result = function2(arr, 0, size - 1, key);

	if (result == -1)
		printf("%d은(는) 존재하지 않음\n", key);
	else
		printf("%d은(는) arr[%d]에 존재함\n", key, result);

	free(arr);

	return 0;
}