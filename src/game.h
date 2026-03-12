#ifndef GAME_H
#define GAME_H

#include "board.h"

// Estados del juego
enum GameState {
    GAME_RUNNING,
    GAME_OVER,
    GAME_EXIT
};

// Acciones del usuario
enum UserAction {
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_DOWN,
    ACTION_ROTATE,
    ACTION_EXIT,
    ACTION_INVALID
};

class Game {
public:
    Game();
    ~Game();
    
    // Inicialización
    bool start();
    
    // Bucle principal
    void run();
    
    // Obtener estado
    GameState getState() const { return state; }
    
private:
    Board board;
    GameState state;
    
    // Pieza actual
    int currentPiece;
    int currentRotation;
    int currentX;
    int currentY;
    
    // Función para leer acción del usuario
    UserAction getUserAction() const;
    
    // Funciones de movimiento con verificación de colisiones
    bool canPlace(int piece, int rotation, int x, int y) const;
    void fixCurrentPiece();
    void generateNewPiece();
    
    // Ejecutar acciones
    bool moveLeft();
    bool moveRight();
    bool moveDown();
    bool rotate();
    
    // Mostrar estado actual (con pieza superpuesta)
    void displayGame() const;
    
    // Procesamiento por turno
    void processTurn(UserAction action);
};

#endif // GAME_H