//int DISTANCIA = 0;
int pinLedAmarillo = 2;
int pinLedVerde = 4;
int pinLedRojo = 5;
int pinLed=2;
int pinEco=12;
int pinGatillo=13;

long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup() {
  Serial.begin(115200);
  pinMode(pinLedAmarillo, OUTPUT);
  pinMode(pinLedVerde, OUTPUT);
  pinMode(pinLedRojo, OUTPUT);
}

void loop() {
  int distancia = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
  Serial.println(distancia);
  
  if (distancia < 5) {
    digitalWrite(pinLedAmarillo, HIGH);
    digitalWrite(pinLedVerde, LOW);
    digitalWrite(pinLedRojo, LOW);
  } else if (distancia >= 5 && distancia < 10) {
    digitalWrite(pinLedAmarillo, LOW);
    digitalWrite(pinLedVerde, HIGH);
    digitalWrite(pinLedRojo, LOW);
  } else if (distancia >= 10 && distancia <= 15) {
    digitalWrite(pinLedAmarillo, LOW);
    digitalWrite(pinLedVerde, LOW);
    digitalWrite(pinLedRojo, HIGH);
  } else {
    digitalWrite(pinLedAmarillo, LOW);
    digitalWrite(pinLedVerde, LOW);
    digitalWrite(pinLedRojo, LOW);
  }
  
  delay(10);
}