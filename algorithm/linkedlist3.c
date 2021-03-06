#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int data;
  struct Node *prev;
  struct Node *next;

}Node;

Node *head, *tail;

void insert(int data){
  Node* node = (Node*)malloc(sizeof(Node));
  node->data = data;
  Node* cur;
  cur = head->next;
  while(cur->data < data && cur !=tail)// 넣고자 하는 데이터 보다 보고있는 포인터의 데이터값이 더 작을때 오른쪽으로 이동
  {cur = cur->next;}

  Node* prev = cur -> prev; //삽입할 위치의 앞쪽노드를 prev로 잡아준다
  prev -> next = node;
  node -> prev = prev;
   cur -> prev = node; // 뒤쪽 노드가 cur 겠다.
  node -> next = cur;
  
}
void removeFront(){
  Node* node = head->next;
  head->next = node->next;
  Node* next = node->next;
  next->prev = head;
  free(node);
}

void show(){
  Node* cur = head->next;
  while(cur != tail){
    printf("%d ", cur->data);
    cur = cur->next;
  }
}


int main(void) {
  head = (Node*)malloc(sizeof(Node));
  tail = (Node*)malloc(sizeof(Node));
  head->next = tail;
  head->prev = head;
  tail->next = tail;
  tail->prev = head;
  insert(2);
  insert(1);
  insert(3);
  insert(9);
  insert(7);
  removeFront();
  show();
  system("pause");
   return 0;
}