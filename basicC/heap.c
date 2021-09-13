#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
int main(void) {
  int *a = malloc(sizeof(int));
  printf("%d\n", a);
  *a = malloc(sizeof(int));
  printf("%d\n", a);
  system("pause");
  return 0;
}*/

//동적 메모리 할당 함수
/*
int main(void){
  int *a =malloc(sizeof(int));
  printf("%d\n", a);
  free(a);
  a = malloc(sizeof(int));
  printf("%d\n", a) ;
  free(a);
  system("pause");
  return 0; 
}
*/

// 동적으로 문자열 처리하기 memset(포인터, 값, 크기) 일괄적인 범위의 메모리를 모두 특정한 값으로 설정하기 위해서는 memset()을 사용

/*
int main(void){
  char *a = malloc(100);
  memset(a, 'A', 100);
  for(int i = 0; i < 100; i++){
    printf("%c ", a[i]);
  }
  system("pause");
  return 0;
}
*/


int main(void){
  int **p = (int**)malloc(sizeof(int*) * 3); // 행
  for(int i = 0; i < 3; i++){
    *(p + i) = (int*)malloc(sizeof(int) * 3); // 열
  }
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      *(*(p + i) + j) = i*3 + j; //특정행에서 몇번째 열인지
    }
  }
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      printf("%d ", *(*(p + i) + j));
    }
    printf("\n");
  }
  system("pause");
  return 0;
}