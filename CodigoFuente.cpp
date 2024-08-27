#define TRIG_PIN 15
#define ECHO_PIN 2
#define LED_VERDE 19
#define LED_AMARILLO 17
#define LED_ROJO 5
#define LED_INDICADOR 33

class UltrasonicSensor {
  private:
    int trigPin;
    int echoPin;
    long duration;
    float distance;

  public:
    UltrasonicSensor(int trig, int echo) {
      trigPin = trig;
      echoPin = echo;
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }

    float getDistance() {
      // Envía un pulso de 10 microsegundos para activar el sensor
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      // Lee el tiempo de respuesta del sensor
      duration = pulseIn(echoPin, HIGH);

      // Calcula la distancia en centímetros
      distance = (duration / 2.0) * 0.0344;
      return distance;
    }
};

class LEDController {
  private:
    int greenLED;
    int yellowLED;
    int redLED;
    int indicatorLED;

  public:
    LEDController(int green, int yellow, int red, int indicator) {
      greenLED = green;
      yellowLED = yellow;
      redLED = red;
      indicatorLED = indicator;

      pinMode(greenLED, OUTPUT);
      pinMode(yellowLED, OUTPUT);
      pinMode(redLED, OUTPUT);
      pinMode(indicatorLED, OUTPUT);
      
      // Apagar todos los LEDs al inicio
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, LOW);
      digitalWrite(indicatorLED, LOW);
    }

    void setIndicator(bool state) {
      digitalWrite(indicatorLED, state ? HIGH : LOW);
    }

    void updateLEDs(int objectCount) {
      if (objectCount < 5) {
        digitalWrite(greenLED, HIGH);
        digitalWrite(yellowLED, LOW);
        digitalWrite(redLED, LOW);
      } else if (objectCount < 10) {
        digitalWrite(greenLED, LOW);
        digitalWrite(yellowLED, HIGH);
        digitalWrite(redLED, LOW);
      } else {
        digitalWrite(greenLED, LOW);
        digitalWrite(yellowLED, LOW);
        digitalWrite(redLED, HIGH);
      }
    }
};

class ObjectCounter {
  private:
    UltrasonicSensor& sensor;
    LEDController& ledController;
    int objectCount;
    float lastDistance;

  public:
    ObjectCounter(UltrasonicSensor& sensorObj, LEDController& ledCtrl) 
      : sensor(sensorObj), ledController(ledCtrl), objectCount(0), lastDistance(0) {}

    void update() {
      float distance = sensor.getDistance();
      Serial.print("Distancia: ");
      Serial.print(distance);
      Serial.println(" cm");

      if (lastDistance > 10 && distance <= 10) {
        objectCount++;
        Serial.print("Objetos contados: ");
        Serial.println(objectCount);
        ledController.setIndicator(true);
      } else if (distance > 10) {
        ledController.setIndicator(false);
      }

      ledController.updateLEDs(objectCount);
      lastDistance = distance;
    }
};

// Declaración de instancias globales
UltrasonicSensor sensor(TRIG_PIN, ECHO_PIN);
LEDController ledController(LED_VERDE, LED_AMARILLO, LED_ROJO, LED_INDICADOR);
ObjectCounter objectCounter(sensor, ledController);

void setup() {
  Serial.begin(115200);
}

void loop() {
  objectCounter.update();
  delay(200);
}