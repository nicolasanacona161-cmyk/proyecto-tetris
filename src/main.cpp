#include "game.h"
#include <iostream>

// Esto es para soportar la codificacion UTF8 para que salgan bien los caracteres de
// pantalla
#ifdef _WIN32
#include <windows.h>
#endif


int main() {
#ifdef _WIN32
    // Cambiar la salida de consola a UTF-8
    SetConsoleOutputCP(CP_UTF8);
    // También cambiar la entrada si lees caracteres especiales (opcional)
    SetConsoleCP(CP_UTF8);
#endif
    std::cout << "╔════════════════════════════╗\n";
    std::cout << "║    TETRIS por Bits v1.0    ║\n";
    std::cout << "╚════════════════════════════╝\n\n";
    
    Game game;
    
    if (game.start()) {
        game.run();
    }
    
    std::cout << "\n¡Gracias por jugar!\n";
    return 0;
}