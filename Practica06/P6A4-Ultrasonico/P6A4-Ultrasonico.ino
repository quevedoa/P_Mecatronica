
#define echoPin 7
#define trigPin 6
#define LED 8

long duracion;
float distancia;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duracion = pulseIn(echoPin,HIGH);  
  
  distancia = duracion * 0.0343/2;
  
  Serial.print("Distancia ");
  Serial.print(distancia);
  Serial.println("cm");
  
  if (distancia < 15.0) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}
