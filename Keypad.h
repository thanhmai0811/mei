#include <Keypad.h>

const byte ROWS = 4; //gọi cột
const byte COLS = 3; //gọi dòng

String reset = ""; //sử dụng string vì string là lưu chuỗi các kí tự
String password = "0811"; 

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowsPins[ROWS] = {2,3,4,5}; //nối chân cột với chân arduino
byte colsPins[COLS] = {6,7,8};

Keypad keypad = Keypad(makeKeymap(keys),rowsPins, colsPins,ROWS,COLS); //hàm khởi tạo 

void setup() {
  Serial.begin(9600);
  Serial.println("hay nhap: ");
}
// có thể sau chép từ loop trở lên cho đỡ mất thời gian, từ loop trở xuống tùy chỉnh theo project
void loop() {
  char key = keypad.getKey(); //đọc key từ bàn phím
if(key)  { //kiểm tra xem phím đã ddocjw nhấn hay chưa 
  if (key == '#') { //nếu phím đã nhấn # thì bắt đầu in ra màn hình 
    if (reset == password) { //chức năng nhập mật khẩu
      Serial.println("mat khau chinh xac");

    } else {
      Serial.println("mat khau khong chinh xac");
    }

    reset = ""; //sau khi in reset chuỗi về rỗng để tiếp tục cho vòng lặp tiếp theo
  }
  else { //nếu phím vẫn chưa nhấn thêm thì tiếp tục cộng dồn vô (reset)
    reset += key;
    Serial.print(key);
  }
}
//============================================================================
//bổ sung thêm một tí hàm
void basic(char key) {
  if(key) {
   if (key == '#') {
     Serial.println(reset);
     reset = "";
   }
  }
    else {
      reset += key;
      Serial.print(key);
  }
}
void passwords(char key) {
if(key) {
  if (key == '#') {
    if (reset == password) {
      Serial.println("mat khau chinh xac");
  }
    else {
     Serial.println("mat khau khong chinh xac")
  }
    reset = "";
  }
  else {
    reset += key;
    Serial.print(key);
  }
}
}
void giuphim (char key) {
  if ((int)keypad.getState() ==  PRESSED) {
    if (temp != 0) {
      key = temp;
    }
  }
  if ((int)keypad.getState() ==  HOLD) {
    state++;
    state = constrain(state, 1, n-1);
    delay(holdDelay);
  }
 
  if ((int)keypad.getState() ==  RELEASED) {
    key += state;
    state = 0;
    //Xuất lên Máy tính để xem kết quả
    Serial.println(key);
 
  }

  //===================================================================//
  //source code bai3-4
  /*Bài 3-4: Lập trình giao tiếp keypad điều khiển 5 led theo qui tắc sau:
nhấn 1 → bật led 1 nhấn 2 → tắt led 1
nhấn 3 → bật led 2 nhấn 4 → tắt led 2
nhấn 5 → bật led 3 nhấn 6 → tắt led 3
nhấn 7 → bật led 4 nhấn 8 → tắt led 4
nhấn 9 → bật led 5 nhấn 0 → tắt led 5 
  */
  #include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 3;
const int led[5] = {9,10,11,12,13};
String reset = "";
String password = "0811";

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowsPins[ROWS] = {2,3,4,5};
byte colsPins[COLS] = {6,7,8};

Keypad keypad = Keypad(makeKeymap(keys),rowsPins, colsPins,ROWS,COLS);

void setup() {
  Serial.begin(9600);
  Serial.println("hay nhap: ");
  for (int i = 0; i < 5; i++) {
    pinMode(led[i],OUTPUT);
    digitalWrite(led[i], LOW);
  }
}
void bai3_4(char key) {
  
  if (key) {
    Serial.println(key);
    switch(key) {
      case '1': digitalWrite(led[0], HIGH); break;
      case '2': digitalWrite(led[0], LOW);  break;
      
      case '3': digitalWrite(led[1], HIGH); break;
      case '4': digitalWrite(led[1], LOW);  break;
      
      case '5': digitalWrite(led[2], HIGH); break;
      case '6': digitalWrite(led[2], LOW);  break;
      
      case '7': digitalWrite(led[3], HIGH); break;
      case '8': digitalWrite(led[3], LOW);  break;
      
      case '9': digitalWrite(led[4], HIGH); break;
      case '0': digitalWrite(led[4], LOW);  break;
    }
  }
}
void loop() {
  char key = keypad.getKey();
  bai3_4(key);
}

  delay(100);
}
