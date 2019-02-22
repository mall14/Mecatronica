// 21-02-2019

// Alejandro Rodriguez - 158192
// Marco Mendoza - 144360

void setup(){
  cli();
  
  DDRB |= 1 << DDB7;   //Digital pin 13 is output
  PORTB |= 1 << PORTB7; //Digital pin 13 output is high
  
  TCCR1A = 0; //Set Timer/Counter Control 1A to 0
  TCCR1B = 0; //Set Timer/Counter Control 1A to 0
  
  TCCR1B |= 1 << CS12; //CLKio/256
  TCCR1B |= 1 << WGM12; //Clear timer on compare match
  
  OCR1AH = 0x3D; //16000000/256/4 = 15625
  OCR1AL = 0x09; //=0011 1101 0000 1001
  
  TIMSK1 = 0; 
  TIMSK1 |=  1 << OCIE1A; //Timer/Counter1A Output Compare Match Interrupt Enable
  //TIMSK1 = B00000010; lo mismo
  sei();
}

void loop(){
}

ISR(TIMER1_COMPA_vect){
  //PORTB = 0x05
  asm volatile(
    "sbis 0x05, 7    \n\t" //skip if bit i/o set
    "rjmp on         \n\t"
    "cbi  0x05, 7    \n\t" //clear bit i/o
    "sbic 0x05, 7    \n\t"
    "on: sbi 0x05, 7 \n\t"
   );
}
