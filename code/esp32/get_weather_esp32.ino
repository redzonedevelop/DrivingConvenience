#include <stdint.h>

// === 데이터 구조체 정의 ===
// 자동차 데이터 구조체
struct CarData {
  uint16_t   speed;
  uint16_t    steering_angle;
  uint8_t    mode_driving;
  uint8_t    mode_auto;
  uint8_t    mode_high_beam;
  uint8_t    mode_rain_road;
  uint8_t    mode_corner_light;
  uint8_t    mode_fog_light;
} __attribute__((packed));
//날씨 데이터 구조체
struct Weatherata {
  uint8_t isRaining;
  uint8_t isFog;
} __attribute__((packed));

//저장된 자동차 정보
CarData lastCar;
//저장된 날씨 정보
Weatherata lastWeather;


void setup() {
  Serial.begin(115200);                           // Node-RED 연결
  Serial2.begin(115200, SERIAL_8N1, 16, 17);      // STM32 연결, TX=17, RX=16 핀 설정
}

void loop() {
  //STM32 → ESP32: CarData 수신
  if (Serial2.available() >= sizeof(CarData)) {
    Serial2.readBytes((char*)&lastCar, sizeof(CarData));
    // Node-RED로 바이너리 전송
    Serial.write((char*)&lastCar, sizeof(CarData));
  }

  //Node-RED → ESP32: Weatherata 수신
  if (Serial.available() >= sizeof(Weatherata)) {
    Serial.readBytes((char*)&lastWeather, sizeof(Weatherata));
    //수신 즉시 STM32로 전송
    Serial2.write((char*)&lastWeather, sizeof(Weatherata));
  }
}
