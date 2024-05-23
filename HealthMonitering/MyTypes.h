// MyTypes.h
#ifndef MY_TYPES_H
#define MY_TYPES_H

struct Task {
  unsigned long previousMillis;
  unsigned long interval;
  void (*function)(); // 함수 포인터
}; // 타이머 구조체

struct InitialValues {
  int initialX;
  int initialY;
  int initialZ;
}; // 초기 기울기 값 구조체

#endif
