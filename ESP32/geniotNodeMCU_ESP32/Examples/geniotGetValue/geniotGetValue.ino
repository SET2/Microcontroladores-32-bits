/*
  CÓDIGO COMPATÍVEL COM:
  VERSÃO API: 5.0 (10-01-2018)
  AUTOR: FERNANDO SIMPLICIO
  API PARA NODEMCU ESP12

  [www.geniot.io] 
  Programa de Monitoramento e controle via Internet de Máquinas e Equipamentos. 
  
  Siga os procedimentos abaixo: 
  
  1° Crie uma conta no geniot PRO Industrial pela internet. Acesse: www.geniot.io
  2° Será enviado um email para sua caixa postal. Você deverá confirmar o recebimento do email e criar uma senha. 
  3° Se quiser, faça download do aplicado para SmartPhone Android na loginha do google Play (procure por Microgenios) 
  4° Acesse sua conta em www.geniot.io e crie suas variáveis. 
  5° Agora basta copiar o  número do Token através do painel de sua conta (www.geniot.io) e colar aqui no código.
  Observação: O token é um número único seu e é necessário para realizar a autenticação com o servidor do geniot. Portanto não o forneça para ninguém. 

  Recomendo que assista as seguintes video aulas auto explicativa. 
  https://youtu.be/KCiTzfMimHs
  https://youtu.be/GZ5o5ASP4VM
  https://youtu.be/ZPQgJpVCNn8
  https://youtu.be/7U3TVGyx2fE
  https://youtu.be/p_ndD7cgxGw
  https://youtu.be/c0Vq7iP3Y6g
  https://youtu.be/Ci4BpQxKK8A
  https://youtu.be/Jn4axQBr81I

Documentação da API: 
----------------------------------------------------------------------------
É possível acessar a API assim: 

void add(char *variable_id, float value);               //client.add("S00", 1234.89); 
void add(char *variable_id, float value, char *ctext);        //client.add("S00", 1234.89, "MSG TEXTO"); 
void add(char *variable_id, float value, unsigned long timestamp);  //client.add("S00", 1234.89, "MSG TEXTO", 1508974492); 
----------------------------------------------------------------------------
bool send(void);        //Envia a mensagem armazenada por Geniot.add para o servidor www.geniot.io
----------------------------------------------------------------------------
int check(Print *debug=NULL);     //Verifica se o retorno do servidor foi 200
----------------------------------------------------------------------------
bool update(char* id);  //Atualiza as variáveis armazenadas por geniot.add no servidor www.geniot.io
----------------------------------------------------------------------------
int read(char* id); //Utilizado para Ler uma variável na sua conta www.geniot.io.
Exemplo: 
 if(RETURN_OK == client.read("S00")) {}
----------------------------------------------------------------------------
float value(void);   //Utilizado LOGO APÓS o uso da chamada client.read(...) para ler o valor da variável float.
Exemplo: 
float valor = client.value();  
---------------------------------------------------------------------------
bool update(char* id); //Utilizando para atualizar um campo específico na variável, tal como a Unidade ou o Nome. 
                       //Recomenda-se fazer as atualizações de nomes e unidades via painel do usuário em www.geniot.io
*/

#include "WiFi.h"
#include <geniotNodeMCU_ESP32.h>

#define WIFISSID    " "     //SSID de sua rede WiFi
#define PASSWORD    " "     //Password 

#define TOKEN_GENIOT    " "   //Token para autenticação com o servidor do geniot PRO Industrial. Exemplo: "111fd7a0b90dc035fa7439d8dd11acsb"

/*
 * Para usar a API do geniot as variáveis devem ser chamadas pelo ShortCut ou pelo seu ID. 
 *  Neste exemplo será declarada duas variáveis pelo seu apelido(ShortCut).
 */

//Declara o apelido do sensor de Temperatura como "S00". Necessário escrever os 3 caracteres em MAIÚSCULO.  
#define Temperatura     "S00"   //Esse é o shortcut de sua variável. Essa String foi gerada automaticamente
                                //quando você criou suas variáveis pelo painel www.geniot.io. 
                                //Você verá usar o shortcut que foi criado pelo servidor. Clique no menu Home e confira.  

#define RETURN_OK        200    //Este é o Código de Confirmação da mensagem HTML do servidor. 

Geniot client(TOKEN_GENIOT);

void setup() {

    Serial.begin(9600);
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);

}

void loop() {
    static const long interval = 30000;  //update a cada 30 segundos
    static unsigned long previousMillis = 0, currentMillis;
    
    /*
     *  Realiza a Leitura da Variável Temperatura no Servidor Cloud geniot.
     *  Caso essa variável NÃO tenha sido criada, esta será criada.
     */
    
    currentMillis = millis();

    if(currentMillis - previousMillis >= interval) 
    {
       previousMillis = currentMillis;
      
        if(client.read(Temperatura))
        { 
          if(RETURN_OK == client.check())
          {
            Serial.println(client.value());  //imprime o valor da variável
            Serial.println(client.text());   //imprime a mensagem de texto da variável
          }

        }
    }

          
}