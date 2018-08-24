
//Display
#define  A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6

//LEDs

#define ledPower  7
#define ledPorta  8

//Botões
#define botaoDec  10
#define botaoInc  9
#define botaoPorta  13
#define botaoPower  12

//Buzzer
#define buzzer 11

//Variáveis para guardar estados dos botões

boolean power = LOW; //ler o estado do botão power
boolean turnOn = false; //guardar o estado do botão power
boolean atualPower = LOW;

boolean porta = LOW;
boolean portaAberta = true;
boolean atualPorta = LOW;

boolean inc = LOW;
boolean atualInc = LOW;
boolean dec = LOW;
boolean atualDec = LOW;

//tempo exibido no display
int tempo = 0;

void setup()
{
  //Saidas
  pinMode(ledPower, OUTPUT);
  pinMode(ledPorta, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  
  //Entradas
  pinMode(botaoDec, INPUT);
  pinMode(botaoInc, INPUT);
  pinMode(botaoPorta, INPUT);
  pinMode(botaoPower, INPUT);
}

void display(int num)
{
  switch(num){
      case 0:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, LOW);
        break;
      case 1:
        digitalWrite(A, LOW);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, LOW);
        digitalWrite(E, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, LOW);
        break;
      case 2:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, LOW);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, LOW);
        digitalWrite(G, HIGH);
        break;
      case 3:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, HIGH);
        break;
      case 4:
        digitalWrite(A, LOW);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, LOW);
        digitalWrite(E, LOW);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
      case 5:
        digitalWrite(A, HIGH);
        digitalWrite(B, LOW);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, LOW);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
      case 6:
        digitalWrite(A, HIGH);
        digitalWrite(B, LOW);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
      case 7:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, LOW);
        digitalWrite(E, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, LOW);
        break;
      case 8:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
      case 9:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, LOW);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
  }
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

//Verificação de incremento e decremento antes da porta fechar  
void incDec(){
  
    atualInc = debounce(inc,botaoInc);
    if(inc == LOW && atualInc == HIGH)
    {
      tempo++;
        if(tempo > 9)
          tempo = 9;
        display(tempo);
    }
    inc = atualInc;
    
    atualDec = debounce(dec,botaoDec);
    if(dec == LOW && atualDec == HIGH)
    {
      tempo--;
        if(tempo < 0)
          tempo = 0;    
        display(tempo);
    }
    dec = atualDec;
  
}

void verificaPorta()
{
  //Verficação porta aberta
   atualPorta = debounce(porta, botaoPorta);  
    if(porta == LOW && atualPorta == HIGH)
    {
      portaAberta = !portaAberta; 
    }
    porta = atualPorta;
    digitalWrite(ledPorta, portaAberta);
  
}

void fornoLigado()
{ 
    //int set = tempo;
    while(tempo >= 0 && !portaAberta)
    { 
        verificaPorta();
      display(tempo);
        delay(1000);
        tempo--;
    }
   if(!portaAberta){
    //tempo = set;
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
   }
    turnOn = LOW;//Desliga o forno depois de terminar
}


void loop()
{  
    display(tempo);
    verificaPorta();    
  
    /*if(!turnOn)
      incDec();*/
     
    if(!portaAberta){
    
        if(!turnOn)
          incDec();
      //Verificação do botao Power
      atualPower = debounce(power, botaoPower);  
      if(power == LOW && atualPower == HIGH)
      {
        turnOn = !turnOn; 
      }
      power = atualPower;
      digitalWrite(ledPower, turnOn);
      if(turnOn && !portaAberta)
        {
          fornoLigado();
        }
   }
   else
   {
      digitalWrite(ledPower, LOW);
   }
    
  
    
    
  
}
