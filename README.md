# CWNU-Silverfox-HealthMonitering
## 노약자 및 하지 장애인을 위한 원격 헬스케어 보행보조시스템
![ko](https://img.shields.io/badge/lang-ko-red.svg)
![py](https://img.shields.io/badge/lang-py-blue.svg)
<p align="center">
    <img width="700" alt="ardu_rasp" src="https://github.com/MaiBoii/CWNU-Silverfox-HealthMonitering/assets/102716410/84ab6f4c-50c2-443f-aade-6bb0078a4857">
</p>

### FEATURES OF THIS PROJECT
- 사용된 아두이노 모듈
    - `Arduino MEGA`
    - `ONE029 (홀 센서)`: 사용자 이동 거리 측정
    - `NEO-7M (GPS 수신기)`: 사용자 위치 정보 수신
    - `로드셀 + HX711` : 사용자 체중 측정 
    - `TMP36(체온 센서)`: 사용자 실시간 체온 측정
    - `MAX30102(산소포화도 센서)`: 사용자 실시간 심맥박수 및 산소포화도 측정
    - `스피커`: 위급한 상황일 시 스피커로 주변 사람에게 구조 요청 
    - `HC-SR0(초음파 센서)`: 위급 상황 판단 1
    - `GY-61(기울기 센서)`: 위급 상황 판단 2
    
- 아두이노-라즈베리파이 정보 저장 및 전송 
    - Serial Moniter 통신으로 라즈베리파이에서 아두이노 센싱 데이터 수신
    - SQLAlchemy ORM으로 MySQL 로컬 데이터베이스에 생체정보 저장
    - LTE 유심를 삽입한 라우터를 통해 LTE망 접속 후 CloudFlare Tunneling을 통해 지정된 도메인으로 데이터 송신
    - 시리얼 모니터로 읽어온 데이터를 json 형태의 전역변수 SERIAL_DATA에 센서 데이터 할당한 뒤에 당일 자정 1분 전에 DB에 저장 후 전역변수 초기화


- 스마트폰 정보 송수신
    - Flask + pyserial 멀티스레딩를 통해 지정된 도메인에 접속한 보호자의 단말기로 데이터 전송
    - FCM(FireBase Cloud Messaging)으로 위급상황시 푸시알림 전송

---