
String voice;
void setup() {
Serial.begin(9600);

  // put your setup code here, to run once:

}

void loop() {
  while(Serial.available()>0)
  {
  delay(10);
  char a=Serial.read();
  voice+=a;

  }
    if(voice.length()>0)
    
    {
      delay(10);
      voice.remove(voice.length()-2);
      Serial.println(voice);
      

      if(voice=="0013947845")
       {
        Serial.println("person1"); 
        delay(1000);
       }
       else if(voice=="0013950454")
       {
        Serial.println("person2");
        delay(1000);
       }
       else
       {
        Serial.println("unknown");  
        delay(1000);
       }
       
       
    }
    voice="";
  // put your main code here, to run repeatedly:

}
