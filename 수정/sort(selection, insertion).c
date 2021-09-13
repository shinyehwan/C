#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#define SIZE 1000

int a[SIZE];

int swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main(void) {
	int n, min, index;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	/*for (int i = 0; i < n; i++){ // 선택정렬
	  min = INT_MAX;
	  for (int j=i; j<n; j++){
		if(min>a[j]){
		  min = a[j];
		  index = j;
		}
	  }
	  swap(&a[i], &a[index]);
	}
	*/

	for (int i = 0; i < n - 1; i++) { // 삽입정렬
		int j = i;
		while (j >= 0 && a[j] > a[j + 1]) {
			swap(&a[j], &a[j + 1]);
			j--;
		}
	}
	
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	return 0;
}