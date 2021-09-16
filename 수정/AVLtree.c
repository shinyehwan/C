#include<stdio.h>
#include<stdlib.h>


// AVL 트리의 정의
int getMax(int a, int b) {
	if (a > b) return a;
	return b;
}

typedef struct{
	int data;
	int height; // 높이를 저장해야 시간 복잡도를 보장할 수 있음.
	struct Node* leftChild;
	struct Node* rightChild;
}Node;


//AVL 트리의 높이 계산 함수

int getHeight(Node *node) {
	if (node == NULL) return 0;
	return node->height;
}

// 모든 노드는 회전을 수행한 이후에 높이를 다시 계산
void setHeight(Node *node) {
	node->height = getMax(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
}

//균형인수를 구하는 코드
int getDifference(Node* node) {
	if (node == NULL) return 0;
	Node *leftChild = node->leftChild;
	Node *rightChild = node->rightChild;
	return getHeight(leftChild) - getHeight(rightChild);
}

//AVL 트리의 LL회전
Node *rotateLL(Node *node) {
	Node *leftChild = node->leftChild;
	node->leftChild = leftChild->rightChild; // 노드의 왼쪽자식을 왼쪽자식의 오른쪽 자식으로 만든다
	leftChild->rightChild = node; // 왼쪽자식의 오른쪽자식을 node로 설정한다
	return leftChild; // leftchild는 이후에 setHeight()를 수행
}

//AVL 트리의 RR회전(LL회전을 반대로 수행)
Node *rotateRR(Node *node) {
	Node *rightChild = node->rightChild;
	node->rightChild = rightChild->leftChild; // 노드의 오른쪽자식을 오른쪽자식의 왼쪽 자식으로 만든다
	rightChild->leftChild = node; // 오른쪽자식의 왼쪽자식을 node로 설정한다
	return rightChild; // rightchild는 이후에 setHeight()를 수행
}


//AVL 트리의 LR회전
Node *rotateLR(Node *node) {
	Node *leftChild = node->leftChild;
	node->leftChild = rotateRR(leftChild);
	return rotateLL(node);
}

//AVL 트리의 RL회전(반대)
Node *rotateRL(Node *node) {
	Node *rightChild = node->rightChild;
	node->rightChild = rotateLL(rightChild);
	return rotateRR(node);
}

//AVL 트리의 균형잡기
Node *balance(Node *node) {
	int difference = getDifference(node);
	if (difference >= 2) {
		if (getDifference(node->leftChild) >= 1) {
			node = rotateLL(node);
		}
		else {
			node = rotateLR(node);
		}
	}
	else if (difference <= -2) {
		if (getDifference(node->rightChild) <= -1) {
			node = rotateRR(node);
		}
		else {
			node = rotateRL(node);
		}
	}
	setHeight(node);
	return node;
}

//AVL트리의 삽입
Node *insertNode(Node *node, int data) {
	if (!node) {
		node = (Node*)malloc(sizeof(Node));
		node->data = data;
		node->height = 1;
		node->leftChild = node->rightChild = NULL;

	}
	else if (data < node->data) {
		node->leftChild = insertNode(node->leftChild, data);
		node = balance(node);
	}
	else if (data > node->data) {
		node->rightChild = insertNode(node->rightChild, data);
		node = balance(node);
	}
	else {
		printf("데이터 중복이 발생했습니다. \n");
	}
	return node;
}

//AVL트리의 출력함수 (세로방향 출력)
Node *root = NULL;

void display(Node *node, int level) {
	if (node != NULL) {
		display(node->rightChild, level + 1);
		printf("\n");
		if (node == root) {
			printf("Root: ");
		}
		for (int i = 0; i < level && node != root; i++) {
			printf("      ");
		}
		printf("%d(%d)", node->data, getHeight(node));
		display(node->leftChild, level + 1);

	}
}

int main(void) {
	root = insertNode(root, 7);
	root = insertNode(root, 6);
	root = insertNode(root, 5);
	root = insertNode(root, 3);
	root = insertNode(root, 1);
	root = insertNode(root, 9);
	root = insertNode(root, 8);
	root = insertNode(root, 12);
	root = insertNode(root, 16);
	root = insertNode(root, 18);
	root = insertNode(root, 23);
	root = insertNode(root, 21);
	root = insertNode(root, 14);
	root = insertNode(root, 15);
	root = insertNode(root, 19);
	root = insertNode(root, 20);
	display(root, 1); printf("\n");
	system("pause");
}