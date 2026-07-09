// Định nghĩa chân
int ENA = 5;
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;
int ENB = 6;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void moveForward(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH); //HIGH-LOW +> đi về phía trước; LOW-HIGH: đi lùi
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  digitalWrite(IN1, LOW); //stop
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  moveForward(200); // Tốc độ từ 0-255
  delay(2000);
  stopMotors();
  delay(1000);
}
//==================================STEPPER==========================================================//
#include <Stepper.h>

// Định nghĩa số bước trên mỗi vòng quay của động cơ (Steps per Revolution)
// Hầu hết động cơ NEMA 17 có góc bước 1.8 độ => 360 / 1.8 = 200 bước/vòng
const int stepsPerRevolution = 200;

// Khởi tạo thư viện Stepper
// Thứ tự chân truyền vào hàm rất quan trọng đối với L298N: IN1, IN3, IN2, IN4
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // Cài đặt tốc độ động cơ (vòng trên phút - RPM)
  myStepper.setSpeed(60); // 60 vòng/phút (1 vòng mỗi giây)
}

void loop() {
  // Quay 1 vòng theo chiều thuận
  myStepper.step(stepsPerRevolution);
  delay(1000); // Chờ 1 giây

  // Quay 1 vòng theo chiều ngược lại
  myStepper.step(-stepsPerRevolution);
  delay(1000); // Chờ 1 giây
}
//======================STEPPE_động cơ bước 28BYJ-48_ULN2003============================================//
#include <Stepper.h>

// Động cơ 28BYJ-48 có 2048 bước để hoàn thành 1 vòng quay 360 độ (ở chế độ Full-step)
const int stepsPerRevolution = 2048;

// Khởi tạo thư viện. Thứ tự chân truyền vào LÀ: IN1, IN3, IN2, IN4
// Tương ứng nối trên Arduino: D8, D10, D9, D11
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // Đặt tốc độ cho động cơ (loại này chạy tốt nhất trong khoảng 10 - 14 RPM)
  myStepper.setSpeed(12); // 12 vòng trên phút
}

void loop() {
  // Quay thuận 1 vòng (2048 bước)
  myStepper.step(stepsPerRevolution);
  delay(1000); // Nghỉ 1 giây

  // Quay ngược lại nửa vòng (-1024 bước)
  myStepper.step(-1024);
  delay(1000); // Nghỉ 1 giây
}
