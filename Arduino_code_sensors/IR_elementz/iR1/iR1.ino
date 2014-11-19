#define INPin A1 // Onboard LED
void setup() {
 Serial.begin (9600);

 
  pinMode(INPin, INPUT); // Use LED indicator (if required)
}
int OUT;
void loop()
{
  
  OUT=analogRead(INPin);
  Serial.print(OUT);
  // print a tab between values:
  Serial.print("\n");
}
