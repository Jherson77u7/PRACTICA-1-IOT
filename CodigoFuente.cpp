int pinLedAmarillo = 2;
int pinLedVerde = 4;
int pinLedRojo = 5;
int pinEco = 12;
int pinGatillo = 13;

int contador = 0;
int umbralDistancia = 10;  // Distancia para detectar el paso de un objeto
bool objetoDetectado = false;

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
  
  if (distancia < umbralDistancia && !objetoDetectado) {
    objetoDetectado = true;  // Detecta que un objeto ha pasado
    contador++;
    Serial.print("Contador de objetos: ");
    Serial.println(contador);
  } else if (distancia >= umbralDistancia) {
    objetoDetectado = false;  // Resetea la detección para el próximo objeto
  }

  // Mostrar el conteo usando los LEDs
  if (contador <= 5) {
    digitalWrite(pinLedVerde, HIGH);
    digitalWrite(pinLedAmarillo, LOW);
    digitalWrite(pinLedRojo, LOW);
  } else if (contador > 5 && contador <= 10) {
    digitalWrite(pinLedVerde, LOW);
    digitalWrite(pinLedAmarillo, HIGH);
    digitalWrite(pinLedRojo, LOW);
  } else if (contador > 10) {
    digitalWrite(pinLedVerde, LOW);
    digitalWrite(pinLedAmarillo, LOW);
    digitalWrite(pinLedRojo, HIGH);
  }

  delay(100);
}