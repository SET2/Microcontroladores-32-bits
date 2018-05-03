#include <thingspeak2.h>

#define WIFISSID     "XT10406621"   
#define PASSWORD    "565f44581e24"    

#define TOKEN_GENIOT  "G92PS0G6TSTX2UYB"
#define Temperatura   "field1"
#define RETURN_OK     200   
#define LED           D4   
              
Geniot client(TOKEN_GENIOT);

void setup() {

    Serial.begin(115200);
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
  
    pinMode(LED, OUTPUT);      
    digitalWrite(LED, LOW);    
}

void loop() {
    static const long interval = 30000;  
  static unsigned long previousMillis = 0, currentMillis;

  currentMillis = millis();
  if(currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis;
      
      if(RETURN_OK == client.iReadSensorAndCheckStatus(Temperatura, &Serial))
        { 
      
            Serial.print(client.fReadSensorValue());
        
   
        }
  }
          
}