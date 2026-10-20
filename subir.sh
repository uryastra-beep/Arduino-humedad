#!/usr/bin/env bash
# Compila y sube el sketch al Arduino. Uso: ./subir.sh [monitor]
set -euo pipefail
cd "$(dirname "$0")"

PIO="$(command -v pio || true)"
[ -z "$PIO" ] && [ -x "$HOME/.platformio/penv/bin/pio" ] && PIO="$HOME/.platformio/penv/bin/pio"
if [ -z "$PIO" ]; then
  echo "PlatformIO no está instalado. Instálalo (CachyOS): sudo pacman -S platformio-core  o  pipx install platformio" >&2
  exit 1
fi

PUERTO="${PUERTO:-}"
if [ -z "$PUERTO" ]; then
  PUERTO="$(ls /dev/serial/by-id/* 2>/dev/null | head -n1 || true)"
  [ -z "$PUERTO" ] && PUERTO="$(ls /dev/ttyUSB* /dev/ttyACM* 2>/dev/null | head -n1 || true)"
fi
[ -z "$PUERTO" ] && { echo "No encuentro el Arduino. Revisa el cable USB." >&2; exit 1; }

if [ ! -r "$PUERTO" ] || [ ! -w "$PUERTO" ]; then
  echo "Dando acceso temporal a $PUERTO..."
  pkexec setfacl -m "u:$USER:rw" "$(readlink -f "$PUERTO")"
fi

"$PIO" run -t upload --upload-port "$PUERTO"
echo "Subido a $PUERTO."

if [ "${1:-}" = "monitor" ]; then
  exec "$PIO" device monitor -p "$PUERTO" -b 9600 --filter printable
fi
