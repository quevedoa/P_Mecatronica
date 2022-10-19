#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 21  
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#define LED 8
#define echo 6
#define trig 7
#define voltimetro A0
#define luminosidad A1
#define sharp A2

int maxV = 863;
int minV = 656;

int salidaVoltimetro;
int salidaLuminosidad;
float tempC;
float distanciaUltrasonico;
float distanciaSharp;

String resultadoLCD;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);

  dht.begin();
  
  lcd.init();
  lcd.backlight();

  pinMode(LED, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  digitalWrite(LED, LOW);
  
  salidaVoltimetro = analogRead(voltimetro);
  salidaLuminosidad = analogRead(luminosidad);

//  delay(2000);
  tempC = dht.readTemperature();

  // Checa distancia con sensor ultrasonico
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duracion = pulseIn(echo,HIGH);  
  distanciaUltrasonico = duracion * 0.0343/2;

  // Checa distancia con sensor Sharp
  int sensor = analogRead(sharp);
  distanciaSharp = 1990*(pow(sensor, -0.921));

  Serial.println(tempC);
//  printResults();
//  printLCD();
//  checarLimites();
}

void printLCD() {
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("L: ");
  lcd.print(salidaLuminosidad);
  lcd.print(" bits");

  lcd.setCursor(0,1);
  lcd.print(resultadoLCD);
}

void checarLimites() {
  // Voltimetro
  if (salidaVoltimetro > minV) {
    digitalWrite(LED, HIGH);
    resultadoLCD = "Low Battery";
  }

  // Temperatura
  if (tempC > 27.0) {
    digitalWrite(LED, HIGH);
    resultadoLCD = "Overheating";
  }

  // Sensor ultrasónico
  if (distanciaUltrasonico <= 15) {
    digitalWrite(LED, HIGH);
    resultadoLCD = "U_Obstacle";
  }

  // Sensor sharp
  if (distanciaSharp <= 15) {
    digitalWrite(LED, HIGH);
    resultadoLCD = "S_Obstacle";
  }
}

void printResults() {
  Serial.print("V: ");
  Serial.print(salidaVoltimetro);
  Serial.print(" bits");

  Serial.print(" -- ");

  Serial.print("L: ");
  Serial.print(salidaLuminosidad);
  Serial.print(" bits");

  Serial.print(" -- ");

  Serial.print("T: ");
  Serial.print(tempC);
  Serial.print(" C");
  
  Serial.print(" -- ");

  Serial.print("DU: ");
  Serial.print(distanciaUltrasonico);
  Serial.print(" cm");

  Serial.print(" -- ");

  Serial.print("DS: ");
  Serial.print(distanciaSharp);
  Serial.println(" cm");
}
