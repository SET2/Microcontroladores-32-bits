/*
VERSÃO API: 5.0 (10-01-2018)
AUTOR: FERNANDO SIMPLICIO
API PARA NODEMCU ESP12

Copyright (c) 2013-2018 Microgenios.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/
#ifndef _GENIOT_NODE_MCU_H_
#define _GENIOT_NODE_MCU_H_

#include <ESP8266WiFi.h>
#include "WiFiUdp.h"
#define TIME_SERVER "pool.ntp.org"
//#define HTTPSERVER "geniot.io"
#define HTTPSERVER "avl-automacao.com.br"
#define HTTPPORT 80

//-----------------------------------------------------------------
//Definições para manter a compatibilidade desta API com as antigas API que foram desenvolvidas.
#define iCheckStatus(x) check(x) 
#define SendMsgRequest() send()
#define iReadSensorAndCheckStatus(x,y) read(x,y)
#define fReadSensorValue() value()
#define SendUpdateRequest(x) update(x)
//-----------------------------------------------------------------

typedef struct Value {
  char  *id;
  char *context;
  float value_id;
  unsigned long timestamp;
} Value;

typedef struct ValueEvent {
  char *id;
  char *value;
} ValueEvent;


class Geniot {
 public:
    Geniot(char* token_geniot, char* event_name_iftt=NULL, char* token_iftt=NULL);
	
    bool send(void);
	bool sendEvent(void);
	bool update(char* id);
	int check(Print *debug=NULL);
    int read(char* id);
	float value(void); 
	String text(void);

	void add(char *, char *);
    void add(char *variable_id, float value);
    void add(char *variable_id, float value, char *ctext);
    void add(char *variable_id, float value, unsigned long timestamp);
    void add(char *variable_id, float value, char *ctext, unsigned long timestamp);
    bool wifiConnection(char *ssid, char *pass);
	unsigned long ntpUnixTime(void);

 private:
    char* _event_name_ifttt;
	char* _token_ifttt;
    char* _token_geniot;
	
    uint8_t maxValues;
	uint8_t maxValues_events;
    uint8_t currentValue;
	uint8_t currentValue_events;
	bool checkStatus(Print *debug);
    Value * val;
	ValueEvent *  events;
	String strText;
    WiFiClient _client;
	String buffer;
	int parseStatus;
	int statusCode;
	WiFiUDP udp;
	float fsensorvalue;
	
};

#endif