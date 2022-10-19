#define LED 7

int volSalidaBits;
int maxV = 863;
int minV = 656;

void setup() {
  Serial.begin(9600);
  
  pinMode(LED, OUTPUT);
}

void loop() {
  volSalidaBits = analogRead(A0);

  Serial.print("Voltaje Salida en Bits ");
  Serial.println(volSalidaBits);

  if ((volSalidaBits <= maxV) && (volSalidaBits > minV)) {
    blink();
  } else {
    digitalWrite(LED, HIGH);
  }

}

void blink() {
  digitalWrite(LED,HIGH);
  delay(125);
  digitalWrite(LED,LOW);
  delay(125);
}
