#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

int timer1;
int timer2;
int person=0;
int day=0;
int flag1=0;
int flag2=0;
int ir1=5; //D1
int ir2=4; //D2
int relay=0; //D3
String value="0";
void setup() {
  Serial.begin(9600);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
  WiFi.begin("wifi name","password");
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(" . . ");
    delay(200);
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  
}

void loop() {
  if(digitalRead(ir1)==LOW && digitalRead(ir2)==LOW){
  day=1;
  person=0;
}
if(digitalRead(ir1)==HIGH && digitalRead(ir2) == HIGH){
  day=0;
}
if(digitalRead (ir1) == LOW && flag1==0){
  timer1 = millis(); 
  flag1=1;
  }
if(digitalRead (ir2) == LOW && flag2==0){
    timer2 = millis(); 
    flag2=1;
    }
if (flag1==1 && flag2==1)
{ 
    if((timer1-timer2)<0){
        person=person+1;
      }
    else if((timer1-timer2)>0)
    {
        person=person-1;
        if(person==-1){
          person=0;
        }
  }
  if (day==1)
  { 
    value="d";
    digitalWrite(relay, LOW); 
    delay(1000);
  }
  if (person>0 && day==0){
    value=String(person);
    digitalWrite(relay, HIGH); 
    delay(1000);
    
  }
  if (person==0 && day==0){
    value=String(person);
    digitalWrite(relay, LOW); 
    delay(1000);
  }
  flag1=0;
  flag2=0;
}
  if (WiFi.status() == WL_CONNECTED) { 
 
    HTTPClient http;  
    String request="http://192.168.1.6/cpsproject/update.php?x=";
    String final_request=request+value;
    http.begin(final_request);  
    int httpCode = http.GET();                                  
    if (httpCode > 0) { 
      String payload = http.getString();   
      Serial.println(payload);             
    }
    http.end();   //Close connection
  }
}
