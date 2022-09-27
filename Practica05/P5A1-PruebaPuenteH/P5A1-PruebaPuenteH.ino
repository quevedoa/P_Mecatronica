#define MotA 10
#define MotB 11

void setup() {
  Serial.begin(9600);
  
  pinMode(MotA, OUTPUT);
  pinMode(MotB, OUTPUT);
}

void loop() {
  // Estado 1
  digitalWrite(MotA, HIGH);
  digitalWrite(MotB, LOW);
  Serial.print("Levogiro");
  delay(1000);

  // Estado 2
  digitalWrite(MotA, LOW);
  digitalWrite(MotB, LOW);
  Serial.print("Freno pasivo");
  delay(1000);

  // Estado 3
  digitalWrite(MotA, LOW);
  digitalWrite(MotB, HIGH);
  Serial.print("Dextrogiro");
  delay(1000);

  // Estado 4
  digitalWrite(MotA, HIGH);
  digitalWrite(MotB, HIGH);
  Serial.print("Freno activo");
  delay(1000);
}
