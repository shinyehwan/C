#include <stdio.h>

/* 입력 버퍼로 인해 흔히 발생하는 오류
int main(void) {
  
  int a;
  char c;
  scanf("%d", &a);
  printf("%d\n", a);
  scanf("%c", &c);
  printf("%c\n", c);
  system("pause");
  return 0;
}
*/ //엔터라는 줄바꿈 자체를 바로 문자로 인식하기 때문에

int main(){
  int a; char c;
  scanf("%d", &a);
  printf("%d\n", a);
  int temp; // 한 자씩 받아서 파일의 끝이거나 줄바꿈 문자를 만나며 입력을 멈추므로 항상 입력 버퍼를 비운다.
  while((temp =getchar()) != EOF && temp != '\n'){}

  scanf("%c", &c);
  printf("%c\n", c);
  return 0;
}