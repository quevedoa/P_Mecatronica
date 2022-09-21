#define x A0
#define y A1
#define z A2

float x_value, y_value, z_value;
float Xg, Yg, Zg;

float x_min = 267.0;
float x_max = 402.0;
float y_min = 267.0;
float y_max = 403.0;
float z_min = 272.0;
float z_max = 412.0;

float alfa, beta;

void setup() {
  Serial.begin(9600); // Empezamos una comunicación entre el Arduino y la computadora
}

void loop() {
  x_value = analogRead(x);
  Xg = map(x_value, x_min, x_max, -100, 100);
  Xg = Xg/100;
  y_value = analogRead(y);
  Yg = map(y_value, y_min, y_max, -100, 100);
  Yg = -Yg/100;
  z_value = analogRead(z);
  Zg = map(z_value, z_min, z_max, -100, 100);
  Zg = Zg/100;

  alfa = -atan(tan(Yg/(sqrt(sq(Xg)+sq(Zg)))))*180/PI;
  beta = atan(tan(Xg/(sqrt(sq(Yg)+sq(Zg)))))*180/PI;

//  Serial.print("  Xg: ");
//  Serial.print(Xg);
//  Serial.print("  Yg: ");
//  Serial.print(Yg);
//  Serial.print("  Zg: ");
//  Serial.println(Zg);

  Serial.print("  alfa: ");
  Serial.print(alfa);
  Serial.print("  beta: ");
  Serial.println(beta);
  

//  delay(10);
}
