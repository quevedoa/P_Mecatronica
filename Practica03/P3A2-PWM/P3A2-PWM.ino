#define pot A0
#define LED 13

float value = 0.0;
float brillo;

int pwm = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600); // Empezamos una comunicación entre el Arduino y la computadora
}

void loop() {
  value = analogRead(pot); // Leemos el valor de analógico del potenciometro (0-1023)
  pwm = value/4; // Convertimos el valor del potenciometro (0-1023) al valor que lee el led (0-254) 
  brillo = (value/1023)*100; // Convertimos de valor (0-1023) a voltaje (0-5)
  
  
  Serial.print("Porcentaje Brillo: "); // Imprimimos valor del potenciometro a la consola
  Serial.println(brillo);
  delay(1000);
  
  analogWrite(LED, pwm); // Prendemos el LED con la intensidad proporcional al valor del potenciometro
}
