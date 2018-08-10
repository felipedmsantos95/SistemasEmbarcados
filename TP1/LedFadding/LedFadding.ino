#define led 3

void setup()
{
  pinMode(led, OUTPUT);
}

void loop()
{
  int valor;
  
  for(valor = 0; valor < 256; valor++){
  analogWrite(led, valor);
    delay(5);
  }
  for(valor = 255; valor >=0; valor--){
  analogWrite(led, valor);
    delay(5);
  }
  
}
