/*Bài 5-1: Điều khiển LED trang trí theo tín hiệu của biến trở
            + Biến trở nhỏ hơn 25%: sáng từ LED1 → LED8 
            + Biến trở lớn hơn 75%: sáng từ LED8 → LED1
            + Biến trở trong khoảng 25% đến 75%: sáng từ 2 phía (LED1 →LED4 và LED8 → LED5).*/
int led[8] = {2,3,4,5,6,7,8,9};
int pin = A0;

void setup() {
  for (int i = 0; i<8;i++) {
    pinMode(led[i],OUTPUT);
  }
  Serial.begin(9600);
}
void loop() {
  int value = analogRead(pin);
  int pot = map(value,0,1023,0,100);

  if (i<25) {
    for (int i = 0; i<8;i++) {
      digitalWrite(led[i],HIGH);
  } else if (i>75) {
    for (int i = 7; i<=0;i--) {
      digitalWrite(led[i],HIGH);
  }
  } else {
    for (int i = 0; i<4;i++) {
      digitalWrite(led[i],HIGH);
      digitalWrite(led[8-i],HIGH);
  }
}
//=============================================================//
/*
  Bài 5-2: Điều khiển số lượng LED sáng theo biến trở
  - Biến trở >= 20% -> LED1 sáng
  - Mỗi 10% tăng thêm -> sáng thêm 1 LED
*/

const int soLED = 8;                          // Tổng số LED sử dụng
int chanLED[soLED] = {2, 3, 4, 5, 6, 7, 8, 9}; // Chân nối LED
const int chanBienTro = A0;                    // Chân đọc biến trở

void setup() {
  // Thiết lập các chân LED là OUTPUT
  for (int i = 0; i < soLED; i++) {
    pinMode(chanLED[i], OUTPUT);
    digitalWrite(chanLED[i], LOW);
  }
  Serial.begin(9600);
}

void loop() {
  int giaTriADC = analogRead(chanBienTro);      // Đọc giá trị 0 - 1023
  int phanTram = map(giaTriADC, 0, 1023, 0, 100); // Quy đổi ra phần trăm 0 - 100%

  int soLEDsang = 0;

  if (phanTram >= 20) {
    // Từ 20% -> sáng 1 LED, mỗi 10% tiếp theo sáng thêm 1 LED
    soLEDsang = 1 + (phanTram - 20) / 10;
  }

  // Giới hạn không vượt quá số LED thực tế có
  if (soLEDsang > soLED) {
    soLEDsang = soLED;
  }

  // Điều khiển LED: LED nào có chỉ số < soLEDsang thì sáng
  for (int i = 0; i < soLED; i++) {
    if (i < soLEDsang) {
      digitalWrite(chanLED[i], HIGH);
    } else {
      digitalWrite(chanLED[i], LOW);
    }
  }

  // In ra Serial Monitor để kiểm tra
  Serial.print("ADC: ");
  Serial.print(giaTriADC);
  Serial.print(" | Phan tram: ");
  Serial.print(phanTram);
  Serial.print("% | So LED sang: ");
  Serial.println(soLEDsang);

  delay(200); // Đọc và cập nhật mỗi 200ms
}
//========================================================================================//
/*Bài 5-3: Điều khiển LED trang trí theo tín hiệu nút ấn
            + Nhấn 1 lần: LED trang trí sáng từ LED1 → LED8
            + Nhấn 2 lần: LED trang trí sáng từ LED8 → LED1
            + Nhấn 3 lần: Hoạt động như nhấn 1 lần
            + Nhấn 4 lần: Hoạt động như nhấn 2 lần */
/* Bài 5-3: Điều khiển LED trang trí theo tín hiệu nút ấn
 * + Nhấn 1 lần: LED sáng từ LED1 -> LED8
 * + Nhấn 2 lần: LED sáng từ LED8 -> LED1
 * + Nhấn 3 lần: giống nhấn 1 lần
 * + Nhấn 4 lần: giống nhấn 2 lần
 */

#define NUM_LEDS 8
int ledPins[NUM_LEDS] = {2, 3, 4, 5, 6, 7, 8, 9};  // LED1 -> LED8
#define BUTTON_PIN 10

int pressCount = 0;          // đếm số lần nhấn
bool lastButtonState = HIGH; // trạng thái nút trước đó (dùng INPUT_PULLUP)

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  pinMode(BUTTON_PIN, INPUT_PULLUP); // nút nối GND, chưa nhấn = HIGH
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  // Phát hiện cạnh xuống (vừa nhấn nút)
  if (lastButtonState == HIGH && buttonState == LOW) {
    delay(30); // chống dội phím (debounce)
    if (digitalRead(BUTTON_PIN) == LOW) {
      pressCount++;
      if (pressCount > 4) pressCount = 1; // quay vòng lại từ 1

      runPattern(pressCount);

      // Chờ nhả nút trước khi tiếp tục
      while (digitalRead(BUTTON_PIN) == LOW) {
        delay(10);
      }
    }
  }

  lastButtonState = buttonState;
}

// Tắt hết LED
void turnOffAll() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

// Chạy hiệu ứng theo số lần nhấn
void runPattern(int count) {
  turnOffAll();

  if (count % 2 == 1) {
    // Nhấn 1 hoặc 3 lần: LED1 -> LED8
    for (int i = 0; i < NUM_LEDS; i++) {
      digitalWrite(ledPins[i], HIGH);
      delay(200);
    }
  } else {
    // Nhấn 2 hoặc 4 lần: LED8 -> LED1
    for (int i = NUM_LEDS - 1; i >= 0; i--) {
      digitalWrite(ledPins[i], HIGH);
      delay(200);
    }
  }
}







