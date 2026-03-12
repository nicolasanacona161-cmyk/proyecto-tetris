# Tetris por Manipulación de Bits en C++/Qt

## Descripción
Implementación de una versión simplificada del juego Tetris utilizando operadores a nivel de bits para representar el tablero y las piezas. 
Desarrollado en C++ con Qt, sin usar STL, strings, ni sintaxis ANSI C.

## Requisitos
- Qt 5.x o superior
- Compilador C++11

## Estructura del Proyecto
src/: Código fuente
board.h/cpp: Manejo del tablero con bits
pieces.h/cpp: Definición de tetriminos
game.h/cpp: Lógica del juego
main.cpp: Punto de entrada

### Controles
a: Mover izquierda
d: Mover derecha
s: Bajar
w: Rotar
q: Salir

## Características
Tablero configurable (ancho múltiplo de 8)
7 tetriminos clásicos
Rotaciones usando máscaras predefinidas
Detección de colisiones con operadores de bits
Limpieza de filas mediante manipulación de punteros
Memoria dinámica para el tablero
Sin STL, strings, ni sintaxis C

## Compilación
```bash
qmake tetris.pro
make

## Ejecucion
./tetris-bits
```