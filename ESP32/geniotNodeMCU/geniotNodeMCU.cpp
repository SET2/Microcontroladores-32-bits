/*
VERSÃO API: 5.0 (10-01-2018)
AUTOR: FERNANDO SIMPLICIO
API PARA NODEMCU ESP12

Copyright (c) 2013-2016 Microgenios.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shbuffer be
included in buffer copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHbuffer THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "GeniotNodeMCU.h"

/*
 * Construtor
 */
Geniot::Geniot(char* token_geniot, char* event_name_ifttt, char* token_ifttt) {
   
    _token_geniot = token_geniot;
	
    maxValues = 5; 
    currentValue = 0;
    val = (Value *)malloc(maxValues*sizeof(Value));

	maxValues_events = 1; 
    currentValue_events = 0;
	_token_ifttt = token_ifttt;
    _event_name_ifttt = event_name_ifttt;
    events = (ValueEvent *)malloc(maxValues_events*sizeof(ValueEvent));
	
    strText.reserve(50);
    buffer.reserve(2048);
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

bool Geniot::send() {
	parseStatus = 0;
	statusCode = 0;
	
    uint16_t i;
	
    String str;
	str.reserve(50);
	
	if(currentValue == 0) {
	  return false; 
	}
	
    buffer = "[";
    for (i = 0; i < currentValue; ) {
        str = String(((val+i)->value_id), 4);
        buffer += "{\"variable\":\"";
        buffer += String((val + i)->id);
        buffer += "\",\"value\":";
        buffer += str;
		
			String time = "";
			if(String((val+i)->timestamp).length() >= 10)
			{
			  buffer += ",\"timestamp\"";
			  buffer += ":";
			  buffer += String((val+i)->timestamp);
			} 

            if(String((val+i)->context).length() >= 1)
            {
              buffer += ",\"description\"";
              buffer += ":\"";
              buffer += String((val+i)->context);
              buffer += "\"";
            } 

        buffer += "}";
        i++;
        if (i < currentValue) {
            buffer += ","; 
        }
    }
    buffer += "]";
    i = buffer.length();
	
	currentValue = 0;
	
    if (_client.connect(HTTPSERVER, HTTPPORT)) {      
		_client.print(F("POST /things/services/api/v1/collections/value"));		 
		_client.print(F("/?token="));		
		_client.print(_token_geniot);		
        _client.println(F(" HTTP/1.1"));		
        _client.println(F("Host: geniot.io"));			
        _client.println(F("Connection: close"));		
        _client.println(F("Content-Type: application/json"));		
        _client.print(F("Content-Length: "));		 
        _client.println(String(i));		
        _client.println();		
        _client.println(buffer);		
        _client.println();

        Serial.println(buffer); 	
		
	} else {
		return false;
	}
	return true;	
}

bool Geniot::sendEvent() {
	parseStatus = 0;
	statusCode = 0;
	
    uint16_t i;

    String str;
    str.reserve(50);
	
	if(currentValue_events == 0) return false; 
	
    buffer = "[{\"";
    for (i = 0; i < currentValue_events; ) {
        str = String(((events+i)->value));
        buffer += String((events + i)->id);
        buffer += "\":\"";
        buffer += str;
        i++;
        if (i < currentValue_events) {
            buffer += "\",\""; 
        }
		else{
		 buffer += "\"}";
		}
    }
    buffer += "]";
    i = buffer.length();
	
	currentValue_events = 0;
	
    if (_client.connect(HTTPSERVER, HTTPPORT)) {    
		_client.print(F("POST /things/services/api/v1/events/"));
		_client.print(_event_name_ifttt);
		_client.print(F("/"));	 
		_client.print(_token_ifttt);		 
		_client.print(F("/?token="));		
		_client.print(_token_geniot);
        _client.println(F(" HTTP/1.1"));		
        _client.println(F("Host: geniot.io"));			
        _client.println(F("Connection: close"));		
        _client.println(F("Content-Type: application/json"));		
        _client.print(F("Content-Length: "));		 
        _client.println(String(i));		
        _client.println();		
        _client.println(buffer);		
        _client.println();
		
	} else {
		return false;
	}
	return true;
}

bool Geniot::update(char* variable) {
    uint16_t i;
    String buffer;
    String str;
	
	if(currentValue_events == 0) return false; 
	
	buffer += "{\"";
    for (i = 0; i < currentValue_events; ) {	    
        str = String(((events+i)->value));
        buffer += String((events + i)->id);
        buffer += "\":\"";
        buffer += str;		
        i++;
        if (i < currentValue_events) {
            buffer += "\",\""; 
        }
		else{
		buffer += "\"}";
		}

    }
    i = buffer.length();
	
	//Serial.println(buffer);

	currentValue_events = 0;
	
    if (_client.connect(HTTPSERVER, HTTPPORT)) {       
	   _client.print(F("PUT /things/services/api/v1/variables/"));		
       _client.print(variable);		 
	   _client.print(F("/?token="));
	   _client.print(_token_geniot);	
       _client.println(F(" HTTP/1.1"));		
       _client.println(F("Host: geniot.io"));
       _client.println(F("Connection: close"));
       _client.println(F("Content-Type: application/json"));	
       _client.print(F("Content-Length: "));
       _client.println(String(i));		
       _client.println();
       _client.println(buffer);
       _client.println();

	} else {
		return false;
	}
	return true;
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

bool Geniot::checkStatus(Print *debug){
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
            buffer = _client.readString();
        }

        if (debug)
            debug->println(buffer);
        return false;

    }

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

int Geniot::check(Print *debug){
    parseStatus = 0;
    statusCode = 0;
	while (checkStatus(debug));
	return statusCode;
}

int Geniot::read(char* id) {
    if(_client.connect(HTTPSERVER, HTTPPORT)) 
    {	
    	_client.print(F("GET /things/services/api/v1/variables/"));		
    	_client.print(id);		 
    	_client.print(F("/value/?token="));		
    	_client.print(_token_geniot);		
    	_client.println(F(" HTTP/1.1"));		
    	_client.println(F("Host: geniot.io"));			
    	_client.println(F("Connection: close"));		 
    	_client.println();	

    } else {

    	return false;
    }
    return true;     
} 

float Geniot::value(){
    uint16_t bodyPosinit;
    uint16_t bodyPosend;

    if(parseStatus > 1) 
    {

        bodyPosinit = 8 + buffer.indexOf("\"value\":");       
        bodyPosend = buffer.indexOf(",\"timestamp\":");
        fsensorvalue = buffer.substring(bodyPosinit,bodyPosend).toFloat();   

    }

    return fsensorvalue;
}

String Geniot::text(){
    uint16_t bodyPosinit;
    uint16_t bodyPosend;

    if(parseStatus > 1) 
    {
        bodyPosinit = 16 + buffer.indexOf(",\"description\":\"");
        bodyPosend = buffer.indexOf("\",\"unit\"");   
        strText = buffer.substring(bodyPosinit,bodyPosend); 
        return strText;

    }

    return "";
}

/*
 * © Francesco Potortì 2013 - GPLv3 - Revision: 1.13
 *
 * Send an NTP packet and wait for the buffer, return the Unix time
 *
 * To lower the memory footprint, no buffers are bufferocated for sending
 * and receiving the NTP packets.  Four bytes of memory are bufferocated
 * for transmision, the rest is random garbage collected from the data
 * memory segment, and the received packet is read one byte at a time.
 * The Unix time is returned, that is, seconds from 1970-01-01T00:00.
 */
unsigned long Geniot::ntpUnixTime () {
    static int udpInited = udp.begin(123); // open socket on arbitrary port

    // Only the first four bytes of an outgoing NTP packet need to be set
    // appropriately, the rest can be whatever.
    const long ntpFirstFourBytes = 0xEC0600E3; // NTP request header

    // Fail if WiFiUdp.begin() could not init a socket
    if (! udpInited)
        return 0;

    // Clear received data from possible stray received packets
    udp.flush();

    // Send an NTP request
    if (! (udp.beginPacket(TIME_SERVER, 123) // 123 is the NTP port
        && udp.write((byte *)&ntpFirstFourBytes, 48) == 48
        && udp.endPacket()))
            return 0;               // sending request failed

    // Wait for buffer; check every pollIntv ms up to maxPoll times
    const int pollIntv = 150;     // poll every this many ms
    const byte maxPoll = 15;      // poll up to this many times
    int pktLen;               // received packet length
    for (byte i = 0; i < maxPoll; i++) {
        if ((pktLen = udp.parsePacket()) == 48)
            break;
        delay(pollIntv);
    }
    if (pktLen != 48)
        return 0;               // no correct packet received

    // Read and discard the first useless bytes
    // Set useless to 32 for speed; set to 40 for accuracy.
    const byte useless = 40;
    for (byte i = 0; i < useless; ++i)
        udp.read();

    // Read the integer part of sending time
    unsigned long time = udp.read();  // NTP time
    for (byte i = 1; i < 4; i++)
        time = time << 8 | udp.read();

    // Round to the nearest second if we want accuracy
    // The fractionary part is the next byte divided by 256: if it is
    // greater than 500ms we round to the next second; we also account
    // for an assumed network delay of 50ms, and (0.5-0.05)*256=115;
    // additionbuffery, we account for how much we delayed reading the packet
    // since its arrival, which we assume on average to be pollIntv/2.
    time += (udp.read() > 115 - pollIntv/8);
    // Discard the rest of the packet
    udp.flush();
    return time - 2208988800ul;       // convert NTP time to Unix time
}