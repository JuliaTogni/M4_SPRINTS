#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

//Conectando ao WIFI
const char* SSID = "PEDRO_5G";
const char* PWD = "Augusto1";

//Função que pega do servidor a informação
void getDataFromServer() {
 
    HTTPClient http;
     
    //Iniciando a rota que a função irá buscar
    http.begin("http://192.168.0.200:3000/esp");
    http.addHeader("Content-Type", "application/json");
    
    
    //Criando a váriavel do tipo "StaticJsonDocument" para suportar o formato JSON
    StaticJsonDocument<200> res;
     
    //Verificando o código HTTP recebido
    int httpResponseCode = http.GET();
 
    // Caso tenha funcionado teremos um código HTTP que é maior que 0
    if(httpResponseCode>0){
       
        //resposta que o servidor irá receber
        /*
            Vale lembrar que receberemos uma STRING que segue o formato JSON ou seja
         {
            "chave": "valor"
         }
         
            Para que pegamos apenas o valor precisamos fazer com que essa STRING se torne um JSON (linha 51 e 53)
         */
        
        String response = http.getString();
       
        deserializeJson(res, response);
    
      String resultado = res["resultado"];
      Serial.println(resultado);
    }
     
}

#define led_vermelho 36
#define led_verde 42


void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);

    //Setup dos leds
    pinMode(led_vermelho, OUTPUT); 
    pinMode(led_verde, OUTPUT); 

    // //Conectando ao WIFI
    //   WiFi.begin(SSID, PWD);
    //   while (WiFi.status() != WL_CONNECTED) {
    //     Serial.print("Tentando novamente!");
    //     delay(500);
    //   }

  Serial.println("WiFi connected");
}

void loop() {
  // put your main code here, to run repeatedly:
    //Guardando o retorno da função em uma variável
  WiFi.begin(SSID, PWD);
      while (WiFi.status() != WL_CONNECTED) {
        Serial.print("Tentando novamente!");
        delay(500);
      }

  digitalWrite(led_vermelho, HIGH);
  // getDataFromServer();
  
    //Verificando a resposta e o que será feito dependendo da resposta
  // if (resultado == "X") {
  //   digitalWrite(led_vermelho, HIGH);
  // } else if (resultado == "O") {
  //   digitalWrite(led_verde, HIGH);
  // } else if (resultado == "DEU EMPATE") {
  //   digitalWrite(led_verde, HIGH);
  //   digitalWrite(led_vermelho, HIGH);
  // } else {
  //   digitalWrite(led_verde, LOW);
  //   digitalWrite(led_vermelho, LOW);
  // }
}

