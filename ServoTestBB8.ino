#include <Servo.h>

Servo servo1;
Servo servo2;

const int PIN_SERVO1 = 9;
const int PIN_SERVO2 = 10;
const int PIN_BOTON = 2;

const int DELAYS[] = { 20, 10, 3 };
const int NUM_NIVELES = 3;
int nivelActual = 0;

int angulo = 0;
int direccion = 1;

bool estadoBoton = HIGH;
bool estadoAnterior = HIGH;
unsigned long ultimoDebounce = 0;
const unsigned long DEBOUNCE_MS = 50;

unsigned long ultimoMovimiento = 0;

void setup() {
  servo1.attach(PIN_SERVO1);
  servo2.attach(PIN_SERVO2);
  pinMode(PIN_BOTON, INPUT_PULLUP);
}

void loop() {
  unsigned long ahora = millis();

  bool lectura = digitalRead(PIN_BOTON);
  if (lectura != estadoAnterior) ultimoDebounce = ahora;

  if ((ahora - ultimoDebounce) > DEBOUNCE_MS) {
    if (lectura != estadoBoton) {
      estadoBoton = lectura;
      if (estadoBoton == HIGH) {
        nivelActual = (nivelActual + 1) % NUM_NIVELES;
      }
    }
  }
  estadoAnterior = lectura;

  if (ahora - ultimoMovimiento >= (unsigned long)DELAYS[nivelActual]) {
    ultimoMovimiento = ahora;

    servo1.write(angulo);
    servo2.write(angulo);

    angulo += direccion;
    if (angulo >= 180 || angulo <= 0) direccion = -direccion;
  }
}