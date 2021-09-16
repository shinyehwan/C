#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NODE_MAX 1001
#define EDGE_MAX 200001 // 양방향 간선이므로 100,000개

typedef struct {
  int cost;
  int node;
} Edge;

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
} priorityQueue;

void push(priorityQueue *pq, Edge *edge) {
  if (pq->count >= EDGE_MAX) return;
  pq->heap[pq->count] = edge;
  int now = pq->count;
  int parent = (pq->count - 1) / 2;
  // 새 원소를 삽입한 이후에 상향식으로 힙을 구성합니다.
  while (now > 0 && pq->heap[now]->cost < pq->heap[parent]->cost) {
    swap(pq->heap[now], pq->heap[parent]);
    now = parent;
    parent = (parent - 1) / 2;
  }
  pq->count++;
}

Edge* pop(priorityQueue *pq) {
  if (pq->count <= 0) return NULL;
  Edge *res = pq->heap[0]; // 루트노드를 반환
  pq->count--;
  pq->heap[0] = pq->heap[pq->count];
  int now = 0, leftChild = 1, rightChild = 2;
  int target = now;
  // 새 원소를 추출한 이후에 하향식으로 힙을 구성합니다.
  while (leftChild < pq->count) {
    if (pq->heap[target]->cost > pq->heap[leftChild]->cost) target = leftChild;
    if (pq->heap[target]->cost > pq->heap[rightChild]->cost && rightChild < pq->count) target = rightChild;
    if (target == now) break; // 더 이상 내려가지 않아도 될 때 종료
    else {
      swap(pq->heap[now], pq->heap[target]);
      now = target;
      leftChild = now * 2 + 1;
      rightChild = now * 2 + 2;
    }
  }
  return res;
}

//프림 알고리즘 간선 연결리스트 구현
typedef struct Node {
  Edge *data;
  struct Node *next;
} Node;

Node** adj;
int d[NODE_MAX];

void addNode(Node** target, int index, Edge* edge) {
  if (target[index] == NULL) { // 특정 정점에 연결되어있는 간선이 하나도 없다면, 첫번째 원소로 해당간 선 추가
    target[index] = (Node*)malloc(sizeof(Node));
    target[index]->data = edge;
    target[index]->next = NULL;
  }
  else {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = edge;
    node->next = target[index];
    target[index] = node;
  }
}

int main(void) {
  int n, m; // 정점의 개수와 간선의 개수
  scanf("%d %d", &n, &m); 
  adj = (Node**)malloc(sizeof(Node*) * (n + 1)); // 정점의 개수 만큼 동적할당으로 연결리스트를 만들어준다
  for(int i = 1; i <= n; i++) {
    adj[i] = NULL;
  }
  priorityQueue*pq;
  pq = (priorityQueue*)malloc(sizeof(priorityQueue));
  pq->count = 0;
  for(int i = 0; i < m; i++) {
    int a, b, c; // a에서 b만큼 가는데 c만큼의 가중치가 들어간다
    scanf("%d %d %d", &a, &b, &c);
    Edge *edge1 = (Edge*)malloc(sizeof(Edge));
    edge1->node = b;
    edge1->cost = c;
    addNode(adj, a, edge1);
    Edge *edge2 = (Edge*)malloc(sizeof(Edge));
    edge2->node = a;
    edge2->cost = c;
    addNode(adj, b, edge2);
  }
//프림 알고리즘 시작
  long long res = 0;
  Edge *start = (Edge*)malloc(sizeof(Edge));
  start->cost = 0; start->node = 1; push(pq, start);
  for (int i = 1; i <= n; i++) { // 정점의 개수가 n개니깐
    int nextNode = -1, nextCost = INT_MAX;
    while (1) { // 방문하지 않은 노드들 중에서 가장 비용이 적은 노드를 우선순위 큐에서 꺼내준다. 알아서 비용이 적은 수로 들어가 있다
      Edge* now = pop(pq);
      if (now == NULL) break;
      nextNode = now->node;
      if (!d[nextNode]) {
        nextCost = now->cost; break;
      }
    }
    if (nextCost == INT_MAX) printf("연결 그래프가 아닙니다.\n");
    res += nextCost;
    d[nextNode] = 1; // 가중치가 적은 간선에 연결되어 있는 노드를 방문 처리
    Node* cur = adj[nextNode];
    while (cur != NULL) { push(pq, cur->data); cur = cur->next; }
  }
  printf("%lld\n", res);
  system("pause");
}

