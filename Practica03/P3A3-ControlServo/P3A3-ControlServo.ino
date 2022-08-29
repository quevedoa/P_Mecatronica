#define pot A0

#include <Servo.h>

Servo servo1; // Definimos una variable para el servo motor

float value = 0;
float angulo;

void setup() {
  servo1.attach(3);
  Serial.begin(9600); // Empezamos una comunicación entre el Arduino y la computadora
}

void loop() {
  value = analogRead(pot); // Leemos el valor del potenciometro
  angulo = map(value, 0, 1023, 0, 180); // Convertimos del valor del potenciometro a grados de ángulo (0-180)

  Serial.print("Ángulo: "); // Imprimimos el ángulo del servomotor (0-180)
  Serial.println(angulo);
  delay(100);
  
  servo1.write(angulo);
}
