#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>


#define tempoEnvio 500
#define sensor A0
int umidadeLida;
 
const char* ssid = "IOT_Felipe";//Icts
const char* password =  "icts1234";//icts@2018 
const char* host = "192.168.0.91";//IP do servidor
unsigned int port = 1500;//Porta de comunicação com o servidor

//Parametros para fixar o IP do Esp
IPAddress ip(192,168,0,177); 
IPAddress gateway(192,168,0,1); 
IPAddress subnet(255,255,255,0); 

//Porta de comunicação 
WiFiServer wifiServer(80);

//Checa se ainda há rede wifi e tenta reconectar se não houver
int checkWiFi()
{
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Ops! Conexão Wifi Perdida, tentando reconectar....");
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Conectado no WiFi. IP: ");
    Serial.println(WiFi.localIP());  
  }

  return 1;
}

int conectaWifi(){
  Serial.print("Conectando...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado no WiFi. IP: ");
  Serial.println(WiFi.localIP());
  
  return 1;
  
}


void setup() {

  Serial.begin(115200);
  pinMode(sensor, INPUT);
  //Inicia o Wifi e configura a conexão de acordo com os parametros de IP fixo
  WiFi.begin(ssid, password);
 // WiFi.config(ip, gateway, subnet); //Fixar IP

  //Tenta conectar no wifi pela primeira vez
  conectaWifi(); 
  wifiServer.begin();

}

void loop() {

  WiFiClient client;
  umidadeLida  = analogRead(sensor);
  Serial.println(umidadeLida);

  
 //Se houver um servidor disponivel com posse do meu endereço IP para trocar informações, começa a comunicação
  if(client.connect(host, port)){
    Serial.println("O ESP conectou no Server"); 
    while (client.connected()) { 

    client.print(String("oi"));
    Serial.println();
    delay(tempoEnvio);
    
    /*if(client.available()){   
        String line = client.readStringUntil('}');
        //Espaço para tratar comandos recebidos, no caso este esp só envia comandos
                  
    }*/      
   } 
    client.stop();
    Serial.println("Cliente desconectou");
  }
  else
  {
    Serial.println("Falha na conexão com servidor");
    client.stop();  
  }

  checkWiFi();
  delay(1000);

  
}