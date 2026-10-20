# Sensor de humedad (Arduino Uno + sonda resistiva)

LED integrado (pin 13): parpadea en seco, fijo en húmedo.

## Cableado
- Un pin de la sonda a GND, el otro a A0. Sin VCC (usa el pull-up interno de A0).

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
