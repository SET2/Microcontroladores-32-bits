/*
geniotNodeMCU API v2.
Copyright (c) 2013-2016 Microgenios.

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

geniotNodeMCU API v2.

*/

#include "thingspeak2.h"

/*
 * Construtor
 */
Geniot::Geniot(char* token_geniot, char* event_name_ifttt, char* token_ifttt) {
   
    _token_geniot = token_geniot;
	
    maxValues = 5; 
    currentValue = 0;
    val = (Value *)malloc(maxValues*sizeof(Value));

	maxValues_events = 5; 
    currentValue_events = 0;
	_token_ifttt = token_ifttt;
    _event_name_ifttt = event_name_ifttt;
    events = (ValueEvent *)malloc(maxValues_events*sizeof(ValueEvent));
	
}


void Geniot::add(char *variable_id, float value) {
    return add(variable_id, value, NULL, NULL);
}

void Geniot::add(char *variable_id, float value, char *ctext) {
    return add(variable_id, value, ctext, NULL);   
}
void Geniot::add(char *variable_id, float value, unsigned long timestamp) {
    return add(variable_id, value, NULL, timestamp);
}
void Geniot::add(char *variable_id, float value, char *ctext, unsigned long timestamp) {
    (val+currentValue)->id = variable_id;
    (val+currentValue)->value_id = value;
    (val+currentValue)->context = ctext;
    (val+currentValue)->timestamp = timestamp;
    currentValue++;
    if (currentValue>maxValues) {
        Serial.println(F("Max 5 consecutives variables."));
        currentValue = maxValues;
    }
}

void Geniot::add(char *ifttt_field, char* str) {
    (events+currentValue_events)->id = ifttt_field;
    (events+currentValue_events)->value = str;
    currentValue_events++;
    if (currentValue_events>maxValues_events) {
        Serial.println(F("Max 5 fields."));
        currentValue_events = maxValues_events;
    }
}

bool Geniot::wifiConnection(char* ssid, char* pass) {
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    WiFi.setAutoReconnect(true);
    Serial.println(F("WiFi connected"));
    Serial.println(F("IP address: "));
    Serial.println(WiFi.localIP());
}


bool Geniot::SendMsgRequest() {
	
    uint16_t i=0;
    String all;
	all.reserve(300);

    all = "{\"";
    all += String((val + i)->id);
    all += "\":"; 
    all += String(((val+i)->value_id), 4);
	all += "}";
      
    i = all.length();
	
	currentValue = 0;
	
    if (_client.connect(HTTPSERVER, HTTPPORT)) {      
		_client.print(F("POST /update.json?"));		 
		_client.print(F("api_key="));		
		_client.print(_token_geniot);		
        _client.println(F("&results=1 HTTP/1.1"));		
        _client.println(F("Host: api.thingspeak.com"));			
        _client.println(F("Connection: close"));		
        _client.println(F("Content-Type: application/json"));		
        _client.print(F("Content-Length: "));		 
        _client.println(String(i));		
        _client.println();		
        _client.println(all);			
        _client.println();
	
		
	} else {
		return false;
	}
	return true;
	
}


bool Geniot::checkStatus(Print *debug)
{

	if (!_client.connected()) {
		if (debug)
			while(_client.available())
				debug->print((char)_client.read());
										
		_client.flush();
		_client.stop();
		return false;
	}
	if (!_client.available())
		return true;
	char c = _client.read();
	if (debug)
		debug->print(c);
	switch(parseStatus) {
	case 0:
		if (c == ' ') parseStatus++; break;  // skip "HTTP/1.1 "
	case 1:
		if (c >= '0' && c <= '9') {
			statusCode *= 10;
			statusCode += c - '0';
		} else {
			parseStatus++;
		}
	}
	return true;
}

int Geniot::iCheckStatus(Print *debug)
{
	while (checkStatus(debug));
	return statusCode;
}


int Geniot::iReadSensorAndCheckStatus(char* id, Print *debug) 
{
	  if(_client.connect(HTTPSERVER, HTTPPORT)) {	
			_client.print(F("GET /channels/316058/fields/1.json?api_key="));				 
			_client.print(F("YKUN5J01LEJ9CGCZ&results=1"));		
			_client.println(F(" HTTP/1.1"));		
			_client.println(F("Host: api.thingspeak.com"));			
			_client.println(F("Connection: close"));		 
			_client.println();		
	  } else {
			return false;
	  }

	while (checkStatus2(debug));

	return statusCode;          

} 


bool Geniot::checkStatus2(Print *debug)
{
	String response;
	response.reserve(1024);
	uint16_t bodyPosinit;
	uint16_t bodyPosend;

	if (!_client.connected()) {				
		_client.flush();
		_client.stop();
		return false;
	}
	if (!_client.available())
		return true;

	if(parseStatus > 1) 
	{
		while (_client.available()) {
			response = _client.readString();
		}

		if (debug)
			debug->println(response);

		bodyPosinit =  response.indexOf("entry_id");
		response = response.substring(bodyPosinit);
		bodyPosinit = 11 + response.indexOf(",\"field1\":\"");		
		bodyPosend = response.indexOf("\"}]}");
		debug->println(response.substring(bodyPosinit,bodyPosend));
		fsensorvalue = response.substring(bodyPosinit,bodyPosend).toFloat();
		return false;

	}

	char c = _client.read();

	switch(parseStatus) 
	{
		case 0:
			if (c == ' ') parseStatus++; break;  // skip "HTTP/1.1 "
		case 1:
			if (c >= '0' && c <= '9') {
				statusCode *= 10;
				statusCode += c - '0';
			} else {
				parseStatus++;
			}
	}

	return true;
}

float Geniot::fReadSensorValue()
{
  return fsensorvalue;
}
