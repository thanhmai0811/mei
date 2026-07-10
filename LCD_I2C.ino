#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Đổi 0x27 thành địa chỉ bạn quét được ở bước 3
LiquidCrystal_I2C lcd(0x27, 16, 2);  // (địa chỉ, số cột, số hàng)

void setup() {
  lcd.init();       // Khởi động LCD
  lcd.backlight();  // Bật đèn nền (nếu không gọi, màn hình sẽ tối)

  lcd.setCursor(0, 0);   // Cột 0, hàng 0 (hàng trên)
  lcd.print("Xin chao!");

  lcd.setCursor(0, 1);   // Cột 0, hàng 1 (hàng dưới)
  lcd.print("Arduino I2C LCD");
}

void loop() {
  // Không cần làm gì nếu chỉ hiện chữ tĩnh
}
