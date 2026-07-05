//HƯỚNG DẪN SỬ DỤNG HC-SR04//
const int trigPin = 9;
const int echoPin = 10;

long duration;
float distance;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop()
{
  //===============TẠO XUNG=============//
  //reset lại chân trig về LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  //bắt đầu phát sóng siêu âm
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //chạy trong 10us; yêu cầu bắt buộc là 10us dựa trên datasheet của nhà phát hành
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); //sau khi chân trig phát tính hiệu thì chân echo có nhiệm vụ là nhận sóng được dội lại;
/*Sensor
))))))))))   Hộp
trig ------------->|
              |
echo <-------------|
===============================================================
pulseIn(pin, value);
pulseIn(pin, value, timeout);
=> Nếu đặt value là HIGH, hàm pulseIn() sẽ đợi đến khi tín hiệu đạt mức HIGH, khởi động bộ đếm thời gian. Khi tín hiệu nhảy xuống LOW, bộ đếm thời gian dừng lại. và ngược lại
=> Nếu tín hiệu luôn ở một mức HIGH/LOW cố định thì sau khoảng thời gian timeout, hàm pulseIn() sẽ dừng bộ đếm thời gian và trả về giá trị 0.
  timeout được tính bằng đơn vị micro giây. Giá trị mặc định của timeout là 60.106 tương ứng với 1 phút.
  Giá trị tối đa là 180.106 tương ứng với 3 phút. timeout có kiểu dữ liệu là unsigned long
*/
  distance = duration * 0.034 / 2;  //tính quảng đường đi; Tốc độ của âm thanh trong không khí là 340 m/s 

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}



//===============================BÀI TẬP THỰC HÀNH ===================//
/* Bài 6-1: Lập trình sử dụng cảm biến HC-SR04 đo khoảng cách đến vật cản và điều
khiển mảng 8 led theo chương trình:
+ Khoảng cách < 30 cm: Chương trình 1: Bật led chạy từ led1 → led8.
+ Khoảng cách > 80 cm: Chương trình 2: Bật led chạy từ led8 → led 1.
+ Khoảng cách từ 30 đến 80cm: Chương trình 3: Bật/ tắt 8 led với chu kỳ 1s.
Hiển thị ra Serial Monitor thông tin theo dạng sau: “Khoảng cách __ cm −> Chương
trình __” tương ứng với khoảng cách đo được.*/

int led[] = {4,5,6,7,8,9,10,11};
int trig = 2;
int echo = 3;

void setup() {
  Serial.begin(115200);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
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

  int duration = pulseIn(echo,HIGH);
  int distance = 0.034*(duration/2);
  Serial.println("khoang cach ");
  Serial.print(distance);
  Serial.print(" cm");
  khoangcach(distance);
  Serial.println("Chuong trinh ");
  for (int i =0; i<8;i++) {
    digitalWrite(led[i],LOW);}
  delay(1000);

}
void khoangcach(int distance) {
  if (distance < 30) {
    for (int i =0; i<8;i++) {
      digitalWrite(led[i],HIGH);
      delay(200);
    }
  }
  else if (distance > 80) {
    for (int i=7; i>=0;i--){
      digitalWrite(led[i],HIGH);
      delay(200);
    }
  } else {
    for (int i=7; i>=0;i--){
      digitalWrite(led[i],HIGH);   
  }
    delay(1000);
    for (int i=7; i>=0;i--){
      digitalWrite(led[i],LOW);
    }
  }
}
//============================================================//
/*Bài 6-2: Lập trình sử dụng cảm biến HC-SR04 cảnh báo va chạm bằng tín hiệu màu
led theo qui tắc:
+ Khoảng cách > 60 cm, an toàn, bật 1 led xanh (led vàng, đỏ tắt).
+ Khoảng cách từ 30 đến 60 cm, cảnh báo, bật 2 led vàng, tắt led xanh, đỏ.
+ Khoảng cách < 30 cm, nguy hiểm, bật 3 led đỏ, tắt led xanh, vàng.

Hiển thị ra Serial Monitor thông tin theo dạng: “Khoảng cách __ cm. trạng thái an
toàn/cảnh báo / nguy hiểm” tương ứng với khoảng cách đo được*/

int led[] = {4,5,6};
int trig = 2;
int echo = 3;
void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo,INPUT);
  for (int i=0; i<3;i++) {
    pinMode(led[i],OUTPUT);
    digitalWrite(led[i],LOW);
  }
  Serial.begin(115200);
}
void loop() {
  digitalWrite(trig,LOW);
  delayMicroseconds(2);

  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  int duration = pulseIn(echo,HIGH);
  int distance = 0.034*(duration/2);
  Serial.print("Khoang cach ");
  Serial.print(distance);
  hienthi(distance);
  Serial.println();
  delay(1000);
  for (int i=0; i<3;i++) {
    digitalWrite(led[i],LOW);
  }
  delay(500);
}
void hienthi(int distance) {
  if (distance > 60) {
    digitalWrite(led[0],HIGH);
    Serial.print(" trang thai an toan");
  }
  else if (distance < 30) {
    digitalWrite(led[2],HIGH);
    Serial.print(" trang thai canh cao");
  }
  else {
    digitalWrite(led[1],HIGH);
    Serial.print(" trang thai nguy hiem");
  }
}

/*Bài 6-3: Lập trình sử dụng cảm biến HC-SR04 hiển thị khoảng cách theo số lượng
led bật theo qui tắc:
+ Khoảng cách = 20 cm, bật 1 led.
+ Mỗi 10cm tiếp theo: bật thêm 1 led.
+ Tổng số led bật lớn nhất: 8 led.
Hiển thị ra Serial Monitor thông tin theo dạng: “Khoảng cách __ cm. Số led bật __”
tương ứng với khoảng cách đo được.*/

int led[] = {4,5,6,7,8,9,10,11};
int trig = 2;
int echo = 3;
int count = 0;

void setup() {
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  for (int i =0; i<8;i++) {
    pinMode(led[i],OUTPUT);
    digitalWrite(led[i],LOW);
  }
  Serial.begin(115200);
}
void loop() {
  digitalWrite(trig,LOW);
  delayMicroseconds(2);

  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  int duration = pulseIn(echo,HIGH);
  int distance = 0.034*(duration/2);

  if (distance >= 20) {
    int count = (distance/10) - 1;
    if (count > 8) count = 8;
    effect(count);
    
  }
  else { //distance <20 thi khong den nao sang
    for (int i =0; i<8;i++) {
      digitalWrite(led[i],LOW);
  }
  }
//print
  Serial.print("Khoang cach ");
  Serial.print(distance);
  Serial.print("cm. ");
  Serial.print("So led bat ");
  Serial.print(count);
  Serial.println();
  delay(500);

  //rese led
  for (int i =0; i<8;i++) {
    digitalWrite(led[i],LOW);
  }      

}
void effect(int count) {
  for (int i = 0; i < count;i++) {
    digitalWrite(led[i],HIGH);
  }
  count = 0;
}
