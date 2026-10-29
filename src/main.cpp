#include <Arduino.h>

// Sonda resistiva sin VCC: pull-up interno de A0 + sonda a GND.
// Seco ~1023, húmedo baja (más bajo = más húmedo).
const uint8_t SENSOR = A0;
const uint8_t LED_AZUL = 2;   // muy húmedo
const uint8_t LED_VERDE = 3;  // medio húmedo
const uint8_t LED_ROJO = 4;   // seco
const uint8_t LED = LED_BUILTIN;

// Umbrales con histéresis (entrada < / salida >) para que no oscile.
const int SECO_A_MEDIO = 800;
const int MEDIO_A_SECO = 900;
const int MEDIO_A_MUY = 450;
const int MUY_A_MEDIO = 550;
const uint8_t MUESTRAS = 8;

enum Estado { SECO, MEDIO, MUY };
Estado estado = SECO;

int leer() {
  long suma = 0;
  for (uint8_t i = 0; i < MUESTRAS; i++) {
    suma += analogRead(SENSOR);
    delay(2);
  }
  return suma / MUESTRAS;
}

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
}

void loop() {
  int v = leer();

  if (estado == SECO && v < SECO_A_MEDIO) estado = MEDIO;
  if (estado == MEDIO && v < MEDIO_A_MUY) estado = MUY;
  else if (estado == MEDIO && v > MEDIO_A_SECO) estado = SECO;
  else if (estado == MUY && v > MUY_A_MEDIO) estado = MEDIO;

  digitalWrite(LED_AZUL, estado == MUY);
  digitalWrite(LED_VERDE, estado == MEDIO);
  digitalWrite(LED_ROJO, estado == SECO);
  digitalWrite(LED, estado == SECO ? (millis() / 300) % 2 : HIGH);

  Serial.println(v);
  delay(50);
}
