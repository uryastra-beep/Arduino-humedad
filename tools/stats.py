#!/usr/bin/env python3
"""Uso: python3 tools/stats.py ~/humedad.log [umbral=800]"""
import sys

path = sys.argv[1]
umbral = int(sys.argv[2]) if len(sys.argv) > 2 else 800
vals = []
for line in open(path, errors="ignore"):
    line = line.strip()
    if line.isdigit() and 0 <= int(line) <= 1023:
        vals.append(int(line))
if not vals:
    sys.exit("sin lecturas válidas")
h = sum(v < umbral for v in vals)
print(f"n={len(vals)} prom={sum(vals)/len(vals):.1f} min={min(vals)} max={max(vals)}")
print(f"humedad relativa media={(1023 - sum(vals)/len(vals))/1023:.1%}")
print(f"tiempo en húmedo (<{umbral})={h/len(vals):.1%}")
