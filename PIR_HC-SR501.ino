Code Polling Đơn Giản — Arduino Uno
/*
 * PIR HC-SR501 — Phát hiện chuyển động bằng polling
 * Board: Arduino Uno
 * Kết nối: VCC→5V, GND→GND, OUT→Pin2
 *
 * QUAN TRỌNG: Sau khi cấp điện, chờ 30-60 giây để sensor khởi động
 * OUT HIGH = phát hiện chuyển động
 * OUT LOW  = không có chuyển động
 */

const int PIR_PIN = 2;

// Trạng thái trước đó — để phát hiện thay đổi (không in liên tục)
bool lastState = false;

void setup() {
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);

  // Đợi PIR khởi động
  Serial.println("Khởi động PIR HC-SR501...");
  Serial.println("Chờ 30 giây để sensor ổn định...");
  for (int i = 30; i > 0; i--) {
    Serial.print(i); Serial.print("s ");
    delay(1000);
    if (i % 10 == 0) Serial.println();
  }
  Serial.println("\nSẵn sàng phát hiện chuyển động!");
  Serial.println("====================================");
}

void loop() {
  bool currentState = (digitalRead(PIR_PIN) == HIGH);

  // Chỉ in khi trạng thái thay đổi — tránh spam Serial
  if (currentState != lastState) {
    if (currentState) {
      Serial.print("[");
      Serial.print(millis() / 1000);
      Serial.println("s] >>> PHÁT HIỆN CHUYỂN ĐỘNG! <<<");
    } else {
      Serial.print("[");
      Serial.print(millis() / 1000);
      Serial.println("s] Không có chuyển động");
    }
    lastState = currentState;
  }

  delay(50); // Polling mỗi 50ms
}
Code Interrupt — Arduino Uno (Tiết Kiệm CPU)
/*
 * PIR HC-SR501 — Phát hiện chuyển động bằng interrupt
 * Board: Arduino Uno
 * Kết nối: VCC→5V, GND→GND, OUT→Pin2 (INT0)
 *
 * Interrupt: không cần polling liên tục — MCU làm việc khác, chỉ
 * bị ngắt khi PIR thay đổi trạng thái. Tiết kiệm CPU, phản ứng nhanh hơn.
 */

const int PIR_PIN = 2; // Pin 2 = INT0 trên Arduino Uno

volatile bool motionDetected = false;
volatile bool motionEnded    = false;

// Interrupt khi OUT lên HIGH (bắt đầu phát hiện)
void onMotionStart() {
  motionDetected = true;
}

// Interrupt khi OUT xuống LOW (hết phát hiện)
void onMotionEnd() {
  motionEnded = true;
}

void setup() {
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);

  // CHANGE: kích hoạt interrupt khi pin thay đổi HIGH ↔ LOW
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), []() {
    if (digitalRead(PIR_PIN) == HIGH) {
      motionDetected = true;
    } else {
      motionEnded = true;
    }
  }, CHANGE);

  Serial.println("PIR HC-SR501 Interrupt Mode");
  Serial.println("Chờ 30s warmup...");
  delay(30000);
  Serial.println("Sẵn sàng!");
}

void loop() {
  // Xử lý flag từ interrupt trong main loop (không làm việc nặng trong ISR)
  if (motionDetected) {
    motionDetected = false;
    Serial.print("["); Serial.print(millis()/1000); Serial.println("s] CHUYỂN ĐỘNG PHÁT HIỆN!");
    // Thêm: bật đèn, gửi MQTT, log...
  }

  if (motionEnded) {
    motionEnded = false;
    Serial.print("["); Serial.print(millis()/1000); Serial.println("s] Kết thúc chuyển động");
  }

  // MCU có thể làm việc khác ở đây mà không cần delay dài
  delay(10);
}
