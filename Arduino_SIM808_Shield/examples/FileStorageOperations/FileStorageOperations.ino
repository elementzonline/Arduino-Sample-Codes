#include <Arduino.h>
#include <SoftwareSerial.h>
#include "ElementzGSM.h"


SoftwareSerial myserialOut(6, 7);
ElementzGSMshield GSM(&myserialOut);
char driveName;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  GSM.begin(9600);
  delay(1500);

  if (GSM.checkSDmode())//Checking Whether SDMODE is activated
  {
    Serial.println("SDMODE activated");
  }
  else
  {
    Serial.println("SDMODE is not activated");
    GSM.prepareForSDcard();//if not activated preparing for SDcard. Do this only one time.
    delay(15000);
    if (GSM.checkSDmode())
    {
      Serial.println("SDMDOE activation success");
    }
  }


  GSM.viewFileStorageMemoryInfo();//You can get an info of memory using this function. This function returns nothing

  driveName = GSM.getDriveLabel(LOCAL);//LOCAL for local sotrage memory.
  Serial.println(driveName);
  driveName = GSM.getDriveLabel(SDCARD);//SDCARD for external drive
  Serial.println(driveName);

  //Use this function to get a list of files and folders inside the drive/path.
  GSM.viewFilelist(driveName, 3); //the second argument means how many files need to be listed
  GSM.createDirectory(driveName, "Test"); //Function for creating a directory
  GSM.viewFilelist(driveName, 4); // you can view the created directory using this function

  GSM.createFile("D:\\Test\\", "testing.txt"); //Function for creating a file
  GSM.viewFilelist("D:\\Test\\", 2); //you can view the created file using this function

  GSM.renameFile("D:\\Test\\testing.txt", "D:\\Test\\test.txt"); //function for renaming a file
  GSM.viewFilelist("D:\\Test\\", 2); //view the change in name

  uint16_t fileSize = GSM.getFileSize("D:\\Test\\test.txt"); //you can know the file size using this function
  Serial.print("File Size = ");
  Serial.println(fileSize);

  GSM.writeTotheBeginningofFile("D:\\Test\\test.txt", "Elementz Engineers", 18, 10); //To write to the beginning of the file use this function
  fileSize = GSM.getFileSize("D:\\Test\\test.txt"); //see the change in file size when data added
  Serial.print("File Size = ");
  Serial.println(fileSize);

  Serial.println(GSM.readFromtheBeginningOftheFile("D:\\Test\\test.txt", 20, 1)); //Use this function to read from thebeginning of a file

  GSM.appendContenttoTheEndoftheFile("D:\\Test\\test.txt", " Guild Pvt Ltd", 14, 10); //To append data to the end of the file use this function
  fileSize = GSM.getFileSize("D:\\Test\\test.txt");//see the change in file size
  Serial.print("File Size = ");
  Serial.println(fileSize);

  Serial.println(GSM.readFromtheBeginningOftheFile("D:\\Test\\test.txt", 40, 1));

  Serial.println(GSM.readFromposition("D:\\Test\\test.txt", 40, 19, 1)); //to read froma particular position use this function.

  GSM.removeFile("D:\\Test\\test.txt"); // to remove any file use this function
  GSM.removeDirectory("D:\\Test");// to remove any directory use this function. Remove the file inside before removing the directory.
}
void loop() {

}

