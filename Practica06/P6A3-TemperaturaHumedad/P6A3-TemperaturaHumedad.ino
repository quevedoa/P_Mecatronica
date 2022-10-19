#include "DHT.h"

#define DHTPIN 21  
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

String dato;

void setup() {
  Serial.begin(9600);

  dht.begin();
}

void loop() {
//  if (Serial.available() > 0) {
//    dato = Serial.readString();
//  }

//  while (Serial.available() == 0) {} 
//  dato = Serial.readString();
//  delay(2000);

  float humedad = dht.readHumidity();
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);

  if (isnan(humedad) || isnan(tempC) || isnan(tempF)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.println(tempC);

  if (dato == "snsr tempC\n") {
    Serial.print(("Temp: "));
    Serial.print(tempC);
    Serial.println(("C°"));
  } else if (dato == "snsr tempF\n") {
    Serial.print(("Temp: "));
    Serial.print(tempF);  
    Serial.println(("F°"));
  } else if (dato == "snsr hum\n") {
    Serial.print(("Humidity: "));
    Serial.print(humedad);
    Serial.println(("%"));
  }

  //  Serial.print(F("Humidity: "));
  //  Serial.print(humedad);
  //  Serial.print(F("%  Temperatura C: "));
  //  Serial.print(tempC);
  //  Serial.print(F("°C Temperatura F: "));
  //  Serial.print(tempF);
  //  Serial.println("F");
}
