#define R1 13
#define Y1 12
#define G1 11

#define R2 10
#define Y2 9
#define G2 8

void setup() {
  pinMode(R1, OUTPUT);
  pinMode(Y1, OUTPUT);
  pinMode(G1, OUTPUT);

  pinMode(R2, OUTPUT);
  pinMode(Y2, OUTPUT);
  pinMode(G2, OUTPUT);
}

void loop() {
  digitalWrite(R1, HIGH);
  digitalWrite(G2, HIGH);
  delay(5000);
  digitalWrite(G2, LOW);
  digitalWrite(Y2, HIGH);
  delay(1000);
  
  digitalWrite(R1, LOW);
  digitalWrite(Y2, LOW);
  digitalWrite(G1, HIGH);
  digitalWrite(R2, HIGH);
  delay(5000);

  digitalWrite(G1, LOW);
  digitalWrite(Y1, HIGH);
  delay(1000);

  digitalWrite(Y1, LOW);
  digitalWrite(R2, LOW);
}
