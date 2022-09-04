#define x A0
#define y A1
#define z A2

float x_value = 0.0;
float y_value = 0.0;
float z_value = 0.0;

void setup() {
  Serial.begin(9600); // Empezamos una comunicación entre el Arduino y la computadora
}

void loop() {
  x_value = analogRead(x);
  y_value = analogRead(y);
  z_value = analogRead(z);

  Serial.print("x: ");
  Serial.println(x_value);
  Serial.print("y: ");
  Serial.println(y_value);
  Serial.print("z: ");
  Serial.println(z_value);

  delay(1000);
}
