
#define LED 7

int volSalidaBits;
int maxV = 1000;
int minV = 500;

int pwm = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(LED, OUTPUT);
}

void loop() {
  volSalidaBits = analogRead(A0);
  pwm = map(volSalidaBits, minV, maxV, 0, 255);

  Serial.print("Voltaje Salida en Bits ");
  Serial.println(volSalidaBits);

  analogWrite(LED, 255-pwm);
}

void blink() {
  digitalWrite(LED,HIGH);
  delay(125);
  digitalWrite(LED,LOW);
  delay(125);
}
