// Codigo para el esclavo
#include <Wire.h>
#include <Servo.h>

Servo servo; // Definimos una variable para el servo motor

int servo_angle; // El angulo del servo que el maestro va a mandar

void setup() {
  servo.attach(3);
  Wire.begin(0xAF);
  Serial.begin(9600);
}

void loop() {
  // Imprimimos llegadas de datos
  Serial.print("Ángulo Servo: ");
  Serial.println(servo_angle);

  // Cada ciclo del loop llamamos lectura para ver que ángulo mandó maestro
  Wire.onReceive(lectura);
}

void lectura() {
  servo_angle = Wire.read();
  servo.write(servo_angle);
}
