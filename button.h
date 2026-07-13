#define BUTTON_PIN 10

bool lastButtonState = HIGH;   // luôn để HIGH nếu dùng INPUT_PULLUP

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  // (A) Phát hiện cạnh xuống = thời điểm VỪA nhấn
  if (lastButtonState == HIGH && buttonState == LOW) {
    delay(30); // (B) Debounce
    if (digitalRead(BUTTON_PIN) == LOW) {

      // (C) ----> CHỖ NÀY THAY BẰNG LOGIC RIÊNG CỦA TỪNG BÀI <----
      xuLyKhiNhanNut();

      // (D) Chờ nhả nút, chặn đếm lặp khi giữ
      while (digitalRead(BUTTON_PIN) == LOW) {
        delay(10);
      }
    }
  }

  lastButtonState = buttonState; // (E) Cập nhật trạng thái
}

//=========================HAM NANG CAP (MILLIS)==================================//
#define BUTTON_PIN 10
#define DEBOUNCE_DELAY 30   // thời gian chống dội (ms)

bool lastRawState = HIGH;       // trạng thái đọc thô lần trước
bool stableState = HIGH;        // trạng thái đã xác nhận ổn định
unsigned long lastDebounceTime = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

bool kiemTraNutVuaNhan() {
  bool raw = digitalRead(BUTTON_PIN);
  bool result = false;

  // Nếu tín hiệu thô thay đổi -> reset lại mốc thời gian đếm debounce
  if (raw != lastRawState) {
    lastDebounceTime = millis();
  }

  // Nếu tín hiệu đã đứng yên đủ lâu (không rung nữa)
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    // Nếu trạng thái ổn định thực sự thay đổi so với lần xác nhận trước
    if (raw != stableState) {
      stableState = raw;
      if (stableState == LOW) {
        result = true; // phát hiện 1 lần nhấn hợp lệ
      }
    }
  }

  lastRawState = raw;
  return result;
}

void loop() {
  if (kiemTraNutVuaNhan()) {
    // logic xử lý khi nhấn nút ở đây
  }
//==========================================================================================//
// constants won't change. They're used here to set pin numbers:
const int BUTTON_PIN = 7; // the number of the pushbutton pin

// Variables will change:
int lastState = HIGH; // the previous state from the input pin
int currentState;    // the current reading from the input pin

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the pushbutton pin as an pull-up input
  // the pull-up input pin will be HIGH when the switch is open and LOW when the switch is closed.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // read the state of the switch/button:
  currentState = digitalRead(BUTTON_PIN);

  if(lastState == LOW && currentState == HIGH)
    Serial.println("The state changed from LOW to HIGH");

  // save the last state
  lastState = currentState;
}

}
