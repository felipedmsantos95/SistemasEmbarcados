//Aluno: Felipe de Menezes Santos

#include <UbidotsMicroESP8266.h>


//Ubidots
#define TOKEN  "A1E-daMeEoX0Te8JK9KRoYNOCkyPia8Dm6"  // Put here your Ubidots TOKEN
#define WIFISSID "Thom_D012627" // Put here your Wi-Fi SSID
#define PASSWORD "3b98c463c363445ef9e3251932" // Put here your Wi-Fi password
#define id_sensor "5b9091a3c03f975030db2dce"

//Entradas
#define botao     16
#define sensor    12


//Saidas
#define led       5
#define buzzer    13

//Variáveis para guardar estados do botão

boolean power = LOW; //ler o estado do botão power
boolean turnOn = false; //guardar o estado do botão power
boolean atualPower = LOW;

//Variáveis para guardar estado do sensor
boolean sensorLigado = HIGH;
boolean ativa = false;
boolean atualSensor = HIGH;

Ubidots client(TOKEN);

void setup(){
    Serial.begin(115200);
    pinMode(botao, INPUT);
    pinMode(sensor, INPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(led, OUTPUT);    
    client.wifiConnection(WIFISSID, PASSWORD);

    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
   

}



boolean debounce(boolean last, int switchPin)
{
  boolean current = digitalRead(switchPin);
  if (last != current)
  {
    delay(5);
    current = digitalRead(switchPin);
  }
  return current;
}



void leituraBotao(){
    
    atualPower = debounce(power, botao);
    if(power == LOW && atualPower == HIGH)
      turnOn =  !turnOn; //Flag global do estado do botao
    power = atualPower;

}

void leituraSensor(){
    
    atualSensor = debounce(sensorLigado, sensor);
    if(sensorLigado == HIGH && atualSensor == LOW){
      digitalWrite(buzzer, HIGH);
      ativa = ! ativa;
    }
      
    sensorLigado = atualSensor;
    
}


void loop(){
    //Verifica o botão e liga o sistema
    leituraBotao();   
    digitalWrite(led, turnOn);
   
    //Ações para quando o sistema estiver ligado
    if(turnOn){
      leituraSensor();      
      
    }
    else
      digitalWrite(buzzer, LOW);

    client.add(id_sensor, ativa);
    client.sendAll();
     

}
