// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 8; // the number of the pushbutton pin
const int relay1 = 0; // the number of the relay1 pin
const int relay2 = 1;
const int relay3 = 2;
const int relay4 = 3;
const int relay5 = 4;
const int relay6 = 5;
const int relay7 = 6;
const int relay8 = 7;

// variables will change:
int buttonState = 0; // variable for reading the pushbutton status

void setup() {
// initialize the relay1,2,3,4 pins as an output:
pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);
pinMode(relay4, OUTPUT);
pinMode(relay5, OUTPUT);
pinMode(relay6, OUTPUT);
pinMode(relay7, OUTPUT);
pinMode(relay8, OUTPUT);
// initialize the pushbutton pin as an input:
pinMode(buttonPin, INPUT);
}

void loop(){
// read the state of the pushbutton value:
buttonState = digitalRead(buttonPin);

// check if the pushbutton is pressed.
// if it is, the buttonState is HIGH:
if (buttonState == HIGH) {
// turn relays on:
digitalWrite(relay1, HIGH);
digitalWrite(relay2, HIGH);
digitalWrite(relay3, HIGH);
digitalWrite(relay4, HIGH);
digitalWrite(relay5, HIGH);
digitalWrite(relay6, HIGH);
digitalWrite(relay7, HIGH);
digitalWrite(relay8, HIGH);
}
else {
// turn relays off:
digitalWrite(relay1, LOW);
digitalWrite(relay2, LOW);
digitalWrite(relay3, LOW);
digitalWrite(relay4, LOW);
digitalWrite(relay5, LOW);
digitalWrite(relay6, LOW);
digitalWrite(relay7, LOW);
digitalWrite(relay8, LOW);
}
}
