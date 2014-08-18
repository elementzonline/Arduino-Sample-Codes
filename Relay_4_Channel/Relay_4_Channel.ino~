// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 7; // the number of the pushbutton pin
const int relay1 = 2; // the number of the relay1 pin
const int relay2 = 3;
const int relay3 = 4;
const int relay4 = 5;

// variables will change:
int buttonState = 0; // variable for reading the pushbutton status

void setup() {
// initialize the relay1,2,3,4 pins as an output:
pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);
pinMode(relay4, OUTPUT);
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
}
else {
// turn relays off:
digitalWrite(relay1, LOW);
digitalWrite(relay2, LOW);
digitalWrite(relay3, LOW);
digitalWrite(relay4, LOW);
}
}
