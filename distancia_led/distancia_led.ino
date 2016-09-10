#include <Ultrasonic.h>     //Carrega a biblioteca Ultrasonic

#define PINO_TRIGGER  12 
#define PINO_ECHO     11 

int n1=2;
int n2=3;
int n3=4;
int n4=5;
int n5=6;

int led;

Ultrasonic ultrasonic(PINO_TRIGGER, PINO_ECHO); 

void setup()
{
  Serial.begin(9600); //Inicializa a serial
  
  pinMode(n1, OUTPUT); 
  pinMode(n2, OUTPUT);
  pinMode(n3, OUTPUT);
  pinMode(n4, OUTPUT);
  pinMode(n5, OUTPUT);
}


void loop(){
  float cmMsec, inMsec;
  //Le os dados do sensor, com o tempo de retorno do sinal
  long microsec = ultrasonic.timing();  
  //Calcula a distancia em centimetros
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM); 
  Serial.print("Cent: ");
  Serial.print(cmMsec);

   
    digitalWrite(n1,LOW);
    digitalWrite(n2,LOW);
    digitalWrite(n3,LOW);
    digitalWrite(n4,LOW);
    digitalWrite(n5,LOW);


  if (cmMsec<100){
    led=1;
    digitalWrite(n1,HIGH);
    digitalWrite(n2,LOW);
    digitalWrite(n3,LOW);
    digitalWrite(n4,LOW);
    digitalWrite(n5,LOW);
  }
  if (cmMsec>=100&&cmMsec<=150){
    led=2;
    digitalWrite(n1,HIGH);
    digitalWrite(n2,HIGH);
    digitalWrite(n3,LOW);
    digitalWrite(n4,LOW);
    digitalWrite(n5,LOW);
  }
  if (cmMsec>=150&&cmMsec<=200){
    led=3;
    digitalWrite(n1,HIGH);
    digitalWrite(n2,HIGH);
    digitalWrite(n3,HIGH);
    digitalWrite(n4,LOW);
    digitalWrite(n5,LOW);
  }
  if (cmMsec>=200&&cmMsec<=250){
    led=4;
    digitalWrite(n1,HIGH);
    digitalWrite(n2,HIGH);
    digitalWrite(n3,HIGH);
    digitalWrite(n4,HIGH);
    digitalWrite(n5,LOW);
  }
  if (cmMsec>=250&&cmMsec<=300){
    led=4;
    digitalWrite(n1,HIGH);
    digitalWrite(n2,HIGH);
    digitalWrite(n3,HIGH);
    digitalWrite(n4,HIGH);
    digitalWrite(n5,HIGH);
  }
  
  switch(led){
    case 1:
    digitalWrite(n1,HIGH);
    break;
    case 2:
    digitalWrite(n2,HIGH);
    break;
    case 3:
    digitalWrite(n3,HIGH);
    break;
    case 4:
    digitalWrite(n4,HIGH);
    break;
    case 5:
    digitalWrite(n5,HIGH);
    break;
  }
  delay(300);
} 
