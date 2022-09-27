#define pot A0
#define MotA 10
#define MotB 11

float potValue = 0;
float voltaje = 0;

void setup() {
  Serial.begin(9600);

  pinMode(MotA, OUTPUT);
  pinMode(MotB, OUTPUT);
}

void loop() {
  potValue = analogRead(pot);
  voltaje = map(potValue, 0, 1023, 0, 5); // Leemos potenciometro y mappeamos a voltaje
  
  Serial.print("Voltaje Potenciometro");
  Serial.println(voltaje);

  if (voltaje > 0 && voltaje < 2) {
    levogiro();
  } else if (voltaje >= 2 && voltaje < 3) {
    girodetenido();
  } else {
    dextrogiro();
  }
}

void levogiro() {
  digitalWrite(MotA, HIGH);
  digitalWrite(MotB, LOW);
  Serial.println("Levogiro");
}

void dextrogiro() {
  digitalWrite(MotA, LOW);
  digitalWrite(MotB, HIGH);
  Serial.println("Dextrogiro");
}

void girodetenido() {
  digitalWrite(MotA, LOW);
  digitalWrite(MotB, LOW);
  Serial.println("Giro Detenido");
}
