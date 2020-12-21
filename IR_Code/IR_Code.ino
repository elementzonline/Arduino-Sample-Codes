int  obstaclePin = 2;        // This is our input pin
void setup() 
{
  pinMode(obstaclePin, INPUT);
  Serial.begin(9600);  
}
void loop() 
{
  int hasObstacle = digitalRead(obstaclePin);
  
  if (hasObstacle == HIGH)
 
  {
    Serial.print( "Stop something is ahead!!  ");
    Serial.println(hasObstacle);
  }
  else
  {
    Serial.print("Path is clear  ");
    Serial.println(hasObstacle);
  }
  delay(1000);
}

