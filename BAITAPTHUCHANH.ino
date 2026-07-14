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
//=======================================BAI7=================================//
/*ài 7: Hệ thống thu thập thông tin về nhiệt độ và độ ẩm của đối tượng điều khiển bao 
gồm: Arduino Uno, cảm biến DHT 11, mô đun 4 led 7 đoạn. Lắp mạch và lập trình 
điều khiển hiển thị thông số thu thập nhiệt độ và độ ẩm theo qui tắc sau:  
+ Hiển thị luân phiên nhiệt độ, độ ẩm sau mỗi 5s  
+ Hiển thị nhiệt độ (số nguyên) tại led 7 đoạn số thứ 1 và thứ 2, hiển thị độ ẩm tương 
đối (số nguyên phần trăm) tại led 7 đoạn số thứ 3 và thứ 4. */

#include <DHT.h>
#include <TM1637Display.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define CLK 3
#define DIO 2

DHT dht(DHTPIN, DHTTYPE);
TM1637Display display(CLK,DIO);

void setup() {
  Serial.begin(9600);
  dht.begin();
  display.setBrightness(0x0f);
}
void loop() {
  delay(2000);

  float humidity = dht.readHumidity();
  display.showNumberDec(humidity,false,2,0);
  float tempC = dht.readTemperature();
  display.showNumberDec(tempC,false,2,2);

}
//==========================================  BAI10 =========================================================//
#include <Wire.h>
#include <TM1637Display.h>
#include <LiquidCrystal_I2C.h>

//7 SEGMENT LED_MODULE 7 LED
#define CLK 3
#define DIO 2
TM1637Display display(CLK,DIO); 

LiquidCrystal_I2C lcd(0x20,16,2); //LCD

//button
const int start = 6;
const int in = 7;
const int out = 8;
int laststate1 = HIGH;
int laststate2 = HIGH;
int laststate3 = HIGH;
int currentstate1,currentstate2,currentstate3;

//millis()
unsigned long previousmillis = 0;
const long interval = 100;

int effect;
int count = 0;

void setup() {
  display.setBrightness(0x0f);
  lcd.init();
  lcd.backlight();

  pinMode(start,INPUT_PULLUP);
  pinMode(in,INPUT_PULLUP);
  pinMode(out,INPUT_PULLUP);
}

void loop() {
  currentstate1 = digitalRead(start);
  currentstate2 = digitalRead(in);
  currentstate3 = digitalRead(out);

  if(laststate1 ==LOW && currentstate1 == HIGH) {
    effect = 1;   
  }
  else if(laststate2 ==LOW && currentstate2 == HIGH) {
    effect = 2;
  }
  else if(laststate3 ==LOW && currentstate3 == HIGH) {
    effect = 3;  
  }
  laststate1 = currentstate1;
  laststate2 = currentstate2;
  laststate3 = currentstate3;
  if(effect == 1) {
    display.showNumberDec(0);
    lcd.clear();
    lcd.setCursor(1,1);
    lcd.print("So nguoi: 0");
    effect = 0;
    delay(50);
  }
  else if (effect == 2) {
    count++;
    display.showNumberDec(count);

    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("co nguoi vao");
    lcd.setCursor(1,1);
    lcd.print("so nguoi: ");
    lcd.setCursor(11,0);
    lcd.print(count);
    effect = 0;
    delay(50);
  }
  else if(effect == 3) {
    count--;
    lcd.clear();
    if (count < 0) {
      count = 0;
      lcd.setCursor(1,0);
      lcd.print("DA HE NGUOI");
    } else {
      lcd.setCursor(1,0);
      lcd.print("co nguoi ra");
    }
    display.showNumberDec(count);
    lcd.setCursor(1,1);
    lcd.print("so nguoi: ");
    lcd.setCursor(11,0);
    lcd.print(count);
    effect = 0;
    delay(50);
  }
}
