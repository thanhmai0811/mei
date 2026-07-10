//===============================================BAI1==================================================//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Mảng 7 led (chỉ số từ 0 đến 6)
int led[] = {6, 7, 8, 9, 10, 11, 12};
LiquidCrystal_I2C lcd(0x20, 16, 2); // Hãy chắc chắn địa chỉ LCD của bạn là 0x3E
int analogIn = A0;

void setup() {
  lcd.init();
  lcd.backlight();
  
  for (int i = 0; i < 7; i++) {
    pinMode(led[i], OUTPUT);
  }
  // Không cần pinMode cho chân Analog đầu vào
}

void turnon(int percent) {
  // Xóa ký tự cũ tại vị trí in số Chương trình (Cột 15 dòng 1)
  lcd.setCursor(15, 1);
  lcd.print(" "); 

  if (percent < 30) {
    lcd.setCursor(15, 1);
    lcd.print("1");
    for (int i = 0; i < 7; i++) {
      digitalWrite(led[i], HIGH);
      delay(500);
      digitalWrite(led[i], LOW);
    }
  }
  else if (percent > 60) {
    lcd.setCursor(15, 1);
    lcd.print("2");
    for (int i = 6; i >= 0; i--) {
      digitalWrite(led[i], HIGH);
      delay(500);
      digitalWrite(led[i], LOW);
    }
  }
  else {
    lcd.setCursor(15, 1);
    lcd.print("3");
    
    // Thuật toán chạy từ giữa ra cho 7 LED (Tâm là led[3])
    // Bước 0: Bật led[3]
    // Bước i: Bật cặp led[3-i] và led[3+i]
    for (int i = 0; i <= 3; i++) {
      if (i == 0) {
        digitalWrite(led[3], HIGH);
        delay(500);
        digitalWrite(led[3], LOW);
      } else {
        digitalWrite(led[3 - i], HIGH);
        digitalWrite(led[3 + i], HIGH); // i max = 3 => 3+3 = 6 (hợp lệ)
        delay(500);
        digitalWrite(led[3 - i], LOW);
        digitalWrite(led[3 + i], LOW);
      }
    }  
  }  
}

void loop() {
  // SỬA: Phải dùng analogRead để lấy giá trị biến trở
  int GiaTriBienTro = analogRead(analogIn);
  int percent = map(GiaTriBienTro, 0, 1023, 0, 100);
  
  lcd.setCursor(1, 0);
  lcd.print("Bien tro: ");
  
  // SỬA: Xóa khoảng trống trước khi in phần trăm để tránh lỗi gối ký tự
  lcd.setCursor(11, 0);
  lcd.print("   "); 
  lcd.setCursor(11, 0);
  lcd.print(percent);
  
  lcd.setCursor(14, 0);
  lcd.print("%");
  
  lcd.setCursor(1, 1);
  lcd.print("Chuong Trinh: ");
  
  turnon(percent);
}
//==============================================================BAI2========================================//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
long duration;
int distance;
int led[] = {2,3,4,5,6,7,8,9};
int echo = 11;
int trig = 10;
LiquidCrystal_I2C lcd(0x20,16,2);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode (echo,INPUT);
  digitalWrite(echo,LOW);
  pinMode (trig,OUTPUT);
  for (int i=0; i<8;i++) {
    pinMode(led[i],OUTPUT);
    digitalWrite(led[i],LOW);
  }
}
void loop() {
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  duration = pulseIn(echo,HIGH);
  distance = 0.034*(duration/2);
  lcd.setCursor(1,0);
  lcd.print ("distance: ");
  lcd.setCursor(11,0);
  lcd.print (distance);
  Serial.println(distance);

  int count;


  if (distance >= 20) {
    count = (distance/10) -1;
    if (count > 8) count = 8;
    for (int i =0; i<count;i++) {
      digitalWrite(led[i],HIGH);
    }
    for (int a = 7; a >= count; a--) {
      digitalWrite(led[a],LOW);
    }
  count = 0;
  }
  else {
    for (int i =0; i<8;i++) {
      digitalWrite(led[i],LOW);}
  }
  delay(1000);
}
//=================================================bai3======================================================//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BUTTON_PIN 10
#define DEBOUNCE_DELAY 30   // thời gian chống dội (ms)

bool lastRawState = HIGH;       // trạng thái đọc thô lần trước
bool stableState = HIGH;        // trạng thái đã xác nhận ổn định
int count;
unsigned long lastDebounceTime = 0;
int led[] = {2,3,4,5,6,7,8,9};

LiquidCrystal_I2C lcd(0x20,16,2);

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  for (int i =0; i<8;i++) {
    pinMode(led[i],OUTPUT);
    digitalWrite(led[i],LOW);
  }
  Serial.begin(9600);
}

bool kiemTraNutVuaNhan() {
  bool raw = digitalRead(BUTTON_PIN);
  bool result = false;

  if (raw != lastRawState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (raw != stableState) {
      stableState = raw;
      if (stableState == LOW) {
        result = true; 
        count ++;
      }
    }
  }

  lastRawState = raw;
  return result;
}

void loop() {
  if (kiemTraNutVuaNhan()) {
    int chuongtrinh = count%4;
    lcd.setCursor(1,0);
    lcd.print("So lan: ");
    lcd.setCursor(9,0);
    lcd.print(count);
    Serial.println(chuongtrinh);
    lcd.setCursor(1,1);
    lcd.print("Chuong trinh: ");

    for (int i=0; i<8;i++) {digitalWrite(led[i],LOW); } //reset lai led

    if (chuongtrinh == 1) {
      for (int i=0; i<8;i++) {
        lcd.setCursor(14,1);
        lcd.print("1");
        digitalWrite(led[i],HIGH);
        delay(200);
      }
    }
    else if (chuongtrinh == 2) {
        lcd.setCursor(14,1);
        lcd.print("2");
      for (int i = 0; i<8; i++) {
        digitalWrite(led[7-i],HIGH);
        delay(200);
      }
    }
    else if (chuongtrinh == 4) {
              lcd.setCursor(14,1);
        lcd.print("4");
      for (int i = 0; i < 5; i++) {
        digitalWrite(led[3-i],HIGH);
        digitalWrite(led[4+i],HIGH);
        delay(200);
      }
    }
    else if (chuongtrinh == 3) {
              lcd.setCursor(14,1);
        lcd.print("3");
      for (int i = 0; i < 5; i++) {
        digitalWrite(led[7-i],HIGH);
        digitalWrite(led[i],HIGH);
        delay(200);
      }
    }
    else {
              lcd.setCursor(14,1);
        lcd.print("0");
      for (int i=0; i<8;i++) {
        digitalWrite(led[i],LOW);
        delay(200);
      }      
    }
  delay(500);
  // các việc khác vẫn chạy song song bình thường, ví dụ:
  // capNhatLED();
  // doCamBien();
  } }
