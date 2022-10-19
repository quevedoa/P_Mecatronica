#define sharp A0
#define LED 8

int sensor;
float distancia;

void setup() {
  pinMode(LED, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  sensor = analogRead(sharp);

  distancia = 1990*(pow(sensor, -0.921));
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if (distancia < 15) {
    digitalWrite(LED, HIGH);
    Serial.println("Obstaculo");
  } else {
    digitalWrite(LED, LOW);
  }
}
