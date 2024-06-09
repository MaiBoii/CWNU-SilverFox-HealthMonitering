// MyFunctions.cpp
// 함수의 구현 부분을 작성한 파일입니다.

#include "MyFunctions.h"
#include "MyVariables.h"
#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include "HX711.h"
#include "spo2_algorithm.h"
#include <RTClib.h>


// GPS 수신기 객체 및 시리얼 통신 객체 생성
extern TinyGPS gps;

// 무게 재기 HX711 객체 생성
HX711 scale;

//심맥박수 센싱 객체 생성
MAX30105 particleSensor;

// Ensure initialValues is recognized
extern InitialValues initialValues;

extern SoftwareSerial ss;

// 위치정보를 업데이트하는 함수
void GpsReceiver() {
  static bool firstRun = true;  // 처음 실행 여부를 확인하는 플래그

  if (firstRun) {
    Serial.println("GPS 수신기가 작동합니다.");
    firstRun = false;  // 첫 실행 후 플래그를 false로 변경
  }

  // GPS 데이터 수신 및 처리
  while (ss.available() > 0) {
    char c = ss.read();
    Serial.print(c);  // GPS 데이터 디버깅 출력
    if (gps.encode(c)) {
      // 위치 정보가 업데이트되었을 때, 정보 출력
      float latitude, longitude;
      unsigned long fix_age;
      gps.f_get_position(&latitude, &longitude, &fix_age);

      // 위치 정보를 JSON 형식으로 출력
      Serial.print("{\"latitude\": \"");
      Serial.print(latitude == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : latitude, 6);
      Serial.println("\"}");
      Serial.print("{\"longitude\": \"");
      Serial.print(longitude == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : longitude, 6);
      Serial.println("\"}");
    }
  }
}

// 사람과의 거리 측정 함수
bool measureDistanceFromHuman() {
  measureDistance();

  // 사람과의 거리 측정 관련 변수 초기화
  long duration;
  float cm;

    // 트리거 핀을 LOW로 설정
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn (ECHO_PIN, HIGH);
  cm = duration / 58.0; 

  //만일 사람이 30cm 이상 기기로부터 멀어졌을 경우
  if ( cm > 30 ){
    Serial.println("30cm 이상 거리에 있음");
    Serial.println(cm);
    return true;
  }
  else {
    Serial.println("30cm 보단 가까이 있음");
   Serial.println(cm);
    return false;
  }
}

//기울기 초깃값 측정
InitialValues measureInitGradient() {
  InitialValues initialValues; // 초기값 측정
  
  initialValues.initialX = analogRead(xPin);
  initialValues.initialY = analogRead(yPin);
  initialValues.initialZ = analogRead(zPin);

  return initialValues;
}

// 기울기 측정 센서
bool measureGradient(InitialValues initialValues) {
  
  int minVal = 265;
  int maxVal = 402;

  double x;
  double y;
  double z;

  int xRead = analogRead(xPin);
  int yRead = analogRead(yPin);
  int zRead = analogRead(zPin);

  int xAng = map(xRead, minVal, maxVal, -90, 90);
  int yAng = map(yRead, minVal, maxVal, -90, 90);
  int zAng = map(zRead, minVal, maxVal, -90, 90);

  // 현재값과 초기값의 차이 계산
  int deltaX = xRead - initialValues.initialX;
  int deltaY = yRead - initialValues.initialY;
  int deltaZ = zRead - initialValues.initialZ;

  // 모듈이 60도 이상 기울어졌을 경우
  if ((abs(deltaX) > 30) || (abs(deltaY) > 30) || (abs(deltaZ) > 30)){
    //Serial.println("기울어짐");
    return true;
  }
  else{
    Serial.println(deltaX);
    Serial.println(deltaY);
    Serial.println(deltaZ);
    Serial.println("기울기 멀쩡함");
    return false;
  }
}

// 거리와 기울기를 측정하여 위급상황인지 판단
void checkEmergencySituation() {

    //위도 경도 측정
    GpsReceiver();
    
    // 거리 측정 함수 호출
    bool distanceFromHuman = measureDistanceFromHuman();

    // 기울기 측정 함수 호출
    bool gradientDetected = measureGradient(initialValues);

    // 둘 다 true를 반환하면 위급 상황으로 판단
    if (distanceFromHuman && gradientDetected) {

      Serial.println("{\"Emergency\": \"True\"}");
      musicStart();
    }
    else {
      //Serial.println("No emergency situation detected.");
    }
}

int hall_value; // 홀센서로 감지한 값(LOW : 자석이 감지됨, HIGH : 자석이 감지되지 않음)
float radius = 0.085; // 바퀴 반지름 : 8.5cm
extern volatile float distance=0; // 환자의 이동거리
extern volatile bool isMagnet = false; // 자석 감지 상태를 유지하기 위한 변수

// 이동거리 측정
void measureDistance() {
  hall_value = digitalRead(HALL_PIN);

  Serial.println(hall_value);
  
  if (isMagnet == true) {
    if (hall_value == HIGH) {
      distance += PI * 2 * radius;
      isMagnet = false;
      Serial.print("{\"Distance\": \"");
      Serial.print(distance);
      Serial.println("\"}");
    }
  } else {
    if (hall_value == LOW) {
      isMagnet = true;
    }
  }
}

// // 인터럽트 서비스 루틴 (ISR)
// void hallSensorISR() {
//   int hall_value = digitalRead(HALL_PIN);
//   if (isMagnet == true && hall_value == HIGH) {
//     distance += PI * 2 * radius;
//     isMagnet = false;
//   } else if (hall_value == LOW) {
//     isMagnet = true;
//   }
// }

// void printDistance() {
//   // 측정된 거리를 출력
//   Serial.print("{'Distance': ");
//   Serial.print(distance);
//   Serial.println("}");
// }

// 산소포화도, 심박수
#define MAX_BRIGHTNESS 255
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
uint16_t irBuffer[100]; 
uint16_t redBuffer[100];
#else
uint32_t irBuffer[100];
uint32_t redBuffer[100];
#endif

int32_t bufferLength; // data length
int32_t spo2; // SPO2 value
int8_t validSPO2; // indicator to show if the SPO2 calculation is valid
int32_t heartRate; // heart rate value
int8_t validHeartRate; // indicator to show if the heart rate calculation is valid

byte pulseLED = 11; 
byte readLED = 13;

int HeartmeasureCount = 0; // 측정 횟수 카운트
bool tempExceeded = false; // 온도 초과 플래그
unsigned long lastTempPrintTime = 0; // 마지막 온도 출력 시간
const unsigned long TempdebounceInterval = 1000; // 온도 디바운스 간격

void initializeHeartrate() {
  pinMode(pulseLED, OUTPUT);
  pinMode(readLED, OUTPUT);

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println(F("MAX30105가 인식되지 않습니다. 연결을 확인해주세요."));
    while (1);
  }

  Serial.println(F("엄지 손가락을 센서 위에 적당한 세기로 눌러주세요."));

  byte ledBrightness = 60; // Options: 0=Off to 255=50mA
  byte sampleAverage = 4; // Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 2; // Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  byte sampleRate = 100; // Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411; // Options: 69, 118, 215, 411
  int adcRange = 4096; // Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);

  bufferLength = 100;

  for (byte i = 0; i < bufferLength; i++) {
    while (particleSensor.available() == false)
      particleSensor.check();

    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();

    particleSensor.nextSample();
  }

  maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
}

void measureHeartrate_Spo2() {
  if (HeartmeasureCount >= 2) return; // 측정 횟수가 4번 이상이면 함수 종료

  for (byte i = 25; i < 100; i++) {
    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();
  }

  for (byte i = 75; i < 100; i++) {
    while (particleSensor.available() == false)
      particleSensor.check();

    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();

    particleSensor.nextSample();
  }
  
  maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);

  if (spo2 == -999 || !validSPO2) {
    Serial.println(F("SPO2 측정이 유효하지 않습니다."));
    return; // 유효하지 않은 경우 측정 횟수 증가하지 않음
  }

  Serial.print("{\"Oxygen\": \"");
  Serial.print(spo2);
  Serial.println("\"}");
  Serial.print("{\"Heartrate\": \"");
  Serial.print(heartRate);
  Serial.println("\"}");

  HeartmeasureCount++; // 유효한 경우에만 측정 횟수 증가
}

int TmpmeasureCount = 0; // 측정 횟수 카운트

void measureTmp() {
  if (TmpmeasureCount >= 2) return; // 측정 횟수가 4번 이상이면 함수 종료

  int tmpValue = analogRead(TMP_PIN);
  float tmpVolt = tmpValue * 5.0 / 1024.0;
  float temperature = tmpVolt * 100 - 60;

  if (temperature <= 20) {
    Serial.println(F("온도 측정이 유효하지 않습니다."));
    return; // 유효하지 않은 경우 측정 횟수 증가하지 않음
  }

  unsigned long currentMillis = millis();

  if (temperature > 20) {
    if (!tempExceeded || (currentMillis - lastTempPrintTime >= TempdebounceInterval)) {
      Serial.print("{\"Temperature\": \"");
      Serial.print(temperature);
      Serial.println("\"}");
    }
  } else {
    Serial.println(F("온도 측정이 유효하지 않습니다."));
  }
  
  TmpmeasureCount++; // 유효한 경우에만 측정 횟수 증가
}

// 스피커 재생 함수
void musicStart() {
  Serial.println("음악이 재생됩니다!");
  pinMode(BUZZER_PIN, OUTPUT); // 스피커 핀 설정

  int melody[] = {
    NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, 
    NOTE_A4, NOTE_A4, NOTE_G4,
    NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4,
    NOTE_D4, NOTE_D4, NOTE_C4
};

  int noteDurations[] = {
    4, 4, 4, 4, 
    4, 4, 2,
    4, 4, 4, 4,
    4, 4, 2
  };

  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    int noteDuration = 1000 / noteDurations[i];
    tone(BUZZER_PIN, melody[i], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
}
