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

#define voltimetro A0
#define sharp1 A8
#define sharp2 A9
#define trig 51
#define echo 53

int estado = 0;
int fast = 70, slow = 45, verySlow = 45;

int minV = 687;
int voltaje, battery;

int L_LDR, R_LDR, B_LDR, light_dif;
int umbral_sup = 80, umbral_inf = -80;
int umbralB = 340;

float US_Sensor, L_Sharp, R_Sharp;
int minDist = 40, distRL;


long tiempo;

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

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  DriveRobot(0,0);
}

void loop() {
//  if (tiempo % 5000 == 0) {
//    checkBattery();
//  }
  
  lightSensor();
  distanceSensor();
  followLight();
  lcd.setCursor(0,0);
  //lcd.print("Estado:");
  //lcd.print(estado);
}

void followLight() {
  switch (estado) {
    case 0: // Mientras la luz este directamente en frente y no existan obstaculos en frente, avanza
      while ((light_dif > umbral_inf) && (light_dif < umbral_sup) && (US_Sensor > minDist) && (B_LDR < umbralB)) {
        lightSensor();
        distanceSensor();
        DriveRobot(1,1);
        controlVelocidad(fast, fast);
      }

      DriveRobot(0,0);
      if (B_LDR >= umbralB) { 
        estado = 1;
      } else if (US_Sensor > minDist) {
        estado = 2;
      } else {
        // If la luz es muy brillante estado 5 si no estado 3
        estado = 3;
      }
      break;

    case 1: // Caso donde el robot esta volteando al revés
      while (B_LDR >= umbralB) {
          lightSensor();
          DriveRobot(-1,1);
          // controlVelocidad(slow, slow);
          analogControlVelocidad(100, 100);
      }
      estado = 0;
      break;

    case 2: // Caso donde el robot no está viendo hacia la luz
      if (light_dif >= umbral_sup) { // Turn right
        while (light_dif >= umbral_sup) {
          lightSensor();
          DriveRobot(-1,1);
          controlVelocidad(slow, slow);
          //analogControlVelocidad(100, 100);
        }
      } else if (light_dif <= umbral_inf) { // Turn left
        while (light_dif <= umbral_inf) {
          lightSensor();
          DriveRobot(1,-1);
          controlVelocidad(slow, slow);
          //analogControlVelocidad(100, 100);
        }
      }
      // Ya se enderezó
      estado = 0;
      break;

    case 3: // Caso donde el robot tiene un obstaculo en frente y busca orientarse para evadir objeto
      if (R_Sharp >= L_Sharp) { // Hay algo mas cerca a la izquierda entonces preferimos derecha
        while (US_Sensor <= minDist) {
          distanceSensor();
          DriveRobot(-1,1);
          // analogControlVelocidad(150, 150);
          controlVelocidad(verySlow, verySlow);
        }
        DriveRobot(0,0);
//        delay(1000);
        distRL = L_Sharp;
        while ((L_Sharp + 10 <= distRL) && (US_Sensor > minDist)) {
          distanceSensor();
          DriveRobot(1,1);
          analogControlVelocidad(150, 150);
//          controlVelocidad(verySlow, verySlow);
        }
        if (US_Sensor > minDist) {
          estado = 0;
        } else {
          while (US_Sensor <= minDist) {
            distanceSensor();
            DriveRobot(-1,-1);
            controlVelocidad(verySlow, verySlow);
          }
        }
        // Turn right hasta que no haya nada en frente
        // Registrar valor del L_Sharp
        // Avanzar de frente hasta que el valor de L_Sharp rebase el valor registrado por arriba o se tope con algo en frente
        // Si se topa algo en frente regresar al estado 3 
      } else { // Hay algo mas cerca a la derecha entonces preferimos izquierda
        while (US_Sensor <= minDist) {
          distanceSensor();
          DriveRobot(1,-1);
          // analogControlVelocidad(150, 150);
          controlVelocidad(verySlow, verySlow);
        }
        DriveRobot(0,0);
//        delay(1000);
        distRL = R_Sharp;
        while ((R_Sharp + 10 <= distRL) && (US_Sensor > minDist)) {
          distanceSensor();
          DriveRobot(1,1);
//          controlVelocidad(verySlow, verySlow);
          analogControlVelocidad(150, 150);
        }
        if (US_Sensor > minDist) {
          estado = 0;
        } else {
          while (US_Sensor <= minDist) {
            distanceSensor();
            DriveRobot(-1,-1);
            controlVelocidad(verySlow, verySlow);
          }
        }
      }
      break;

    case 5: // Chance un caso para que se pare cuando llegue a la luz
      while (true) {
        DriveRobot(0,0);
      }
  }
}

void checkBattery() {
  voltaje = analogRead(voltimetro);
  Serial.print("Lectura voltaje: ");
  Serial.println(voltaje);
  while (voltaje < minV) {
    DriveRobot(0,0);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LOW BATTERY");
    delay(1000);
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
  Serial.print(B_LDR);
  Serial.print(" - DIFF: ");
  Serial.println(light_dif);

  tiempo = millis();
  if (tiempo % 10 == 0) {
    lcd.clear();
    printLightSensors();
  }
}

void printLightSensors() {
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

void distanceSensor() {
  delay(300);
  // sharp1 - R, sharp2 - L
  int sensorSharp1 = analogRead(sharp1);
  int sensorSharp2 = analogRead(sharp2);

  R_Sharp = 1990*(pow(sensorSharp1, -0.921));
  L_Sharp = 1990*(pow(sensorSharp2, -0.921));

  // Checa distancia con sensor ultrasonico
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duracion = pulseIn(echo,HIGH);  
  US_Sensor = duracion * 0.0343/2;

  Serial.print("US_Sensor");
  Serial.print(US_Sensor);
  Serial.print(" - R_Sharp");
  Serial.print(R_Sharp);
  Serial.print(" - L_Sharp");
  Serial.println(L_Sharp);
  Serial.print("ESTADO:");
  Serial.println(estado);
  Serial.println();
  
}

void controlVelocidad(int LVel, int RVel) {
  digitalWrite(acelerar1, LVel);
  digitalWrite(acelerar2, RVel-20);
}

void analogControlVelocidad(int LVel, int RVel) {
  analogWrite(acelerar1, LVel);
  analogWrite(acelerar2, RVel);
}

void DriveRobot(float LSignal, float RSignal) {
  // Si la señal de la rueda izquierda es menor a 0, entonces esta gira hacia atràs.
  if(LSignal > 0) {
    digitalWrite(signal1MotorA,HIGH);
    digitalWrite(signal2MotorA,LOW);
//    digitalWrite(acelerar1, 10);
  }
  
  // Si la señal de la rueda izquierda es mayor a cero, entonces girarà hacia adelante.
  if(LSignal < 0) {
    digitalWrite(signal1MotorA,LOW);
    digitalWrite(signal2MotorA,HIGH);
//    digitalWrite(acelerar1, 10);
  }
  
  // Si la señal es igual a 0, entonces se queda sin movimiento la rueda 
  if(LSignal == 0) {
    digitalWrite(signal1MotorA,LOW);
    digitalWrite(signal2MotorA,LOW);
//    digitalWrite(acelerar1, 0);
  }
  
  // Si la señal de la rueda derecha es menor a cero, entonces girarà hacia atràs.
  if(RSignal > 0) {
    digitalWrite(signal1MotorB,LOW);
    digitalWrite(signal2MotorB, HIGH);
//    digitalWrite(acelerar2, 10);
  }
  
  // Si la señal de la rueda derecha es mayor a cero, entonces girarà hacia adelante.
  if( RSignal < 0) {
    digitalWrite(signal1MotorB,HIGH);
    digitalWrite(signal2MotorB,LOW);
//    digitalWrite(acelerar2, 10);
  }
  
  // Si la señal de la rueda derecha es igual a cero, entonces no se moverà esta rueda. 
  if(RSignal == 0) {
    digitalWrite(signal1MotorB,LOW);
    digitalWrite(signal2MotorB,LOW);
//    digitalWrite(acelerar2, 0);
  }
}
