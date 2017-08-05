// Basic serial communication with ESP8266
// Uses serial monitor for communication with ESP8266
//
//  Pins
//  Arduino pin 2 (RX) to ESP8266 TX
//  Arduino pin 3 to voltage divider then to ESP8266 RX
//  Connect GND from the Arduiono to GND on the ESP8266
//  Pull ESP8266 CH_PD HIGH
//
// When a command is entered in to the serial monitor on the computer 
// the Arduino will relay it to the ESP8266
//
 
#include <SoftwareSerial.h>
SoftwareSerial ESPserial(2, 3); // RX | TX
 int sensorValue;
 String dummy;
void setup() 
{
    Serial.begin(9600);     // communication with the host computer
    //while (!Serial)   { ; }
 
    // Start the software serial for communication with the ESP8266
    ESPserial.begin(9600);  
 
    Serial.println("");
    Serial.println("Remember to to set Both NL & CR in the serial monitor.");
    Serial.println("Ready");
    Serial.println("");    
}
 
void loop() 
{
    // listen for communication from the ESP8266 and then write it to the serial monitor
    sensorValue = analogRead(A0);
    dummy=String(sensorValue);
    Serial.println(dummy);
    Serial.println(sensorValue);
    
    char arr[10];
    arr[0]='c';
    arr[1]='k';
    for(int i=0;i<dummy.length();i++)
     {
      arr[2+i]=dummy[i];
     }
     arr[2+dummy.length()]='\0';
     
    {  ESPserial.write(arr);  }
    delay(1000);
}
