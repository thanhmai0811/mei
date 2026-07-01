#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 3;

String reset = "";

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
}

void loop() {
  char key = keypad.getKey();
if(key) {
  if (key == '#') {
    Serial.println(reset);
    reset = "";
  }
  else {
    reset += key;
  }
}

}
