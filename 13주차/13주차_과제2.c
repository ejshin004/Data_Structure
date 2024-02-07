#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
} TreeNode;

//            15
//       4         20
//    1         16    25
//  5   2     3          7

TreeNode n1 = { 5, NULL, NULL };
TreeNode n2 = { 2, NULL, NULL };
TreeNode n3 = { 1, &n1, &n2 };
TreeNode n4 = { 4, &n3, NULL };
TreeNode n5 = { 3, NULL, NULL };
TreeNode n6 = { 16, &n5, NULL };
TreeNode n7 = { 7, NULL, NULL };
TreeNode n8 = { 25, NULL, &n7 };
TreeNode n9 = { 20, &n6, &n8 };
TreeNode n10 = { 15, &n4, &n9 };
TreeNode *root = &n10;

//중위 순회
void inorder(TreeNode *root)
{
	if (root != NULL) {
		inorder(root->left);
		printf("[%d] ", root->data); //노드 방문
		inorder(root->right);
	}
}

//전위 순회
void preorder(TreeNode *root)
{
	if (root != NULL) {
		printf("[%d] ", root->data); //노드 방문
		preorder(root->left);
		preorder(root->right);
	}
}

//후위 순회
void postorder(TreeNode *root)
{
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("[%d] ", root->data); //노드 방문
	}
}

void preorder_plus(TreeNode *root)
{
	if (root != NULL) {
		root->data++;
		preorder_plus(root->left);
		preorder_plus(root->right);
	}
}

int sum(TreeNode *root)
{
	if (root == NULL)
		return 0;
	else {
		int tmp = sum(root->left) + sum(root->right);
		return tmp + root->data;
	}
}

int FindMax(TreeNode *root)
{
	if (root == NULL)
		return 0;
	else {
		int left = FindMax(root->left);
		int right = FindMax(root->right);
		int max = left > right ? left : right;
		return (max > root->data ? max : root->data);
	}
}

void MinValue(TreeNode *root, int x) {
	if (root != NULL) {
		MinValue(root->left, x);
		if (root->data < x) {
			printf("[%d] ", root->data);
		}
		MinValue(root->right, x);
	}
}

int main(void)
{
	int x = 0;

	printf("중위 순회: ");
	inorder(root);
	printf("\n");

	printf("전위 순회: ");
	preorder(root);
	printf("\n");

	printf("후위 순회: ");
	postorder(root);
	printf("\n");

	printf("\n전위 순회 1 증가: ");
	preorder_plus(root);
	preorder(root);
	printf("\n");

	printf("후위 순회 총합: ");
	printf("%d\n", sum(root));

	printf("후위 순회 최댓값: ");
	printf("%d\n", FindMax(root));
	printf("\n");

	printf("x값 입력: "); scanf("%d", &x);
	printf("%d보다 작은 값: ", x);
	MinValue(root, x);
	printf("\n");

	return 0;
}