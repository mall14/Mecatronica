 // 08-02-2019

// Alejandro Rodriguez - 158192
// Marco Mendoza - 144360
 
int led = 13;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  DDRB = DDRB | B10000000;
}

// the loop routine runs over and over again forever:
void loop() {
 asm volatile (
  "principal: \n\t"
  "sbi 0x05, 7 \n\t" \
  "call tiempo \n\t"
  "cbi 0x05, 7 \n\t" \
  "call tiempo \n\t"
  "jmp principal \n\t"

  "tiempo: \n\t"
  "ldi r22, 24 \n\t"
  "loop3: \n\t" 
  "ldi r21, 255 \n\t" 
  "loop2: \n\t"
  "ldi r20, 255 \n\t"
  "loop1: \n\t"
  "dec r20 \n\t"
  "brne loop1 \n\t"
  "dec r21 \n\t"
  "brne loop2 \n\t"
  "dec r22 \n\t"
  "brne loop3 \n\t"
  "nop \n\t"
  "ret \n\t" 
 );
}
