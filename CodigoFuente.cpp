int pinLedVerde = 2;       // LED verde en pin 2
int pinLedAmarillo = 4;    // LED amarillo en pin 4
int pinLedRojo = 5;        // LED rojo en pin 5
int pinLedParpadeo = 19;   // LED de parpadeo en el pin 19
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
  pinMode(pinLedVerde, OUTPUT);
  pinMode(pinLedAmarillo, OUTPUT);
  pinMode(pinLedRojo, OUTPUT);
  pinMode(pinLedParpadeo, OUTPUT);  // Configura el pin 19 para el nuevo LED

  // Asegurarse de que todos los LEDs estén apagados al inicio
  digitalWrite(pinLedVerde, LOW);
  digitalWrite(pinLedAmarillo, LOW);
  digitalWrite(pinLedRojo, LOW);
}

void loop() {
  int distancia = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
  Serial.println(distancia);
  
  if (distancia < umbralDistancia && !objetoDetectado) {
    objetoDetectado = true;  // Detecta que un objeto ha pasado
    contador++;
    Serial.print("Contador de objetos: ");
    Serial.println(contador);

    // Hacer parpadear el LED al detectar un objeto
    for (int i = 0; i < 3; i++) {  // Parpadea 3 veces
      digitalWrite(pinLedParpadeo, HIGH);
      delay(200);
      digitalWrite(pinLedParpadeo, LOW);
      delay(200);
    }
  } else if (distancia >= umbralDistancia) {
    objetoDetectado = false;  // Resetea la detección para el próximo objeto
  }

  // Encender los LEDs progresivamente según el contador
  if (contador >= 5 && contador < 10) {
    digitalWrite(pinLedVerde, HIGH);   // Enciende el LED verde al contar 5 objetos
  } else if (contador >= 10 && contador < 15) {
    digitalWrite(pinLedVerde, HIGH);
    digitalWrite(pinLedAmarillo, HIGH); // Enciende el LED amarillo al contar 10 objetos
  } else if (contador >= 15) {
    digitalWrite(pinLedVerde, HIGH);
    digitalWrite(pinLedAmarillo, HIGH);
    digitalWrite(pinLedRojo, HIGH);     // Enciende el LED rojo al contar 15 objetos
  }

  delay(100);
}