#include <Stepper.h>

// Số bước để quay hết 1 vòng (28BYJ-48 ~ 2048 bước ở half-step)
const int stepsPerRevolution = 200;

// Khai báo đối tượng Stepper, thứ tự chân theo đúng IN1-IN3-IN2-IN4 
// (lưu ý: thư viện Stepper yêu cầu thứ tự 1-3-2-4, không phải 1-2-3-4!)
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(10); // tốc độ: 10 vòng/phút (nên để thấp, 28BYJ-48 yếu)
}

void loop() {
  // Quay thuận 1 vòng
  myStepper.step(stepsPerRevolution);
  delay(1000);

  // Quay ngược 1 vòng
  myStepper.step(-stepsPerRevolution);
  delay(1000);
}
