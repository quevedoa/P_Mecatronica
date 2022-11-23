#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define acelerar1 2
#define signal1MotorA 4
#define signal2MotorA 3

#define acelerar2 7
#define signal1MotorB 5
#define signal2MotorB 6

#define voltimetro A0

#define fotoRes1 A1
#define fotoRes2 A2
#define fotoRes3 A3

int L_LDR, R_LDR, B_LDR, light_dif;
int umbral_sup = -25, umbral_inf = -35;
int umbralB_sup = 400, umbralB_inf = 350;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(signal1MotorA, OUTPUT);
  pinMode(signal1MotorB, OUTPUT);
  pinMode(signal2MotorA, OUTPUT);
  pinMode(signal2MotorB, OUTPUT);

  pinMode(acelerar1, OUTPUT);
  pinMode(acelerar2, OUTPUT);

  stopRobot();
}

void loop() {
  lightSensor();
  followLight();
}

void followLight() {
  if ((B_LDR >= umbralB_inf) && (B_LDR <= umbralB_sup)) {
    while ((light_dif < umbral_inf) && (light_dif > umbral_sup)) {
      lightSensor();
      DriveRobot(1,-1);
    }
  }
  
  if ((light_dif > umbral_inf) && (light_dif < umbral_sup)) {
    lightSensor();
    DriveRobot(1,1);
  } else if (light_dif >= umbral_sup) {
    while (light_dif >= umbral_sup) {
      lightSensor();
      DriveRobot(1,-1);
    }
  } else if (light_dif <= umbral_inf) {
    while (light_dif <= umbral_inf) {
      lightSensor();
      DriveRobot(-1,1);
    }
  }
}

void lightSensor() {
  // A1 - Right, A2 - Left y A3 - Back 
  R_LDR = analogRead(fotoRes1);
  L_LDR = analogRead(fotoRes2);
  B_LDR = analogRead(fotoRes3);

  light_dif = R_LDR - L_LDR;
  Serial.print("R: ");
  Serial.print(R_LDR);
  Serial.print(" - L: ");
  Serial.print(L_LDR);
  Serial.print(" - B: ");
  Serial.println(B_LDR);
  printLightSensors();
}

void  printLightSensors() {
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("L:");
  lcd.print(L_LDR);
  lcd.print(" - R:");
  lcd.print(R_LDR);

  lcd.setCursor(0,1);
  lcd.print("D:");
  lcd.print(light_dif);
  lcd.print(" - B:");
  lcd.print(B_LDR);
}

void DriveRobot(float LSignal, float RSignal) {
  // Si la señal de la rueda izquierda es menor a 0, entonces esta gira hacia atràs.
  if(LSignal < 0) {
    digitalWrite(signal1MotorA,HIGH);
    digitalWrite(signal2MotorA,LOW);
    digitalWrite(acelerar1, 10);
  }
  
  // Si la señal de la rueda izquierda es mayor a cero, entonces girarà hacia adelante.
  if(LSignal > 0) {
    digitalWrite(signal1MotorA,LOW);
    digitalWrite(signal2MotorA,HIGH);
    digitalWrite(acelerar1, 10);
  }
  
  // Si la señal es igual a 0, entonces se queda sin movimiento la rueda 
  if(LSignal == 0) {
    digitalWrite(signal1MotorA,LOW);
    digitalWrite(signal2MotorA,LOW);
    digitalWrite(acelerar1, 0);
  }
  
  // Si la señal de la rueda derecha es menor a cero, entonces girarà hacia atràs.
  if(RSignal < 0) {
    digitalWrite(signal1MotorB,LOW);
    digitalWrite(signal2MotorB, HIGH);
    digitalWrite(acelerar2, 10);
  }
  
  // Si la señal de la rueda derecha es mayor a cero, entonces girarà hacia adelante.
  if( RSignal > 0) {
    digitalWrite(signal1MotorB,HIGH);
    digitalWrite(signal2MotorB,LOW);
    digitalWrite(acelerar2, 10);
  }
  
  // Si la señal de la rueda derecha es igual a cero, entonces no se moverà esta rueda. 
  if(RSignal == 0) {
    digitalWrite(signal1MotorB,LOW);
    digitalWrite(signal2MotorB,LOW);
    digitalWrite(acelerar2, 0);
  }
}

//void DriveRobot(float LSignal, float RSignal) {
//  if (LSignal > 0 && RSignal > 0) {
//    Serial.println("adelante");
//    digitalWrite(signal1MotorA, HIGH);
//    digitalWrite(signal2MotorA, LOW);
//
//    digitalWrite(signal1MotorB, HIGH);
//    digitalWrite(signal2MotorB, LOW);
//  } else if (LSignal > 0 && RSignal < 0) {
//    Serial.println("derecha");
//    digitalWrite(signal1MotorA, HIGH);
//    digitalWrite(signal2MotorA, LOW);
//    
//    digitalWrite(signal1MotorB, LOW);
//    digitalWrite(signal2MotorB, HIGH);
//  } else if (LSignal < 0 && RSignal > 0) {
//    Serial.println("izquierda");
//    digitalWrite(signal1MotorA, LOW);
//    digitalWrite(signal2MotorA, HIGH);
//
//    digitalWrite(signal1MotorB, HIGH);
//    digitalWrite(signal2MotorB, LOW);
//  } else if(LSignal < 0 && RSignal < 0){
//    Serial.println("atras");
//    digitalWrite(signal1MotorA, LOW);
//    digitalWrite(signal2MotorA, HIGH);
//
//    digitalWrite(signal1MotorB, LOW);
//    digitalWrite(signal2MotorB, HIGH);
//    
//  }else {
//    stopRobot();
//  }
//}

void stopRobot() {
    digitalWrite(signal1MotorA, LOW);
    digitalWrite(signal2MotorA, LOW);
    digitalWrite(signal1MotorB, LOW);
    digitalWrite(signal2MotorB, LOW);
}
