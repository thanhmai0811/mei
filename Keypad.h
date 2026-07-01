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
  
}
