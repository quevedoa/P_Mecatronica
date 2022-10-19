#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define LED 8
#define echo 6
#define trig 7
#define voltimetro A0
#define luminosidad A1
#define sharp A2

#define DHTPIN 10
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int minV = 687;

int salidaVoltimetro;
int salidaLuminosidad;
float tempC;
float distanciaUltrasonico;
float distanciaSharp;

String resultadoLCD;
String errors[4] = {"Low Battery", "Overheating", "U_Obstacle", "S_Obstacle"};
String errorsShort[4] = {"Bt", "Tmp", "UObs", "SObs"};

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
 
  salidaVoltimetro = analogRead(voltimetro);
  salidaLuminosidad = analogRead(luminosidad);

  delay(1000);
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

  // Serial.println(tempC);
  printResults();
  checarLimites();
  printLCD();  
}

void printLCD() {
  lcd.clear();
 
  lcd.setCursor(0,0);
  lcd.print("L: ");
  lcd.print(salidaLuminosidad);
  lcd.print(" bits");

  lcd.setCursor(0,1);
  lcd.print(resultadoLCD);
}

void checarLimites() {
  byte count = 0b0000;
 
  // Voltimetro
  if (salidaVoltimetro < minV) {
    bitWrite(count, 0, 1);
  }
 
  // Temperatura
  if (tempC > 20.0) {
    bitWrite(count, 1, 1);
  }
 
  // Sensor ultrasónico
  if (distanciaUltrasonico <= 15) {
    bitWrite(count, 2, 1);
  }

  // Sensor sharp
  if (distanciaSharp <= 15) {
    bitWrite(count, 3, 1);
  }

  resultadoLCD = "";
  if (count == 0b0000) {
    digitalWrite(LED, LOW);
    resultadoLCD = "";
  } else if ((count == 0b1000) or (count == 0b0100) or (count == 0b0010) or (count == 0b0001)) {
    digitalWrite(LED, HIGH);
    int index = int(log(count)/log(2));
    resultadoLCD = errors[index];
  } else {
    digitalWrite(LED, HIGH);
    for (int i = 0; i <= 3; i++) {
      if (bitRead(count, i) == 1) {
        resultadoLCD = resultadoLCD + errorsShort[i] + "-";
      }
    }
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
