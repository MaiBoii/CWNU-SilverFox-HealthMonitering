// MyFunctions.h
// 함수 선언만 모아놓은 헤더 파일입니다.
#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#include "MyTypes.h" 

void musicStart(); //음악 시작 함수

InitialValues measureInitGradient(); //기울기 초기값 측정 함수 
bool measureGradient(InitialValues initialValues); // 기울기 최초값 - 현재 기울기 측정 함수

bool measureDistanceFromHuman(); //사람과의 거리 측정 함수

void measureDistance(); //이동거리 측정 함수
void GpsReceiver(); //GPS 정보 수신 함수

void checkEmergencySituation(); //응급 상황 판단 함수

void initializeHeartrate(); //심박수 초기화 함수
void measureHeartrate_Spo2(); //심박수 및 산소포화도 측정 함수

void measureTmp(); //체온 측정 함수
#endif