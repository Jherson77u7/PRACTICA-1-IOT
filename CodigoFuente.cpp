
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
        digitalWrite(pinLedVerde, HIGH);   
      } else if (contador >= 10 && contador < 15) {
        digitalWrite(pinLedVerde, HIGH);
        digitalWrite(pinLedAmarillo, HIGH); 
      } else if (contador >= 15) {
        digitalWrite(pinLedVerde, HIGH);
        digitalWrite(pinLedAmarillo, HIGH);
        digitalWrite(pinLedRojo, HIGH);     
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

      digitalWrite(pinLedVerde, LOW);
      digitalWrite(pinLedAmarillo, LOW);
      digitalWrite(pinLedRojo, LOW);
    }

    void detectarObjeto() {
      int distancia = 0.01723 * readUltrasonicDistance();
      Serial.println(distancia);

      if (distancia < umbralDistancia && !objetoDetectado) {
        objetoDetectado = true; 
        contador++;
        Serial.print("Contador de objetos: ");
        Serial.println(contador);

   
        for (int i = 0; i < 3; i++) {  // Parpadea 3 veces
          digitalWrite(pinLedParpadeo, HIGH);
          delay(200);
          digitalWrite(pinLedParpadeo, LOW);
          delay(200);
        }

        actualizarLEDs();  // Actualiza el estado de los LEDs según el contador
      } else if (distancia >= umbralDistancia) {
        objetoDetectado = false;  // Resetea la detección para el próximo objeto
      }
    }

 
    void reiniciarContador() {
      contador = 0;
      objetoDetectado = false;
      digitalWrite(pinLedVerde, LOW);
      digitalWrite(pinLedAmarillo, LOW);
      digitalWrite(pinLedRojo, LOW);
    }

    int obtenerContador() {
      return contador;
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
