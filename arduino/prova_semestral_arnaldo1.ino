#include <Adafruit_LiquidCrystal.h>

int dist1 = 0;

int dist2 = 0;

int livres, ocupadas, vaga1, vaga2 = 0;
String texto1, texto2, final = "";

Adafruit_LiquidCrystal lcd(0);

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop()
{
  
  dist1 = 0.01723 * readUltrasonicDistance(13, 12);
  if (dist1 < 200) {
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    Serial.print("Distance1: ");
  	Serial.print(dist1);
  	Serial.println(" cm");
    vaga1 = 1;
    texto1 = "\"A\":0";
  } else {
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);
    Serial.print("Distance1: ");
  	Serial.print(dist1);
  	Serial.println(" cm");
    vaga1 = 0;
    texto1 = "\"A\":1";
  }

  dist2 = 0.01723 * readUltrasonicDistance(3, 2);
  if (dist2 < 200) {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    Serial.print("Distance2: ");
  	Serial.print(dist2);
  	Serial.println(" cm");
    vaga2 = 1;
    texto2 = "\"B\":0";
  } else {
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    Serial.print("Distance2: ");
  	Serial.print(dist2);
  	Serial.println(" cm");
    vaga2 = 0;
    texto2 = "\"B\":1";
  }
  final = "\{"+texto1+","+texto2+"\}";
  ocupadas = vaga1 + vaga2;
  livres = 2 - ocupadas;
  Serial.println(final);
  
  lcd.setCursor(0,0);
  lcd.print("vagas livres   ");
  lcd.print(livres);
  lcd.setCursor(0,1);
  lcd.print("vagas ocupadas ");
  lcd.print(ocupadas);
  delay(10); // Delay a little bit to improve simulation performance
}