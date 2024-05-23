#include "MyVariables.h"
#include "MyFunctions.h"

InitialValues initialValues;
SoftwareSerial ss(GPS_RXPin, GPS_TXPin);

Task tasks[] = {
  {0, 1000, measureTmp},
  // {0, 1000, measureWeight},
  {0, 30000, GpsReceiver},
  {0, 3000, checkEmergencySituation},
  {0,1000, measureHeartrate_Spo2},
  {0,1000, measureDistance}
};

const int numTasks = sizeof(tasks) / sizeof(Task);

void setup() {

  //시리얼 측정 주기 
  Serial.begin(115200);

  initialValues = measureInitGradient(); // 기울기 초기값 설정

  // GPS 수신기 핀 설정
  ss.begin(115200);

  // // HX711 무게 센서 핀 설정
  // scale.begin(DOUT, SCK);
  // scale.set_scale(6000);  // 기본 측정 단위로 보정합니다.
  // scale.tare();

  //심박수 
  initializeHeartrate();
}

void loop() {
  unsigned long currentMillis = millis();

  for (int i = 0; i < numTasks; ++i) {
    if (currentMillis - tasks[i].previousMillis >= tasks[i].interval) {
      tasks[i].previousMillis = currentMillis; // 마지막 실행 시간 업데이트
      tasks[i].function(); // 해당 작업 함수 호출
    }
  }
}
