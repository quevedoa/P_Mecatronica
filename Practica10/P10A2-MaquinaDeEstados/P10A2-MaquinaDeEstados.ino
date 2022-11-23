#define LED 13

int estado;
int light_dif;

void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
}

void loop() {
  switch (estado) {
    case 0:
      Serial.println("Estado 0");
      estado = 1;
      break;
      
    case 1:
      Serial.println("Estado 1");
      digitalWrite(LED, LOW);
      lightSensor();
      if (abs(light_dif) < 30) {
        estado = 2;
      } else {
        estado = 0;
      }
      break;

    case 2:
      Serial.println("Estado 1");
      digitalWrite(LED, HIGH);
      delay(1000);
      estado = 0;
      break;
  }
}

void lightSensor() {
  light_dif = 20;
}
