 // 21-02-2019

// Alejandro Rodriguez - 158192
// Marco Mendoza - 144360


void setup(){
  
  cli();
  
  DDRB |= 1 << DDB7; // initialize the digital pin as an output.
  PORTB |= 1 << PORTB7; //initialize output as high
  
  TCCR1A = 0;
  TCCR1B = B00000101; // CLKio/1024 
  //TCCR1B |= 1 << CS12; //lo mismo
  //TCCR1B |= 1 << CS10;
  
  TCNT1H = 0xC2; //2**16 - 16M/1024 = 49911
  TCNT1L = 0xF7;
  
  TIMSK1 = B00000001; // Timer/Counter1 Overflow Interrupt Enable
  //TIMSK1 |=  1 << TOIE1; //lo mismo
  
  sei();
}

void loop(){
}

ISR(TIMER1_OVF_vect){
  //PORTB = 0x05
  asm volatile(
    "sbis 0x05, 7    \n\t"
    "rjmp on         \n\t"
    "cbi  0x05, 7    \n\t"
    "sbic 0x05, 7    \n\t"
    "on: sbi 0x05, 7 \n\t"
   );
   
  TCNT1H = 0xC2;
  TCNT1L = 0xF7;
}
