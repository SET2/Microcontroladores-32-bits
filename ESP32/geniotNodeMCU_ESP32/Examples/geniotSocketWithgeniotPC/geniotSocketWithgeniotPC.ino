/*
 * O geniot PRO Industrial contempla vários softwares: Um desses software é o geniot PRO Industrial para PC que consiste em um
 programa de computador que tem o objetivo de capturar os dados de sensores via Serial, USB, TCP e também dados de CLP, via OPC Server
 Modbus TCP/RTU, e enviar para o servidor em núvem www.geniot.io. 

 Este programa apresenta uma forma simples de fazer uma conexão Socket TCP LOCAL (ou seja, em uma rede interna Intranet) entre o
 geniot (PC) e o NodeMCU. Assim é possível monitorar muitos sensores locais e enviar todas as informações para núvem, via geniot PC.
 ------------------------------------------------
 * Este programa realiza uma conexão socket client com o software geniot para Windows instalado no computador. A cada 30 segundos 
 * o valor do canal AD do ESP8266 será enviado via Socket para o software geniot para Windows. 
 * 
 * Para executar o programa siga os passos a seguir:
 * 1° Instale o software geniot PRO Industrial para PC em seu computador. 
 * 2° Abra o software geniot para Windows como administrador, pois iremos trabalhar como um Socket Server. 
 * Clique com o botão direito mouse sobre o programa e escolha a opção: "Executar como administrador".
 * 3° Em seguida, no geniot clique no menu TCP/IP (imagem de rede) e anote o IP e PORTA. Habilite a opção "TCP/IP Enable" para reiniciar 
 * o geniot como Servidor TCP.
 * 4° Através do menu Wizard do geniot, crie uma variável com o shortcut "S00" e habilite o retorno. Assista aos videos encontrados em geniot.io
 * 5° No programa do ESP8266 configure o SSID e PassWord de sua rede Wifi. 
 * 6° Configure o IP e PORTA do geniot (valores encontrados na 3° Etapa). 
 * 7° Grave o programa no ESP8266. 
 * 8° Para saber se houve a conexão TCP entre o ESP8266 e o software geniot clique no menu 'TCPIP' do geniot (imagem de rede) e monitore
 * a conexão através da caixa de conexão TCP.
 */
#include "WiFi.h"

/*Configuração de sua rede Wifi*/
const char* ssid      = " ";  
const char* password  = " ";

/*Endereço do Servidor geniot*/
const char* serverIP  = "192.168.43.27"; 
const int   serverPort  = 9765;          

/*Variaveis do timerSys Ticks*/
const long intervalo = 30000; //Update a cada 30 segundos.
unsigned long previousMillis = 0; 

String inputString = "";      
boolean stringComplete = false;  

WiFiClient client;

#define LED D4   //Led Azul do ESP-12

void setup() {

  /*Inicializa Serial para debug do programa*/
  Serial.begin(9600);
  delay(10);

  /*Conecta o device a rede WiFi*/
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  /*Tenta se reconectar a rede*/
  WiFi.setAutoReconnect(true);
  
  Serial.println("");
  Serial.println("WiFi conectado");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  ServerConnect();
  
  /*reserva n bytes para armazenar as mensagens de retorno do geniot*/
  inputString.reserve(20);
  
  /*Configura GPIO*/
  pinMode(LED, OUTPUT);     
  digitalWrite(LED, LOW);   //Atenção: No NodeMCU mini o LED azul acende em nível LOW.
}


void loop() {

  unsigned long currentMillis = millis();

      if(client.connected())   //Esta conectado ao servidor geniot?
      {
        if (currentMillis - previousMillis >= intervalo) { //a cada 30 segundos envia a leitura do AD para o geniot
            previousMillis = currentMillis;
            
            int val = analogRead(A0);  //Lê um sensor analogico qualquer e  
            client.print("{S00:");     //Envia para o geniot o valor do AD -> Exemplo: "{S00:1023}\r\n" 
            client.print(val);          
            client.print("}\r\n");
         }
      
          tcpReadBytes(); //Lê os bytes enviados pelo servidor geniot (caso o retorno esteja habilitado no geniot)
          acionaLed();    //Trata o pacote de retorno
      }     
      //Verifica se o Servidor desconectou o cliente ou se a conexão caiu.
      if (!client.connected()) //A conexão caiu? Sim, então precisamos reconectar.
      {
           client.stop();
           delay(2000); 
           /*Tenta se reconectar ao servidor geniot*/
       ServerConnect();  
           
      }
}

boolean ServerConnect()
{
        while(1)
           {
              if (client.connect(serverIP, serverPort)) {
                  Serial.println("Dispositivo conectado."); 
                  break;                               
              } else {                 //falha de conexão com o servidor. 
                  Serial.println("Falha de Conexão.");
                  delay(3000);  //Aguarda 3 segundos para estabilizar a conexão.
              }
           }
  return true;
}

 void tcpReadBytes() {
    while (client.available()) 
    {
      char inChar = (char)client.read();
    
      inputString += inChar; //{"S00":1} 
      if (inChar == '\n') {   //caractere que indica o fim do pacote
        stringComplete = true;
      }
    }
  }

  //Caso a variável S00 seja zerada ou setada pelo smartphone ou pelo próprio software geniot para Windows, o LED Azul do nodeMCU
  //apagará ou acenderá. Para isso faz necessário que o retorno da variavel esteja habilitado no software geniot PC. 
  //Para habilitar o retorno clique np menu Wizard do geniot e marque o campo CheckBox da variável em questão.
  void acionaLed(){
     if (stringComplete) 
     {
        //Modelo: {"S00":1}\r\n onde 1 indica que é para ligar o led.
        if(inputString[0] == '{' && inputString[1] == '\"'
                                 && inputString[2] == 'S'
                                 && inputString[3] == '0' 
                                 && inputString[4] == '0'
                                 && inputString[5] == '\"'
                                 && inputString[6] == ':')
        {
            if(inputString[8] == '}')
            {
              //Liga ou desliga o LED Azul do ESP-12.
              digitalWrite(LED, (((inputString[7]-'0')==0)?1:0)); //ASC - '0' //aciona ou desaciona led (LIGA EM ZERO)
            }
          
        }
  
         inputString = "";
         stringComplete = false;
     }
  }