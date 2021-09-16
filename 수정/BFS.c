#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define INF 99999999
#define MAX_SIZE 1001


typedef struct {
	int index;
	struct Node* next;
}Node;

typedef struct {
	Node* front;
	Node* rear;
	int count;
} Queue;

Node** a; //연결리스트(정점)이 여러개이기 때문에 이차원 포인터로 할당
int n, m, c[MAX_SIZE]; //n은 정점, m은 간선, c는 방문을 했는지 파악

void addFront(Node* root, int index) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->index = index;
	node->next = root->next;
	root->next = node;
}

void queuePush(Queue* queue, int index) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->index = index;
	node->next = NULL;
	if (queue->count == 0) { //큐가 비어있다면 앞에 추가
		queue->front = node;
	}
	else { //큐가 비어있지 않다면 꼬리에 추가
		queue->rear->next = node;
	}
	queue->rear = node;
	queue->count++;
}

int queuePop(Queue* queue) {
	if (queue->count == 0) {
		printf("큐 언더플로우가 발생했습니다. \n");
		return -INF;
	}
	Node* node = queue->front;
	int index = node->index;
	queue->front = node->next;
	free(node);
	queue->count--;
	return index;
}

void bfs(int start) {
	Queue q;
	q.front = q.rear = NULL; //큐 초기화
	q.count = 0;
	queuePush(&q, start); //시작 인덱스를 넣어줌
	c[start] = 1; //방문처리
	while (q.count != 0) {
		int x = queuePop(&q);
		printf("%d ", x);
		Node* cur = a[x]->next;
		while (cur != NULL) { //인접 노드 확인
			int next = cur->index;
			if (!c[next]) { //방문하지 않은 상태라면 큐에 넣음
				queuePush(&q, next);
				c[next] = 1;
			}
			cur = cur->next;
		}
	}
}

int main(void) {
	scanf("%d %d", &n, &m); //정점 개수 간선 개수 입력
	a = (Node**)malloc(sizeof(Node*) * (MAX_SIZE));
	for (int i = 1; i <= n; i++) {
		a[i] = (Node*)malloc(sizeof(Node));
		a[i]->next = NULL;
	}
	for (int i = 0; i < m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		addFront(a[x], y);
		addFront(a[y], x);
	}
	bfs(1);
	system("pause");
}