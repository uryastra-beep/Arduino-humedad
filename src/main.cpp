#include <Arduino.h>

// Sonda resistiva sin VCC: pull-up interno de A0 + sonda a GND.
// Seco ~1023, húmedo baja (más bajo = más húmedo).
const uint8_t SENSOR = A0;
const uint8_t LED = LED_BUILTIN;

// Histéresis: entra en húmedo por debajo de ENTRA_HUMEDO,
// vuelve a seco solo por encima de SALE_HUMEDO.
const int ENTRA_HUMEDO = 800;
const int SALE_HUMEDO = 900;
const uint8_t MUESTRAS = 8;

bool humedo = false;

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
}

void loop() {
  int v = leer();
  if (!humedo && v < ENTRA_HUMEDO) humedo = true;
  else if (humedo && v > SALE_HUMEDO) humedo = false;

  Serial.println(v);
  digitalWrite(LED, humedo ? HIGH : (millis() / 300) % 2);
  delay(50);
}
