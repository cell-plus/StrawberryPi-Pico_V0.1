/*-----------------------------------------------------

  StrawberryPi-Pico 
  by STRAWBERRY FARM<<１５>>
  V0.1.0-202501

  Capacitive Soil Moisture Sensor v1.2
    dry : 685
     ↓  RED & Watering
    Level1 : 600  YELLOW_THRESHOLD SENSOR_THRESHOLD
     ↓  YELLOW
    Level2 : 450  GREEN_THRESHOLD
     ↓  GREEN
    Level3 : 350  BLUE_THRESHOLD
     ↓  BLUE
    wet : 320
  
-----------------------------------------------------*/


#include <Adafruit_NeoPixel.h>

#define ONBOARD_NP_PIN 25
#define LINE_NP_PIN 24
#define NUMPIXELS 144
#define SENSORPIN A0
#define TRANSISTORPIN 23

#define SENSOR_THRESHOLD 600    // センサーの閾値
#define COUNT_THRESHOLD 12      // センサー閾値以下の回数の閾値 12
#define SENSOR_INTERVAL 5000    // センサー読み取りの間隔（ミリ秒）
#define PUMP_ON_DURATION 60000  // ポンプをONにする時間（ミリ秒）60000

#define BLUE_THRESHOLD 350    // 青色にする閾値
#define GREEN_THRESHOLD 450   // 緑色にする閾値
#define YELLOW_THRESHOLD 600  // 黄色にする閾値

Adafruit_NeoPixel pixel0(1, ONBOARD_NP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels(NUMPIXELS, LINE_NP_PIN, NEO_GRB + NEO_KHZ800);

int count = 0;
unsigned long previousMillis = 0;
bool pumpState = false;
unsigned long pumpOnTime = 0;

void setup() {
  Serial.begin(9600);  // シリアル通信の初期化
  pixel0.begin();
  pixel0.setBrightness(50);
  pixels.begin();
  pixels.setBrightness(50);
  pinMode(TRANSISTORPIN, OUTPUT);
  digitalWrite(TRANSISTORPIN, LOW);
}

void checkPump(int sensorValue) {
  // ポンプの動作判定関数　一定時間ごとにセンサー値を確認、一定回数閾値を下回った場合、一定時間ポンプON

  unsigned long currentMillis = millis();

  // SENSOR_INTERVAL(ミリ秒)経過するごとにセンサー値を記録
  if (currentMillis - previousMillis > SENSOR_INTERVAL) {
    previousMillis = currentMillis;
    Serial.print("Sensor :");
    Serial.println(sensorValue);

    // 一定回数連続でセンサー閾値を上回ったときにcount++  (ノイズスパイク対策)
    if (sensorValue > SENSOR_THRESHOLD) {
      count++;
      Serial.print("Count :");
      Serial.println(count);
    } else {
      count = 0;
      Serial.print("Count :");
      Serial.println(count);
    }

    // ポンプステータスがOFFかつカウント閾値に達した場合、ポンプON
    if (count == COUNT_THRESHOLD && !pumpState) {
      pumpState = true;
      pumpOnTime = currentMillis;
      Serial.println("Pump ON---------------------------------------------");
      digitalWrite(TRANSISTORPIN, HIGH);
      count = 0;
    }
  }

  if (pumpState) {
    pixel0.setPixelColor(0, pixel0.Color(50, 50, 50));
    pixel0.show();
    delay(100);
  }

  // ポンプステータスがONかつポンプをONにする時間に達した場合、ポンプOFF
  if (pumpState && currentMillis - pumpOnTime > PUMP_ON_DURATION) {
    pumpState = false;
    Serial.println("Pump OFF--------------------------------------------");
    digitalWrite(TRANSISTORPIN, LOW);
    count = 0;
  }
}



void loop() {
  int sensorValue = analogRead(SENSORPIN);  // 土壌センサーの値を取得
  checkPump(sensorValue);                   // ポンプの動作判定

  pixel0.setPixelColor(0, pixel0.Color(0, 0, 0));
  for (int i = 0; i < NUMPIXELS; i++) {
    if (i % 2 == 0) {  // 偶数のピクセルはオフ
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    } else {  // 奇数のピクセルは点灯 センサー値に応じて色を変更
      if (sensorValue <= BLUE_THRESHOLD) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 50));
      } else if (sensorValue <= GREEN_THRESHOLD) {
        pixels.setPixelColor(i, pixels.Color(0, 50, 0));
      } else if (sensorValue <= YELLOW_THRESHOLD) {
        pixels.setPixelColor(i, pixels.Color(50, 50, 0));
      } else {
        pixels.setPixelColor(i, pixels.Color(50, 0, 0));
      }
    }
  }

  pixel0.show();
  pixels.show();  // NeoPixelの変更を一斉に適用
  delay(400);

  checkPump(sensorValue);  // ポンプの動作判定

  if (sensorValue <= BLUE_THRESHOLD) {
    pixel0.setPixelColor(0, pixel0.Color(0, 0, 50));
  } else if (sensorValue <= GREEN_THRESHOLD) {
    pixel0.setPixelColor(0, pixel0.Color(0, 50, 0));
  } else if (sensorValue <= YELLOW_THRESHOLD) {
    pixel0.setPixelColor(0, pixel0.Color(50, 50, 0));
  } else {
    pixel0.setPixelColor(0, pixel0.Color(50, 0, 0));
  }
  for (int i = 0; i < NUMPIXELS; i++) {
    if (i % 2 == 0) {  // 偶数のピクセルは点灯 センサー値に応じて色を変更
      if (sensorValue <= BLUE_THRESHOLD) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 50));
      } else if (sensorValue <= GREEN_THRESHOLD) {
        pixels.setPixelColor(i, pixels.Color(0, 50, 0));
      } else if (sensorValue <= YELLOW_THRESHOLD) {
        pixels.setPixelColor(i, pixels.Color(50, 50, 0));
      } else {
        pixels.setPixelColor(i, pixels.Color(50, 0, 0));
      }
    } else {  // 奇数のピクセルはオフ
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
  }

  pixel0.show();
  pixels.show();  // NeoPixelの変更を一斉に適用
  delay(400);
}
