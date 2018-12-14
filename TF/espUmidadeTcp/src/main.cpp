#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <WiFiClient.h>
#include <IPAddress.h>


#define UDP_PORT    5555

#define tempoEnvio  500
#define sensor      0
#define bomba       13

int umidadeLida;
float setPoint = 45;
int ligou = 0;
int ultimoLigou = 0;
 
const char* ssid = "Icts";//Icts
const char* password =  "icts@2018";//icts@2018 
const char* host = "192.168.0.68";//IP do servidor a ser encontrado via broadcast
unsigned int port = 1500;//Porta de comunicação com o servidor

//Parametros para fixar o IP do Esp
/*IPAddress ip(192,168,0,177); 
IPAddress gateway(192,168,0,1); 
IPAddress subnet(255,255,255,0);*/


//Porta de comunicação 
WiFiServer wifiServer(80);

char dadoAnterior = '0';
char buff[100];

int tipoComando(char dado1){
  
  if(dado1 == '4')
    return bomba;
  else
    return 255;
}

char tipoComandoChar(int porta){
  if(porta == sensor)
    return '1';
  else if(porta == bomba)
    return '4';
  else
    return 'Ç';
}

//Função para mudar o status da porta com valores em char, terceira posição do formato pacote
int ioChar(char dado2){
  if(dado2 == '0')
    return LOW;    
  else
    return HIGH;  
}


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

float converteUmidade(int valorAnalog){  
    return (((1024 - (float)valorAnalog)/1024) * 2.8 * 100); 
}

//Esta função retorna o valor da posição do vetor dos ultimos estados do respectivo IO
int posVetUltimo(char dado1)
{
    if(dado1 == '1')//Sensor
        return 0;
    if(dado1 == '2')//Bomba
        return 1;
}

//Aqui é feita a leitura do comando e o respectivo acionamento é feito
String tcpAcionaIO(String comando){
    
  int porta = tipoComando(comando[1]);
  int io = ioChar(comando[2]);  

  if(porta == 255)
    return ("Este comando nao surtiu efeito: " + comando);
  else{
    digitalWrite(porta, io);
    return (String("{") + String(comando[1]) + String(comando[2]) + String(dadoAnterior) + "}");  
  }
}

float convertCharUmidade(String comando)
{
  float convertido;
  if(comando[1] == '3')
  {
      convertido = (float)(comando.substring(2).toFloat());
      Serial.println(convertido);
      return convertido;
  }
  else return 120;
}

//pegar a umiade convertida e salvar na EEPROM para ser lida na variavel setpoint
void setaUmidade()
{

}

void comparaSetPoint(){
    umidadeLida  = analogRead(sensor);
    Serial.println(umidadeLida);
      if(converteUmidade(umidadeLida) < (setPoint - 2))
      {
          digitalWrite(bomba, LOW);
          ligou = 1;
      }        
      else
      {
          digitalWrite(bomba, HIGH);
          ligou = 0;
      }
      
}

String comandoBomba(){
  if(ligou)
    return ("{21}");
  else
    return ("{20}");
}


void setup() {

  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(bomba, OUTPUT);
  //Inicia o Wifi e configura a conexão de acordo com os parametros de IP fixo
  WiFi.begin(ssid, password);
 // WiFi.config(ip, gateway, subnet); //Fixar IP

  //Tenta conectar no wifi pela primeira vez
  conectaWifi(); 
  wifiServer.begin();
  digitalWrite(bomba, HIGH);


}

void loop() {

  WiFiClient client;
  comparaSetPoint();
 //Se houver um servidor disponivel com posse do meu endereço IP para trocar informações, começa a comunicação
  if(client.connect(host, port)){
    Serial.println("O ESP conectou no Server");
    client.print(comandoBomba()); 
    Serial.print(comandoBomba());
    while (client.connected()) { 
      comparaSetPoint();
      client.print(String("{1") + String(converteUmidade(umidadeLida)) + String("}"));   
      delay(tempoEnvio);
       if(ligou != ultimoLigou)
       {
         client.print(comandoBomba());
         ultimoLigou = ligou;
       }
    
    if(client.available()){
      
       String line = client.readStringUntil('}');
       Serial.println(line);
       client.println(tcpAcionaIO(line));
       dadoAnterior = line[2];
       setPoint = convertCharUmidade(line);     

                  
    }      
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