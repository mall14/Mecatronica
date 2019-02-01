// 25-01-2019

// Alejandro Rodriguez - 158192
// Marco Mendoza - 144360

int analogPin = A0;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5V
int val = 0;           // variable to store the value read
int led = 13;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(A0, INPUT);              
  Serial.begin(9600); //  setup serial
}

void loop()
{
  val = analogRead(analogPin);     // read the input pin
  Serial.println(val);             // debug value
  delay(10);
  digitalWrite(led, val<800 ? LOW : HIGH);
  //  if(val<800){
  //     digitalWrite(led, LOW); 
  //  }else{
  //    digitalWrite(led, HIGH); 
  //  }
}
