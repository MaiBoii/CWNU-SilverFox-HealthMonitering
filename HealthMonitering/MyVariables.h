// MyVariables.h
// 변수 선언만 따로 모아놓은 헤더 파일입니다.
#ifndef MY_VARIABLES_H
#define MY_VARIABLES_H

#include "MyTypes.h" 

#include <SoftwareSerial.h>
#include <Arduino.h>

const int ECHO_PIN = 2; //ECHO 핀 
const int TRIG_PIN = 3; //TRIG 핀 

const int BUZZER_PIN = 9; // 스피커 모듈 핀
const int GPS_RXPin = 11;  //GPS RX 핀 `
const int GPS_TXPin = 12;  //GPS TX 핀 

const int TMP_PIN = A0; // 체온 측정 핀

const int xPin = A1; // x기울기 핀
const int yPin = A2; // y기울기 핀
const int zPin = A3; // z기울기 핀

const int HALL_PIN = 5; //홀 센서 핀

//테스트용 반짝반짝 작은별
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523




#endif // MY_VARIABLES_H