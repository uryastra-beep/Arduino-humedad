# Sensor de humedad (Arduino Uno + sonda resistiva)

Tres LEDs indican el nivel de humedad:

| LED | Pin | Estado |
|---|---|---|
| Azul | D2 | Muy húmedo (< ~450) |
| Verde | D3 | Medio húmedo (~450–900) |
| Rojo | D4 | Seco (> ~800) |

El LED integrado (pin 13) parpadea en seco y queda fijo en húmedo.

## Cableado
- Un pin de la sonda a GND, el otro a A0. Sin VCC (usa el pull-up interno de A0).
- Cada LED: ánodo (pata larga) → resistencia 220 Ω → pin (D2/D3/D4); cátodo (pata corta) → GND.

## Subir
```bash
git clone https://github.com/uryastra-beep/Arduino-humedad.git
cd Arduino-humedad
./subir.sh            # compila y sube
./subir.sh monitor    # además abre el monitor serie
```
En VS Code: `Ctrl+Shift+B` ejecuta lo mismo.

Requiere PlatformIO (`pio`). El script detecta el puerto solo y pide permiso (pkexec) si hace falta; con otro puerto: `PUERTO=/dev/ttyUSB1 ./subir.sh`.
Cierra el monitor serie antes de volver a subir.

## Promedio
```bash
./subir.sh monitor | tee ~/humedad.log
python3 tools/stats.py ~/humedad.log 800
```
