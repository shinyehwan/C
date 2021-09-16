#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 1001	
// 작동은 되는데 정상적으로 동작하지 않는다ㅠㅠ
typedef struct {
	int index;
	struct Node *next;
}Node;

Node **a; // 정점이 여러개라고 가정.
int n, m, c[MAX_SIZE];

void addFront(Node *root, int index) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->index = index;
	node->next = root->next;
	root->next = node;

}

void dfs(int x) {
	if (c[x]) return;
	c[x] = 1;
	printf("%d ", x);
	Node *cur = a[x]->next;
	while (cur != NULL) {
		int next = cur->index;
		dfs(next); //재귀적 호출
		cur = cur->next;
	}
}

int main(void) {
	scanf("%d %d", &n, &m);
	a = (Node**)malloc(sizeof(Node*) * (MAX_SIZE));
	for (int i = 1; i <= n; i++) {
		a[i] = (Node*)malloc(sizeof(Node));
		a[i]->next = NULL;
	}
	for (int i = 0; i < m; i++); {
		int x, y;
		scanf("%d %d", &x, &y);
		addFront(a[x], y);
		addFront(a[y], x);
	}
	dfs(1); // 1에서 시작한다고 생각해라
	system("pause");
	return 0;
}