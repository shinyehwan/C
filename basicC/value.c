#include <stdio.h>


/* 값에 의한 전달 방식
void add(int a, int b){
  a = a + b;

}
int main(void) {
  int a = 7;
  add(a,10);
  printf("%d\n", a);
  system("pause");
  return 0;
}*/

// 참조에 의한 전달 방식 -> 값을 전달하는 것이 아니라 변수의 주소를 전달한다. 이러한 방식을 이용하면 원래 변수의 값에 접근하여 값을 변경할 수 있다.

void add(int *a){
  *a = (*a) + 10;
}

int main(void){
  int a = 7;
  add(&a);
  printf("%d\n", a);

  return 0;
}