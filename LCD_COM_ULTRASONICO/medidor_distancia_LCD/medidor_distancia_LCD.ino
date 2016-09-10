//Programa: Teste de Display LCD 16 x 2
//Autor: FILIPEFLOP
 
//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>
 
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Define as variáveis utilizadas nos calculos da distancia
const int trig = 9, echo = 10;
long duration, Distanceincm, Litros;

void setup()
{
  setupLCD();
  setupUltrasonic();
}
 
void loop()
{
  //Limpa a tela
  lcd.clear();
  showLevel();
  //showCustomMessage();
}


void setupLCD(){
  lcd.begin(16, 2);
}

void setupUltrasonic(){
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void showLevel(){
  lcd.setCursor(0, 0);
  lcd.print("NIVEL EM LITROS");
  lcd.setCursor(3, 1);
  lcd.print(calc());
  
   lcd.setCursor(9, 1);
   lcd.print(Distanceincm);
  delay(5000);
}

int calc(){
  digitalWrite(trig, HIGH);
  delay(15);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  Distanceincm = duration / 58;  
  Litros = ((115 - Distanceincm)*10);

  Serial.print("Distance in cm = ");
  Serial.print(Distanceincm);
  Serial.print("Litros");
  Serial.print(Litros);
  
  return Litros;
}


