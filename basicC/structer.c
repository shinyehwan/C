#include <stdio.h>
#include<string.h>

typedef struct Student{ // 학생 구조체 정의
  char studentId[10];
  char name[10];
  int grade;
  char major[100];
} Student;


int main(void) {

  
  Student s; // 구조체 변수 선언
  strcpy(s.studentId, "32172274");
  strcpy(s.name, "신예환");
  s.grade = 3;
  strcpy(s.major, "컴퓨터공학과");
  // struct Student s = {"32172274", "신예환", 3, "컴퓨터공학과"};
  printf("학번: %s\n", s.studentId);
  printf("학번: %s\n", s.name);
  printf("학번: %d\n", s.grade);
  printf("학번: %s\n", s.major);
  return 0;
}