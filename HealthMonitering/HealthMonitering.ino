#include "MyVariables.h"
#include "MyFunctions.h"

InitialValues initialValues;
SoftwareSerial ss(GPS_RXPin, GPS_TXPin);

// // RTC 객체 생성
// RTC_DS3231 rtc;

// 생체 정보 측정 주기 (단위: 밀리초)
const unsigned long measureInterval = 10000; // 1분
unsigned long lastMeasureTime = 0;

// 생체 정보 측정 횟수 저장 변수
int measureCount = 0;


// // 하루 동안 측정을 몇 번 했는지 저장하는 변수
// int day = -1;

void setup() {

  //시리얼 측정 주기 
  Serial.begin(115200);

  //   // RTC 초기화
  // if (!rtc.begin()) {
  //   Serial.println("Couldn't find RTC");
  //   while (1);
  // }

  //   // RTC가 배터리로 백업되는 동안 작동하고 있는지 확인
  // if (rtc.lostPower()) {
  //   Serial.println("RTC lost power, lets set the time!");
  //   rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // 컴파일 시간으로 RTC 설정
  // }

  // // 초기 측정 횟수 및 날짜 설정
  // DateTime now = rtc.now();
  // day = now.day();

  initialValues = measureInitGradient(); // 기울기 초기값 설정

  // GPS 수신기 핀 설정
  ss.begin(115200);

    //초음파 핀 설정
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // //심박수 
  // initializeHeartrate();


  pinMode(HALL_PIN, INPUT);
}

void loop() {

  //   DateTime now = rtc.now();

  // // 하루가 지나면 측정 횟수 초기화
  // if (now.day() != day) {
  //   measureCount = 0;
  //   day = now.day();
  //   distance = 0.0;  // 하루가 바뀔 때 이동 거리 초기화
  // }

  //   // 주기적으로 생체 정보 측정
  // unsigned long currentTime = millis();
  // if (currentTime - lastMeasureTime >= measureInterval) {
  //   lastMeasureTime = currentTime;
    
  //   if (measureCount < 15) {
  //     measureHeartrate_Spo2();
  //     measureTmp();
  //     //measureGradient(initialValues);
  //     //measureDistanceFromHuman();
  //     measureCount++;
  //     Serial.print("Measurements taken today: ");
  //     Serial.println(measureCount);
  //   } else {
  //     //Serial.println("Maximum number of measurements taken for today.");
  //   }
  // }

  // 이동 거리 측정 함수 호출
  checkEmergencySituation();
  measureDistance();
}
