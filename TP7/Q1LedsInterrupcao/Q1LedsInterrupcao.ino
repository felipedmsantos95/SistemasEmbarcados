
#define nBotao 6

const byte led[nBotao] = {8, 9, 10, 11, 12, 13};
volatile byte state[nBotao] {LOW, LOW, LOW, LOW, LOW, LOW};
int cont = 0;

void setup()
{
  pinMode(2, INPUT_PULLUP);//Botões
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  
  for(cont = 0; cont <nBotao; cont++)
    pinMode(led[cont], OUTPUT);
  
  PCICR = B00000100;//Habilitar grupo de interrupção PCIE2
  PCMSK2 = B11111100; //Botões do D2 ao 7, PCINT18 a PCINT23 habilitados
  PCIFR = B00000000;//limpa os flags
}

void loop()
{
  
 for(cont = 0; cont < nBotao; cont++)
    digitalWrite(led[cont], state[cont]);
  
  
}

volatile uint8_t last_PIND = PIND;

ISR(PCINT2_vect){
  uint8_t changed_bits;
  changed_bits = PIND ^ last_PIND;
    last_PIND = PIND;
  
    if (changed_bits & (1 << PIND2)) //Porta D2 Arduino, Verificar pinagem controlador pra ver a letra, vai de A a D
    {
      if (PIND & (1 << PIND2)) { //Mudança de LOW pra HIGH
        state[0] = !state[0];
    }
    else {
    // D2 mudou de HIGH para LOW;
        }
    }
    if (changed_bits & (1 << PIND3)) //Porta D3 Arduino
      if (PIND & (1 << PIND3))  //Mudança de LOW pra HIGH
        state[1] = !state[1];
    if (changed_bits & (1 << PIND4)) //Porta D4 Arduino
      if (PIND & (1 << PIND4))  //Mudança de LOW pra HIGH
        state[2] = !state[2];
    if (changed_bits & (1 << PIND5)) //Porta D4 Arduino
      if (PIND & (1 << PIND5))  //Mudança de LOW pra HIGH
        state[3] = !state[3];
    if (changed_bits & (1 << PIND6)) //Porta D4 Arduino
      if (PIND & (1 << PIND6))  //Mudança de LOW pra HIGH
        state[4] = !state[4];
    if (changed_bits & (1 << PIND7)) //Porta D4 Arduino
      if (PIND & (1 << PIND7))  //Mudança de LOW pra HIGH
        state[5] = !state[5];
  
  
}
