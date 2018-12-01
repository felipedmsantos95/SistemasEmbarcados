const int ledPin = 13;
volatile byte state = LOW;
void setup() {
  pinMode(ledPin, OUTPUT);
  TIMSK2 = (TIMSK2 & B11111001) | 0x06;
  TCCR2B = (TCCR2B & B11111000) | 0x07;
  OCR2A = 128;
  OCR2B = 200;
}

void loop() {
  digitalWrite(ledPin, state);
}

volatile int segundos = 0;
volatile int segundos2 = 0;
ISR(TIMER2_COMPA_vect){
    
    if(segundos == 305)//5 segundos
    {
      state = HIGH;
      segundos = 0;
    }
    segundos++;
    
}
ISR(TIMER2_COMPB_vect){
  if(segundos2 == 425)//7 segundos
    {
      state = LOW;
      segundos2 = 0;
    }
    segundos2++;
}
