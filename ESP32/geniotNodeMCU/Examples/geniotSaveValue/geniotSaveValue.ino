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

void add(char *variable_id, float value);  							//client.add("S00", 1234.89); 
void add(char *variable_id, float value, char *ctext);   			//client.add("S00", 1234.89, "MSG TEXTO"); 
void add(char *variable_id, float value, unsigned long timestamp); 	//client.add("S00", 1234.89, "MSG TEXTO", 1508974492); 
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

#include <geniotNodeMCU.h>

#define WIFISSID " "       //SSID de sua rede WiFi
#define PASSWORD " "       //Password 

#define TOKEN_GENIOT  " "  //Instale o App (link acima) para acessar seu token.  LER TEXTO ACIMA. Exemplo: "11fd7a0b90dc035fa7439d8dd11aca4b"

//Para usar a API do geniot as variáveis devem ser chamadas pelo ShortCut ou pelo seu ID. Neste exemplo será declarada duas variáveis pelo seu apelido(ShortCut).
#define Temperatura  "S00"    //Declara o shortcut do sensor de Temperatura como S00 
#define Umidade 	 "S01"    //Declara o shortcut do sensor de Umidade como S01 
							  //Esse é o shortcut de sua variável. Essa String foi gerada automaticamente
                              //quando você criou suas variáveis pelo painel www.geniot.io. 
                              //Você verá usar o shortcut que foi criado pelo servidor. Clique no menu Home e confira.  

#define RETURN_OK        200    //Este é o Código de Confirmação da mensagem HTML do servidor. 


Geniot client(TOKEN_GENIOT);

void setup() {
    Serial.begin(9600);
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);	 
}

void loop() 
{

      static const long interval = 30000;  //Update a cada 30 segundos. 
      static unsigned long previousMillis = 0, currentMillis;
      currentMillis = millis();

	  if(currentMillis - previousMillis >= interval) 
	  {
		   previousMillis = currentMillis;
		   
			//ATENÇÃO: 
			//1° Se a variável não existir no servidor cloud, ou seja, se não for encontrado nenhuma variável com o shortcut "S00", será então
			//criado uma nova variável, contendo o nome da categoria e da variável sendo "S00". 
			//2° Caso a variável "S00" exista, então seu valor será atualizado. 
			
			int value = analogRead(A0);      

			/*
			* Em sua conta www.geniot.io carregue o widget "Display -> LCD-X" para visualizar a mensagem de texto enviada pelo NodeMCU.
			*/  
			
			client.add(Temperatura, value, "Sua Mensagem de Texto"); 
			client.add(Umidade, random(300));   //ATENÇÃO - Máximo 5 adds podem ser usados sequencialmente. 
												

			if (client.send())
	        {

				if (RETURN_OK == client.check(&Serial))
				{
					Serial.println("OK.");
				}
				else {
					Serial.print("Falha no envio.");
				}

			}
			else {
				Serial.println("Falha de conexão.");
			}
			
       }
   
}