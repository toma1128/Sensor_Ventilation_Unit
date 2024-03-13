#include <Arduino.h>
#include <ESP32Servo.h>

Servo servo_on;
Servo servo_off;
// 変数設定
float ad_val; // アナログ入力値
int angle;    //動かす度数

const int SENS_PIN = 25;  //センサーのピン
int sensVal = 0;
int crtVal = 0;       //前回の結果を記録しておく変数

int count = 0;

// 初期設定 -----------------------------------------
void setup() {
  Serial.begin(115200);
  //pinMode(32, ANALOG);          //アナログ入力端子設定
  pinMode(SENS_PIN, INPUT_PULLUP);

  // PWM設定（以下のタイマ1つで4チャンネル使用可のため、最大16台の設定が可能）
	//ESP32PWM::allocateTimer(0); // ledcチャンネル 0,1,8,9用タイマ(C Plusではノイズ音が鳴るため非推奨)
  // ESP32PWM::allocateTimer(1); // ledcチャンネル 2,3,10,11用タイマ割当許可
  // ESP32PWM::allocateTimer(2); // ledcチャンネル 4,5,12,13用タイマ割当許可
  // ESP32PWM::allocateTimer(3); // ledcチャンネル 6,7,14,15用タイマ割当許可

  // サーボ設定（使用するサーボ毎に設定）
  servo_on.setPeriodHertz(50);    // 周波数設定（一般的なRCサーボは50Hz）
  servo_on.attach(16, 500, 2400); // サーボ設定（端子番号, 最小角度Dutyパルス幅μs, 最大角度Dutyパルス幅μs）
  servo_off.setPeriodHertz(50);
  servo_off.attach(15, 500, 2400);
  
}

// メイン -------------------------------------------
void loop() {
  sensVal = digitalRead(SENS_PIN); //センサー読み取り

  Serial.println(sensVal);
  if(crtVal != sensVal){
    Serial.print("Sensor Value = ");
    Serial.println(sensVal,BIN);
    if(sensVal == 1){
      Serial.println("on!");
      servo_on.write(90);      // 角度を指定してサーボ動作実行
      delay(1000);
      servo_on.write(0);
    }else{
      Serial.println("停止");
    servo_off.write(90);
    delay(1000);
    servo_off.write(0);
    }
    crtVal = sensVal;
  }
  delay(500); // 遅延時間
}