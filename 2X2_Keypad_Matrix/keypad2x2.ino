#include <Keypad.h>

const byte ROWS = 2; //two rows
const byte COLS = 2; //two columns
char keys[ROWS][COLS] = {
  {'1','3'},
  {'2','4'},
};
byte rowPins[ROWS] = {2, 3,}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5,}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.println(key);
  }
}
