#define sensor 0
#define buzina 3

void setup()
{
  pinMode(buzina, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  
  digitalWrite(buzina, LOW);
  int leitura = analogRead(sensor);
  float tensao = leitura * 5.0;
  tensao /= 1024.0; 
  float temperatura = (tensao - 0.5) * 100 ; 
  
  if(temperatura >= 50){
    digitalWrite(buzina,HIGH);
    delay(1000);
  }
  
  
 
}
