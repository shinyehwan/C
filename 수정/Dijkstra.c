#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NODE_MAX 20001
#define EDGE_MAX 600001 // 양방향 간선이므로 300000개

typedef struct {
	int cost;
	int node;
}Edge;

void swap(Edge *a, Edge *b) {
	Edge temp;
	temp.cost = a->cost;
	temp.node = a->node;
	a->cost = b->cost;
	a->node = b->node;
	b->cost = temp.cost;
	b->node = temp.node;
}
typedef struct {
	Edge *heap[EDGE_MAX];
	int count;
}priorityQueue;

void push(priorityQueue *pq, Edge *edge) {
	if (pq->count >= EDGE_MAX) return;
	pq->heap[pq->count] = edge;
	int now = pq->count;
	int parent = (pq->count - 1) / 2;
	// 새원소를 삽입한 이후에 상향식으로 힙을 구성합니다.
	while (now > 0 && pq->heap[now]->cost < pq->heap[parent]->cost) {
		swap(pq->heap[now], pq->heap[parent]);
		now = parent;
		parent = (parent - 1) / 2;
	}
	pq->count++;
}

Edge *pop(priorityQueue *pq) {
	if (pq->count <= 0)return NULL;
	Edge *res = pq->heap[0]; // 루트노드를 반환
	pq->count--;
	pq->heap[0] = pq->heap[pq->count];
	int now = 0, leftChild = 1, rightChild = 2;
	int target = now;
	// 새 원소를 추출한 이후에 하향식으로 힙을 구성
	while (leftChild < pq->count) {
		if (pq->heap[target]->cost > pq->heap[leftChild]->cost) target = leftChild;
		if (pq->heap[target]->cost > pq->heap[rightChild]->cost && rightChild < pq->count) target = rightChild;
		if (target == now) break; // 더 이상 내려가지 않아도 될때 종료
		else {
			swap(pq->heap[now], pq->heap[target]);
			now = target;
			leftChild = now * 2 + 1;
			rightChild = now * 2 + 2;
		}
	}
	return res;
}

// 프림 알고리즘 간선 연결리스트 구현
typedef struct Node {
	Edge *data;
	struct Node *next;
}Node;

Node **adj;
int ans[NODE_MAX]; //특정한 노드값의 최단 거리값 

void addNode(Node **target, int index, Edge *edge) {
	if (target[index] == NULL) { // 특정 정점에 연결되어있는 간선이 하나도 없다면, 첫번째 원소로 해당 간선 추가
		target[index] = (Node*)malloc(sizeof(Node));
		target[index]->data = edge;
		target[index]->next = NULL;
	}
	else {
		Node *node = (Node*)malloc(sizeof(Node));
		node->data = edge;
		node->next = target[index];
		target[index] = node;
	}
}

int main(void) {
	int n, m, k; //정점의 개수, 간선의 개수, 출발하는 노드
	scanf("%d %d %d", &n, &m, &k);
	adj = (Node**)malloc(sizeof(Node*)*(n + 1)); //정점의 개수 만큼 동적할당으로 연결리스트를 만들어준다
	for (int i = 1; i <= n; i++) {
		adj[i] = NULL;
		ans[i] = INT_MAX;

	}
	priorityQueue *pq;
	pq = (priorityQueue*)malloc(sizeof(priorityQueue));
	pq->count = 0;
	for (int i = 0; i < m; i++) {
		int a, b, c; // a에서 b만큼 가는데 c만큼 가중치가 들어간다.
		scanf("%d %d %d", &a, &b, &c);
		Edge *edge = (Edge*)malloc(sizeof(Edge));
		edge->node = b;
		edge->cost = c;
		addNode(adj, a, edge);

	}

	//다익스트라 알고리즘 시작
	ans[k] = 0;
	Edge *start = (Edge*)malloc(sizeof(Edge));
	start->cost = 0; start->node = k; push(pq, start);

	while (1) {
		Edge *now = pop(pq);
		if (now == NULL) break;
		int curNode = now->node;
		int curCost = now->cost;
		if (ans[curNode] < curCost) continue;
		Node *cur = adj[curNode];
		while (cur != NULL) {
			Edge * temp = cur->data;
			temp->cost += curCost;
			if (temp->cost < ans[temp->node]) { ans[temp->node] = temp->cost; push(pq, temp); }
			cur = cur->next;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (ans[i] == INT_MAX) printf("INF\n");
		else printf("%d\n", ans[i]);
	}
	system("pause");
}
