#include <Wire.h>

#define LED 13

int dato;

void setup() {
  Wire.begin(0xAF);
  Wire.onReceive(lectura);

  pinMode(LED, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  Serial.println(dato);
  delay(100);
}

void lectura() {
  dato = Wire.read();

  if (dato == 1) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}
