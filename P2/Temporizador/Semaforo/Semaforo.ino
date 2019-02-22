void setup(){
  
  cli();
  
  PORTB = 0;
  DDRB |= 1 << DDB7;    //r1 pin13 (on)
  PORTB |= 1 << PORTB7;
  DDRB |= 1 << DDB6;    //y1 pin12
  DDRB |= 1 << DDB5;    //g1 pin11
  
  DDRB |= 1 << DDB2;    //r2 pin2
  DDRB |= 1 << DDB1;    //y2 pin52
  DDRB |= 1 << DDB0;    //g2 pin53 (on)
  PORTB |= 1 << PORTB0;
  
  TCCR1A = 0;
  TCCR1B = 0;
  
  TCCR1B |= 1 << CS12; //CLKio/1024
  TCCR1B |= 1 << CS10;
  
  TCCR1B |= 1<< WGM12; //CTC
  
  OCR1AH = 0x3D; //16000000/1024/1 = 15625
  OCR1AL = 0x09;
  
  sei();
}

void loop(){
  //PORTB = 0x05
  //TIFR1 = 0x16
  asm volatile(    //r1g1
  "sbi 0x05, 7 \n\t"   //turn on r1
  "cbi 0x05, 6 \n\t"   //turn off y1
  "cbi 0x05, 5 \n\t"   //turn off g1

  "cbi 0x05, 2 \n\t"   //turn off r2
  "cbi 0x05, 1 \n\t"   //turn off y2
  "sbi 0x05, 0 \n\t"   //turn on g2

  "ldi r20, 0x07 \n\t" //load 7 seconds
  
  "r1g2:"
  "sbis 0x16, 1 \n\t"  //OCF1A
  "rjmp r1g2 \n\t"
  "sbi 0x16, 1 \n\t"   //sending a 1 turns of the flag
  "dec r20 \n\t"
  "brne r1g2 \n\t"
  "sbi 0x05, 1 \n\t"   //turn on y2
  "ldi r20, 0x03 \n\t" //load 3 seconds
  
  "r1g2y2:"
  "sbis 0x16, 1 \n\t"
  "rjmp r1g2y2 \n\t"
  "sbi 0x16, 1 \n\t"
  "dec r20 \n\t"
  "brne r1g2y2 \n\t"
  "cbi 0x05, 7 \n\t"   //turn off r1
  "sbi 0x05, 5 \n\t"   //turn on g1
  "sbi 0x05, 2 \n\t"   //turn on r2
  "cbi 0x05, 1 \n\t"   //turn off y2
  "sbi 0x05, 0 \n\t"   //turn off g2
  "ldi r20, 0x07 \n\t" //load 7 seconds

  "g1r2:"
  "sbis 0x16, 1 \n\t"  
  "rjmp g1r2 \n\t"
  "sbi 0x16, 1 \n\t"   
  "dec r20 \n\t"       
  "brne g1r2 \n\t"   
  "sbi 0x05, 6 \n\t"   //turn on y1
  "ldi r20, 0x03 \n\t" //load 3 seconds
  
  "g1y1r2:"
  "sbis 0x16, 1 \n\t"
  "rjmp g1y1r2 \n\t"
  "sbi 0x16, 1 \n\t"
  "dec r20 \n\t"
  "brne g1y1r2\n\t"
  );
}
