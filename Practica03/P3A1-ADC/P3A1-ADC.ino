#define pot A0
#define LED 13

float value = 0.0;
float voltaje;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600); // Empezamos una comunicación entre el Arduino y la computadora
}

void loop() {
  value = analogRead(pot); // Leemos el valor de analógico del potenciometro (0-1023)
  voltaje = (value/1023)*5; // Convertimos de valor (0-1023) a voltaje (0-5)
  
  Serial.print("Valor ADC: "); // Imprimimos valor del potenciometro a la consola
  Serial.println(voltaje);
  delay(100);

  if (voltaje > 3) { // Si el voltaje es mayor a 3 prendemos el LED, de lo contrario se apaga
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}
