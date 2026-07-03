/*Bài 4-2: Lắp mạch và lập trình điều khiển độ sáng của đèn led theo giá trị đọc từ biến
trở bằng phương pháp băm xung PWM. Hiển thị trên Serial Monitor các thông tin sau:

+ Giá trị biến trở (phần trăm)
+ Giá trị điện áp đầu ra trên chân điều khiển LED (tính theo V)*/
int analog = A0;
int led = 8;
void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int value = analogRead(analog);
  int POT = map(value,0,1023,0,100);
  int V = map(value,0,1023,0,5);
  int valueled = map(value,0,1023,0,255);
  analogWrite (led,valueled);

  Serial.println ("Gia tri bien tro(%): ");
  Serial.println (POT);
  Serial.println ("Gia tri dien ap(V): "); 
  Serial.println (V);     
  delay(500);
}
/*Bài 4-3: Viết chương trình điều khiển tốc độ nháy của đèn led bằng giá trị biến trở,
chu kỳ bật / tắt led từ 0,1s (tương ứng với giá trị biến trở bằng 1023) đến 1s (tương
ứng với giá trị biến trở bằng 0). Hiển thị trên Serial Monitor thông tin sau:
+ Giá trị biến trở ở dạng phần trăm.
+ Chế độ bật / tắt LED hiện hành
+ Thời gian một chu kỳ (bằng thời gian bật + thời gian tắt)*/
int analog = A0;
int led = 8;
void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int value = analogRead(analog);
  float sight = map(value,0,1023,1000,100);
  int period = sight/2;
  pinMode(led,HIGH);
  delay(period);
  pinMode(led,LOW);
  delay(period);
}
/*Bài 4-4: Lập trình điều khiển chế độ bật tắt 7 LED (các chân 2→8 trên Uno) theo giá
trị biến trở và hiển thị chế độ hiện thời trên Serial Monitor.
Giá trị biến trở < 30% → chế độ 1: Bật lần lượt từ trái → phải (2→8)
Giá trị biến trở > 70% → chế độ 2: Bật lần lượt từ phải → trái (8→2)
Giá trị biến trở 31% - 69% → chế độ 3: Bật lần lượt từ led giữa sang hai phía (5→8 và
5→2)
Hiển thị trên Serial Monitor các thông tin sau:
+ Giá trị biến trở
+ Chế độ hiện hành.*/
int analogpin = A0;
int led[7] = {2,3,4,5,6,7,8};
void setup() {
  for (int i = 0; i <7; i++) {
    pinMode(led[i],OUTPUT);
  }
  Serial.begin(9600);
}
void loop() {
  int value = analogRead(analogpin);
  int pot = map(value,0,1023,0,100);
  Serial.println(pot);
  if (pot < 30) {
    for (int i = 0; i < 7; i++) {
      digitalWrite(led[i],HIGH);
      delay(500);
    }
  }
  else if (pot > 70) {
    for (int i = 6; i >= 0; i--) {
      digitalWrite(led[i],HIGH);
      delay(500);
    }
  
  }
  else {
    for (int i = 0; i <= 3; i++) {
        digitalWrite(led[3 - i], HIGH); // Chạy ngược về phía 2
        digitalWrite(led[3 + i], HIGH); // Chạy xuôi về phía 8
        delay(500);
    }
  }
  delay(500);
  for (int i = 0; i<= 7; i++) {
  digitalWrite(led[i],LOW);
    }
}

