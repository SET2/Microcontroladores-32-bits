#include <thingspeak2.h>

#define WIFISSID     "XT10406621"   
#define PASSWORD    "565f44581e24"   

#define TOKEN_GENIOT  "G92PS0G6TSTX2UYB"
#define Alarme1       "field1"
#define RETURN_OK        200   

Geniot client(TOKEN_GENIOT);

void setup() 
{
  Serial.begin(9600);
  delay(100);
  client.wifiConnection(WIFISSID, PASSWORD); 
}

void loop() 
{
   static const long interval = 30000;  
   static unsigned long previousMillis = 0, currentMillis;
   currentMillis = millis();

   if(currentMillis - previousMillis >= interval) 
   {
      previousMillis = currentMillis;
      
        //Máximo até 5 add.
      client.add(Alarme1, random(300));
      //client.add(Alarme2, random(300));
        
      if(client.SendMsgRequest())
          {

          if (RETURN_OK == client.iCheckStatus(&Serial)){
            Serial.println("OK.");
          } else {
            Serial.print("Falha no envio.");
          }

      } else {  
        Serial.println("Falha de conexão.");
      }
      
       }
   
}