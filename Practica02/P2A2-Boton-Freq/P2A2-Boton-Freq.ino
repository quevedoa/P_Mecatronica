#define LED 13
#define BTN 12

int btnState;

void setup() {
  pinMode(LED, OUTPUT)
  pinMode(BTN, INPUT)
}

void loop() {
  btnState = digitalRead(BTN);

  if (btnState == 1) {
    // Rutina de 4Hz
    digitalWrite(LED, HIGH);
    delay(250);
    digitalWrite(LED, LOW);
    delay(250);
  } else {
    // Rutina de 1Hz
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);
  }
}
