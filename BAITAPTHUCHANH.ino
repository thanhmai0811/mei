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
