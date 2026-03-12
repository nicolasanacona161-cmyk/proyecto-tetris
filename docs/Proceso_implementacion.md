# Proyecto : Tetris

## Lenguaje : C++

## framework : Qt

archivo de configuracion de Qt (framework para desarrollo

El archivo `tetris.pro` es un archivo de proyecto de  **qmake** , la herramienta de construcción de Qt. Su función es definir cómo se debe compilar y enlazar el proyecto.

### Contenido de `tetris.pro`

```
QT -= gui
CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
    src/main.cpp \
    src/board.cpp \
    src/pieces.cpp \
    src/game.cpp

HEADERS += \
    src/board.h \
    src/pieces.h \
    src/game.h

DEFINES += QT_NO_STRING
```

### Explicación línea por línea

#### 1. `QT -= gui`

* **Significado** : Elimina el módulo `gui` de Qt del proyecto.
* **Por qué** : Este es solo de consola, no necesita interfaz gráfica (ventanas, widgets, etc.). Se quita para evita enlazar bibliotecas innecesarias y poder reduci el tamaño del ejecutable.

#### 2. `CONFIG += c++11 console`

* **`c++11`** : Indica que se debe usar el estándar C++11 (o superior). Esto permite características como `nullptr`, rangos `for`, etc. El código proporcionado usa C++11.
* **`console`** : Le dice a qmake que la aplicación es una aplicación de consola (en Windows, esto hace que se genere un ejecutable que abre una terminal al ejecutarse.

#### 3. `CONFIG -= app_bundle`

* **Solo aplica en macOS** : Elimina la generación de un "app bundle" (carpeta con estructura de aplicación).

#### 4. `SOURCES += \ ...`

* Lista todos los archivos fuente `.cpp` que forman parte del proyecto. Cada archivo se compilará y enlazará.
* Las barras invertidas (`\`) permiten escribir la lista en varias líneas.

#### 5. `HEADERS += \ ...`

* Lista todos los archivos de cabecera `.h`. Aunque no se compilan directamente, son necesarios para que qmake genere dependencias y los incluya en el IDE.

#### 6. `DEFINES += QT_NO_STRING`

* **Significado** : Define una macro del preprocesador llamada `QT_NO_STRING`.
* **Propósito** : El desafío prohíbe explícitamente el uso de `std::string` y también de `QString` (que es la clase de cadenas de Qt). Al definir `QT_NO_STRING`, Qt deshabilita todas las funciones y clases relacionadas con `QString` (por ejemplo, `QString`, `QByteArray`, etc.), de modo que si accidentalmente se intenta usar, el compilador dará error. Es una forma de forzar el cumplimiento de la restricción "sin strings".
* **Nota** : Esta macro solo afecta a Qt, no a `std::string`. Pero como también está prohibido usar STL, no se debe incluir `<string>` ni usar `std::string`. Esta línea es una protección adicional para evitar el uso de `QString`.

### Otras configuraciones opcionales que podrías añadir

* **`CONFIG += warn_on`** : Activa todas las advertencias del compilador.
* **`QMAKE_CXXFLAGS += -Wall -Wextra`** : Agrega banderas específicas de advertencia (más allá de las de Qt).
* **`TARGET = tetris-bits`** : Define el nombre del ejecutable (por defecto toma el nombre de la carpeta).

### ¿Cómo se usa este archivo?

1. Desde la terminal: Se ejecuta `qmake tetris.pro` para generar un Makefile (o un proyecto de Visual Studio, según la plataforma).
2. Ejecuta:  `make` (o `mingw32-make` en Windows) para compilar.
3. Adicionalmente se puede abrir el archivo directamente en  **Qt Creator** , que leerá el `.pro` y configurará automáticamente el proyecto.

### Resumen

El `tetris.pro` es el corazón de la configuración de compilación. Asegura que:

* Se compile como aplicación de consola.
* Se use C++11.
* Se listen todos los archivos fuente.
* Se prohíba el uso de `QString` mediante `QT_NO_STRING`.
