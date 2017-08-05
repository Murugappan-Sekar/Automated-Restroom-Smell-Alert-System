
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define FIREBASE_HOST "remotemonitoring-39929.firebaseio.com"
#define FIREBASE_AUTH "3drtrOtCHwNQa6YKxfie9HnffkfDmdD1ChR8qFMt"
#define WIFI_SSID "MurugappanSekar"
#define WIFI_PASSWORD "12345678"

String location="ssn",slash="/";
String path,day,month,year,timegmt,hour,minu,ans;
String gTime,temp;
int spaceCount;
String op;
void setup() {
  Serial.begin(9600);
  // connect to wifi.
  delay(1000);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("guesssiongg");
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  delay(1000);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
  Serial.println("database ok");
}

String getTime() {
  WiFiClient client;
  while (!!!client.connect("google.co.in", 80)) {
    Serial.println("connection failed, retrying...");
  }

  client.print("HEAD / HTTP/1.1\r\n\r\n");
  while(!!!client.available()) {
     yield();
  }

  while(client.available()){
    if (client.read() == '\n') {   
      if (client.read() == 'D') {   
        if (client.read() == 'a') {   
          if (client.read() == 't') {   
            if (client.read() == 'e') {   
              if (client.read() == ':') {   
                client.read();
                String theDate = client.readStringUntil('\r');
                client.stop();
                return theDate;
              }
            }
          }
        }
      }
    }
  }
}
void resolveTime()
{
  spaceCount=0;
  temp="";
  for(int i=0;i<gTime.length();i++)
  {
    if(gTime[i]!=' ')
    {
      temp+=gTime[i];
      continue;
    }
    spaceCount++;
    if(spaceCount==1)
    {
      temp="";
      continue;
    }
    if(spaceCount==2)
    {
      day=temp;
      //Serial.print("day  ");
      //Serial.println(day);
    }
    else if(spaceCount==3)
    {
      month=temp;
      //Serial.print("month  ");
      //Serial.println(month);
    }
    else if(spaceCount==4)
    {
      year=temp;
      //Serial.print("year  ");
      //Serial.println(year);
      hour="";
      hour+=gTime[i+1];
      hour+=gTime[i+2];
      minu="";
      minu+=gTime[i+4];
      minu+=gTime[i+5];
    }
    else if(spaceCount==5)
    {
      timegmt=temp;
      //Serial.print("timegmt  ");
      //Serial.println(timegmt);
    }
    temp="";
  }
}

void loop() {
  //Serial.readString()
  op=Serial.readString();
  if(op.length()>=3)
  {
    int pos=op.length()-1;
    while(op[pos]!='c')
      pos--;
    op=op.substring(pos);
  }
  Serial.println("done");
  Serial.println(op);
  gTime=getTime();
  delay(1000);
  resolveTime();
  path=location+slash+year+slash+month+slash+day+slash+hour;
  ans=minu+op;
  Firebase.pushString(path,ans);
}
