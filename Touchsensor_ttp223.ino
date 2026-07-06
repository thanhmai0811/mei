/*
 * Touch Sensor TTP223 — Đọc trạng thái chạm cơ bản
 * Board: Arduino Uno
 * Kết nối: VCC→5V, GND→GND, SIG→Pin2
 *
 * Mặc định (không hàn pad): Momentary, Active HIGH
 * SIG = HIGH khi chạm, LOW khi không chạm
 */

const int TOUCH_PIN = 2;
const int LED_PIN   = 13; // LED nội bộ để demo

void setup() {
  Serial.begin(9600);
  pinMode(TOUCH_PIN, INPUT);    // Không cần PULLUP — output tích cực
  pinMode(LED_PIN, OUTPUT);
  Serial.println("=== Touch Sensor TTP223 ===");
  Serial.println("Không chạm vào pad trong 0.5 giây đầu (IC calibrating)");
  delay(600); // Chờ IC calibrate xong
  Serial.println("Sẵn sàng — chạm vào pad!");
}

void loop() {
  int touchVal = digitalRead(TOUCH_PIN);

  if (touchVal == HIGH) {
    digitalWrite(LED_PIN, HIGH); // LED sáng khi chạm
    Serial.println("CHẠM!");
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  delay(50); // Đọc 20 lần/giây
}
//=============================================//
/*
 * Touch Sensor — Interrupt: phát hiện chạm ngay lập tức
 * Board: Arduino Uno
 * Kết nối: VCC→5V, GND→GND, SIG→Pin2
 *
 * Dùng RISING trigger: SIG lên HIGH (= có chạm) → gọi ISR
 */

const int TOUCH_PIN = 2;
const int LED_PIN   = 13;

volatile bool touchEvent = false;
bool ledState = false;

// ISR — gọi khi phát hiện chạm (SIG rising)
void onTouch() {
  touchEvent = true;
}

void setup() {
  Serial.begin(9600);
  pinMode(TOUCH_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  delay(600); // Chờ TTP223 calibrate

  // Trigger ISR khi SIG lên HIGH (RISING edge = bắt đầu chạm)
  attachInterrupt(digitalPinToInterrupt(TOUCH_PIN), onTouch, RISING); //khi mà touchpin bắt đầu nhận đc tính hiệu từ LOW->HIGH thì hàm onTouch sẽ chạy; và lúc đó hàm loop mới bắt đầu chạy

  Serial.println("Touch Interrupt ready. Chạm để toggle LED.");
}

void loop() {
  if (touchEvent) {
    touchEvent = false;              //reset lại touch về ban đầu
    ledState = !ledState;           // Toggle LED //đảo ngược lại trạng thái để bắt dầu lại
    digitalWrite(LED_PIN, ledState ? HIGH : LOW); //toán tử 3 ngôi; điều kiện ? đúng : sai; 
    Serial.print("Chạm! LED: ");
    Serial.println(ledState ? "BẬT" : "TẮT");
  }
}
//==============================================================//
/*
 * Touch Sensor — Phát hiện chạm ngắn vs chạm dài
 * Ngắn (<500ms): toggle LED
 * Dài (>500ms): reset / action khác
 * Board: Arduino Uno
 * Kết nối: VCC→5V, GND→GND, SIG→Pin2
 */

const int TOUCH_PIN   = 2;
const int LED_PIN     = 13;
const int LONG_PRESS_MS = 1000; // 1 giây = "long press"

bool ledState = false;

void setup() {
  Serial.begin(9600);
  pinMode(TOUCH_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  delay(600); // Chờ IC calibrate
  Serial.println("Chạm ngắn: toggle LED | Chạm dài: tắt LED");
}

void loop() {
  // Đợi có chạm (SIG = HIGH)
  if (digitalRead(TOUCH_PIN) == HIGH) {
    unsigned long pressStart = millis();

    // Đợi thả (SIG về LOW) — đo thời gian giữ
    while (digitalRead(TOUCH_PIN) == HIGH) {
      delay(10);

      // Báo hiệu đang hold (sau 800ms)
      if (millis() - pressStart > 800) {
        Serial.print(".");
      }
    }

    unsigned long pressDuration = millis() - pressStart;

    if (pressDuration >= LONG_PRESS_MS) {
      // Chạm dài → tắt LED
      ledState = false;
      digitalWrite(LED_PIN, LOW);
      Serial.println("\nChạm DÀI — LED tắt");
    } else {
      // Chạm ngắn → toggle
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);
      Serial.print("Chạm ngắn (");
      Serial.print(pressDuration);
      Serial.print("ms) — LED: ");
      Serial.println(ledState ? "BẬT" : "TẮT");
    }
  }
}


//=======================================================================================================//
/*Bài 6-5: Lập trình cảm biến chạm điện dung TTP223 gồm 2 cảm biến, chạm cảm biến
led sáng, nếu chạm cảm biến A, tăng số lần thêm 1, chạm cảm biến B, giảm số lần đi
1. Đếm tổng số lần chạm các cảm biến (số lần chạm bắt đầu bằng 0, khi số lần bằng 0,
chạm cảm biến B không giảm, khi số lần bằng 9, chạm cảm biến A không tăng) và
hiển thị số lần bằng led 7 đoạn.
Hiển thị lên Serial monitor thông tin ở dạng sau: “Đã chạm cảm biến: __ , tổng số lần
chạm: __ lần.”*/
int touch1 = 10;
int touch2 = 11;
int led = 9;
int led7[] = {2,3,4,5,6,7,8}; //a,b,c,d,e,f,g
int count = 0;
const byte maled[] = {
  B0111111, // 0
  B0000110, // 1
  B1011011, // 2
  B1001111, // 3
  B1100110, // 4
  B1101101, // 5
  B1111101, // 6
  B0000111, // 7
  B1111111, // 8
  B1101111  // 9
};
void setup() {
  Serial.begin(9600);
  pinMode(touch1,INPUT);
  pinMode(touch2,INPUT);
  pinMode(led,OUTPUT);
  for (int i=0; i<7;i++) {
    pinMode(led7[i],OUTPUT);
  }
  delay(600);
}
void loop() {

  int touchval1 = digitalRead(touch1);
  int touchval2 = digitalRead(touch2);

  if (touchval1 == HIGH) {
    Serial.print("Da cham cam bien 1,");
    digitalWrite(led,HIGH);
    count ++;
    if (count > 9) count = 9;
    for (int i = 0; i<7;i++){
      boolean bitvalue = bitRead(maled[count],i);
      digitalWrite(led7[i],bitvalue);
    }
    Serial.print(" Tong so lan cham la: ");
    Serial.println(count);
    delay(100);
  }
  else if (touchval2 == HIGH) {
    Serial.print("Da cham cam bien 2,");
    digitalWrite(led,HIGH);
    count --;
    if (count < 0) count = 0;
    for (int i = 0; i<7;i++){
      boolean bitvalue = bitRead(maled[count],i);
      digitalWrite(led7[i],bitvalue);
    }
    Serial.print(" Tong so lan cham la: ");
    Serial.println(count); 
    delay(100);
  } else {
        digitalWrite(led,LOW);
  }
  
  delay(600);
}
