void loop() {
  if (Serial.available() > 0) {
    String lenh = Serial.readStringUntil('\n');  // đọc đến khi gặp Enter
    lenh.trim();  // xóa khoảng trắng/ký tự \r thừa ở đầu-cuối
    Serial.print("Lenh nhan: ");
    Serial.println(lenh);

    if (lenh == "ON") {
      digitalWrite(LED_BUILTIN, HIGH);
    } else if (lenh == "OFF") {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
