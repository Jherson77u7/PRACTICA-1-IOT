class ContadorObjetos {
  private:
    int pinLedVerde;
    int pinLedAmarillo;
    int pinLedRojo;
    int pinLedParpadeo;
    int pinEco;
    int pinGatillo;
    int contador;
    int umbralDistancia;
    bool objetoDetectado;

    long readUltrasonicDistance() {
      pinMode(pinGatillo, OUTPUT);
      digitalWrite(pinGatillo, LOW);
      delayMicroseconds(2);
      digitalWrite(pinGatillo, HIGH);
      delayMicroseconds(10);
      digitalWrite(pinGatillo, LOW);
      pinMode(pinEco, INPUT);
      
      return pulseIn(pinEco, HIGH);
    }

    void actualizarLEDs() {
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
    }

  public:
    ContadorObjetos(int verde, int amarillo, int rojo, int parpadeo, int eco, int gatillo, int umbral) {
      pinLedVerde = verde;
      pinLedAmarillo = amarillo;
      pinLedRojo = rojo;
      pinLedParpadeo = parpadeo;
      pinEco = eco;
      pinGatillo = gatillo;
      contador = 0;
      umbralDistancia = umbral;
      objetoDetectado = false;

      pinMode(pinLedVerde, OUTPUT);
      pinMode(pinLedAmarillo, OUTPUT);
      pinMode(pinLedRojo, OUTPUT);
      pinMode(pinLedParpadeo, OUTPUT);

      // Asegurarse de que todos los LEDs estén apagados al inicio
      digitalWrite(pinLedVerde, LOW);
      digitalWrite(pinLedAmarillo, LOW);
      digitalWrite(pinLedRojo, LOW);
    }

    void detectarObjeto() {
      int distancia = 0.01723 * readUltrasonicDistance();
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

        actualizarLEDs();
      } else if (distancia >= umbralDistancia) {
        objetoDetectado = false;  // Resetea la detección para el próximo objeto
      }
    }
};

ContadorObjetos contador(2, 4, 5, 19, 12, 13, 10);

void setup() {
  Serial.begin(115200);
}

void loop() {
  contador.detectarObjeto();
  delay(100);
}