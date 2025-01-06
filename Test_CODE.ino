#include <Adafruit_NeoPixel.h>

#define NEOPIXELPIN   24
#define NUMPIXELS    144
#define SENSORPIN     A0
#define TRANSISTORPIN 23

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); 
  pinMode(TRANSISTORPIN, OUTPUT);
  digitalWrite(TRANSISTORPIN, LOW);
}

void loop() {
  int count = 0;
  int sensorValue = 0;
  for(int i = 0; i < 10; i++) {
    sensorValue = analogRead(SENSORPIN);
    if(sensorValue < 100) {
      count++;
    }
    delay(5000); // 5秒待つ
  }
  
  if(count == 10) {
    for(int i=0; i<NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // ピクセルを全て赤色に
    }
    pixels.show();
    delay(5000); // 5秒待つ
    
    digitalWrite(TRANSISTORPIN, HIGH); // ポンプをONに
    delay(60000); // 60秒待つ
    
    digitalWrite(TRANSISTORPIN, LOW); // ポンプをOFFに
  }

  // 土壌センサーの値に応じてNeoPixelの色を変更
  for(int i=0; i<NUMPIXELS; i++){
    if(sensorValue >= 200) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 255)); // 青色
    } else if(sensorValue >= 150) {
      pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // 緑色
    } else if(sensorValue >= 100) {
      pixels.setPixelColor(i, pixels.Color(255, 255, 0)); // 黄色
    } else {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // 赤色
    }
    pixels.show();
    delay(100);
  }
}
