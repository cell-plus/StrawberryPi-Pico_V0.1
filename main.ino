#include <Adafruit_NeoPixel.h>

#define NEOPIXELPIN   24
#define NUMPIXELS    144
#define SENSORPIN     A0
#define TRANSISTORPIN 23

#define SENSOR_THRESHOLD 100  // センサーの閾値
#define COUNT_THRESHOLD 10    // 閾値以下の回数の閾値
#define SENSOR_INTERVAL 5000  // センサー読み取りの間隔（ミリ秒）
#define PUMP_ON_DURATION 60000  // ポンプをONにする時間（ミリ秒）

#define BLUE_THRESHOLD 200  // 青色にする閾値
#define GREEN_THRESHOLD 150  // 緑色にする閾値
#define YELLOW_THRESHOLD 100  // 黄色にする閾値

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);

int count = 0;
unsigned long previousMillis = 0; 
bool pumpState = false;
unsigned long pumpOnTime = 0;

void setup() {
  pixels.begin(); 
  pinMode(TRANSISTORPIN, OUTPUT);
  digitalWrite(TRANSISTORPIN, LOW);
}

void loop() {
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis > SENSOR_INTERVAL) {
    previousMillis = currentMillis;   
    int sensorValue = analogRead(SENSORPIN);
    
    if(sensorValue < SENSOR_THRESHOLD) {
      count++;
    } else {
      count = 0; // データが閾値以上のときはカウントをリセット
    }

    if(count == COUNT_THRESHOLD && !pumpState) {
      pumpState = true;
      pumpOnTime = currentMillis;
      digitalWrite(TRANSISTORPIN, HIGH); // ポンプをONに
    }
    
    if(pumpState && currentMillis - pumpOnTime > PUMP_ON_DURATION) {
      pumpState = false;
      digitalWrite(TRANSISTORPIN, LOW); // ポンプをOFFに
    }
  }
  
  // 土壌センサーの値に応じてNeoPixelの色を変更
  int sensorValue = analogRead(SENSORPIN);
  for(int i=0; i<NUMPIXELS; i++){
    if(sensorValue >= BLUE_THRESHOLD) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 255)); // 青色
    } else if(sensorValue >= GREEN_THRESHOLD) {
      pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // 緑色
    } else if(sensorValue >= YELLOW_THRESHOLD) {
      pixels.setPixelColor(i, pixels.Color(255, 255, 0)); // 黄色
    } else {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // 赤色
    }
    pixels.show();
  }
}
