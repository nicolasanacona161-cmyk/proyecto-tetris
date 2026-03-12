# Informe Preliminar - Tetris por Bits (Marzo 13)

## 1. Análisis del Problema

### Contexto

Se requiere implementar un motor de Tetris por turnos en consola, donde cada celda del tablero se representa como un bit para optimizar el uso de memoria y permitir operaciones eficientes mediante operadores bitwise.

### Restricciones Clave

- Ancho del tablero: múltiplo de 8, mínimo 8
- Sin uso de STL, strings, ni sintaxis ANSI C
- Uso obligatorio de memoria dinámica y punteros
- Operaciones de bits para: movimientos, colisiones, rotaciones, limpieza de filas

### Consideraciones de Diseño

1. **Representación del tablero**: Matriz de `unsigned char` donde cada bit es una celda
2. **Piezas**: Máscaras de 16 bits (unsigned short) para soportar hasta 16 columnas
3. **Rotaciones**: Predefinidas para cada pieza (simplifica el cálculo)
4. **Colisiones**: Comparación AND entre bits de pieza y tablero

## 2. Diseño de Estructuras de Datos

### Tablero

```cpp
class Board {
    int width;           // Ancho en celdas
    int height;          // Alto en filas
    int bytesPerRow;     // width/8
    unsigned char** board; // [height][bytesPerRow]
};
```

### Justificación:

Usar unsigned char permite manipular 8 celdas por byte.
El doble puntero facilita el desplazamiento de filas durante la limpieza.

### Piezas

#### En cpp

```cpp
// Máscaras predefinidas para cada rotación
const unsigned short I_SHAPES[2][4] = {
    {0b1111000000000000, ...}, // Horizontal
    {0b1000000000000000, ...}  // Vertical
};
Justificación: Precalcular rotaciones evita operaciones complejas en tiempo real y mantiene el uso de bits.
```

## 3. Esquema de Tareas

### 1. Módulo Board

* Reserva dinámica de memoria
* Liberación de memoria
* Impresión en consola
* Acceso a bits individuales
* Detección de filas completas
* Desplazamiento de filas

### 2. Módulo Pieces

* Definición de máscaras (7 piezas)
* Funciones de acceso
* Selección aleatoria

### 3. Módulo Game

* Detección de colisiones
* Movimientos
* Rotaciones
* Fijación de piezas
* Game Over

## 4. Problemas Potenciales y Soluciones

Problema							Solución Propuesta
Desbordamiento de bits				Usar tipos fijos (unsigned char/short)
Fragmentación de memoria			Asignar filas contiguas
Eficiencia en colisiones			Operaciones bitwise en lugar de bucles
Límites del tablero					Validaciones en cada movimiento

## 5. Próximos Pasos

* Implementar módulo Board completo
* Probar con tableros de diferentes tamaños
* Implementar colisiones básicas
