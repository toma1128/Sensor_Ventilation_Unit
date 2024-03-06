#include <Arduino.h>
#include <ESP32Servo.h>

Servo servo1;
// 変数設定
float ad_val; // アナログ入力値
int angle;    //動かす度数

int sensPin = 2;   //センサーのピン
int sensVal;
int crtVal;

// 初期設定 -----------------------------------------
void setup() {
  Serial.begin(115200);
  pinMode(32, ANALOG);          //アナログ入力端子設定

  // PWM設定（以下のタイマ1つで4チャンネル使用可のため、最大16台の設定が可能）
	ESP32PWM::allocateTimer(0); // ledcチャンネル 0,1,8,9用タイマ(C Plusではノイズ音が鳴るため非推奨)
  // ESP32PWM::allocateTimer(1); // ledcチャンネル 2,3,10,11用タイマ割当許可
  // ESP32PWM::allocateTimer(2); // ledcチャンネル 4,5,12,13用タイマ割当許可
  // ESP32PWM::allocateTimer(3); // ledcチャンネル 6,7,14,15用タイマ割当許可

  // サーボ設定（使用するサーボ毎に設定）
  servo1.setPeriodHertz(50);    // 周波数設定（一般的なRCサーボは50Hz）
  servo1.attach(22, 500, 2400); // サーボ設定（端子番号, 最小角度Dutyパルス幅μs, 最大角度Dutyパルス幅μs）
  
}

// メイン -------------------------------------------
void loop() {
  angle = 60;               // 角度指定
  servo1.write(angle);      // 角度を指定してサーボ動作実行（「最小角度Dutyパルス幅時間μs」以下の場合は角度として扱われ、それ以外はパルス幅μsとして扱われます。）

  delay(1000);

  ad_val = analogRead(32);  // アナログ入力値（0〜4095）を取得
    angle = map(ad_val, 0, 4095, 0, 180);  // アナログ値 （0〜4095）→ 角度（0゜〜180゜）換算
    servo1.write(angle);      // 角度を指定してサーボ動作実行（「最小角度Dutyパルス幅時間μs」以下の場合は角度として扱われ、それ以外はパルス幅μsとして扱われます。）



  sensVal = digitalRead(sensPin); //センサー読み取り
  if(crtVal != sensVal){
    Serial.print("Sensor Value = ");
    Serial.println(sensPin,BIN);

    angle = 60;               // 角度指定
    servo1.write(angle);      // 角度を指定してサーボ動作実行（「最小角度Dutyパルス幅時間μs」以下の場合は角度として扱われ、それ以外はパルス幅μsとして扱われます。）

  delay(1000);

  ad_val = analogRead(32);  // アナログ入力値（0〜4095）を取得
    angle = map(ad_val, 0, 4095, 0, 180);  // アナログ値 （0〜4095）→ 角度（0゜〜180゜）換算
    servo1.write(angle);

    crtVal = sensVal;
  }

  // シリアルモニタ出力（角度、Dutyパルス幅時間μs）※使用する場合は有効にしてdelay時間長くする。
  // Serial.printf("Angle : %d'  Pulse Width(us) : %d\n", servo1.read(), servo1.readMicroseconds());
  delay(1000); // 遅延時間
}