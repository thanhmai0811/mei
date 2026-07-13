void loop() {
  // 1. Đọc và xử lý nút bấm
  if (digitalRead(START_PIN) == LOW) {
    isRunning = true;
  }
  if (digitalRead(STOP_PIN) == LOW) {
    isRunning = false;
  }
  if (digitalRead(RESET_PIN) == LOW) {
    isRunning = false;
    timeCount = 0;
    updateLCD();
  }

  // 2. Đếm thời gian (mỗi 100ms = 0.1s)
  if (isRunning) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 100) {
      previousMillis = currentMillis;
      timeCount++;
      if (timeCount > 9999) timeCount = 0; // Tràn số về 0 (999.9s)
      updateLCD();
    }
  }

  // 3. Liên tục quét và hiển thị lên 4 LED 7 đoạn
  displayTime(timeCount);
}
