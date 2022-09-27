#define pot A0
#define MotA 10
#define MotB 11
#define acelerar 9


float potValue = 0;
float voltajePorcentaje = 0;

int pwm = 0;

void setup() {
  Serial.begin(9600);

  pinMode(MotA, OUTPUT);
  pinMode(MotB, OUTPUT);
  pinMode(acelerar, OUTPUT);
}

void loop() {
  potValue = analogRead(pot);

  // Mapeamos el valor del potenciometro de 0-500 para poder representar centésimas de volts.
  voltajePorcentaje = map(potValue, 0, 1023, 0, 500);
  
  Serial.print("Voltaje Potenciometro ");
  Serial.println(voltajePorcentaje/100);

  if (voltajePorcentaje >= 0 && voltajePorcentaje <= 200) {
    levogiro();
    pwm = map(voltajePorcentaje, 0, 200, 0, 255);
    analogWrite(acelerar, 255-pwm); // Hacemos 255-pwm para que empiece en la velocidad más alta y disminuya cuando se acerque a los 200 volts.
  } else if (voltajePorcentaje > 200 && voltajePorcentaje < 300) {
    girodetenido();
    analogWrite(acelerar, 0);
  } else if (voltajePorcentaje >= 300 && voltajePorcentaje <= 500) {
    dextrogiro();
    pwm = map(voltajePorcentaje, 300, 500, 0, 255);
    analogWrite(acelerar, pwm);
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
