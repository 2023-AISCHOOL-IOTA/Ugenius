#include <HX711.h>

// 로드셀 1번
#define DOUT1 25
#define CLK1 26
// 로드셀 2번
#define DOUT2 16
#define CLK2 17
// 로드셀 3번
#define DOUT3 27
#define CLK3 14
// 로드셀 4번
#define DOUT4 13
#define CLK4 12

#define calibration_factor 7050.0

// int btPin = 5;

HX711 scale1;
HX711 scale2;
HX711 scale3;
HX711 scale4;

enum MeasurementStage {
  WAIT,
  MEASURE,
  POST_MEASURE_PAUSE,
};

MeasurementStage stage = WAIT;
unsigned long startTime;
int measureCount;
String rowString;

float weight1;
float weight2;
float weight3;
float weight4;

float currentWeight;

void setup() {
  Serial.begin(115200);

  // pinMode(btPin, INPUT);

  scale1.begin(DOUT1, CLK1);
  scale2.begin(DOUT2, CLK2);
  scale3.begin(DOUT3, CLK3);
  scale4.begin(DOUT4, CLK4);

  scale1.set_scale(calibration_factor);
  scale2.set_scale(calibration_factor);
  scale3.set_scale(calibration_factor);
  scale4.set_scale(calibration_factor);
  
  scale1.tare();
  scale2.tare();
  scale3.tare();
  scale4.tare();

  weight1 = scale1.get_units();
  weight2 = scale2.get_units();
  weight3 = scale3.get_units();
  weight4 = scale4.get_units();

  // PLX-DAQ에서 엑셀 시트에 데이터를 기록하기 위한 설정
  Serial.println("CLEARDATA");
  Serial.print("LABEL");
  for(int i = 1; i <= 100; i++){
    Serial.print(",");
    Serial.print("time_");
    Serial.print(String(i));
  }
  Serial.println();
  Serial.print("DATA");
}

void loop() {
  unsigned long elapsedTime = millis() - startTime;
  
  weight1 = abs(scale1.get_units());
  weight2 = abs(scale2.get_units());
  weight3 = abs(scale3.get_units());
  weight4 = abs(scale4.get_units());
  
  currentWeight = (weight1 + weight2 + weight3 + weight4) / 4.0;

  if (measureCount < 100) {
    if (elapsedTime >= measureCount * 100) {
      Serial.print(",");
      Serial.print(currentWeight);
      measureCount++;
    }
  } else {
    Serial.println();
    Serial.print("DATA");
    measureCount = 0;
    startTime = millis();
  }
}