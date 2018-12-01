#define LEDPIN 13

volatile byte state = LOW;
void setup()
{
  pinMode(LEDPIN, OUTPUT);
  cli();         
  TCCR1A = 0;    
  TCCR1B = 0;    
  TIMSK1 |= (1 << TOIE1);
  TCCR1B |= (1 << CS12); // Sets bit CS12 in TCCR1B
  

  sei();
}

volatile byte segundos = 0;
ISR(TIMER1_OVF_vect)
{    
    if(segundos == 10){//10 segundos
      segundos = 0;
      state = ! state;
    }
    segundos++;
}

void loop() {
  digitalWrite(LEDPIN, state);
}
