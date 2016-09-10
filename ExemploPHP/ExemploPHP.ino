int ledPin13 =  13;

void setup()   {
  Serial.begin(9600);
 
  pinMode(ledPin13, OUTPUT);
}
 
void loop()
{
  char caracter;
  caracter = Serial.read();
  
  printf("Passou");
  
  if(caracter == 'on')
  {
      digitalWrite(ledPin13, HIGH);
  }
  else
    digitalWrite(ledPin13, LOW);
 
  delay(5000);
}
