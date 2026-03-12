#include "game.h"
#include "pieces.h"
#include <iostream>
#include <conio.h> // Para Windows, para Linux usar ncurses o alternativa

Game::Game() : state(GAME_EXIT), currentPiece(0), currentRotation(0), 
               currentX(0), currentY(0) {}

Game::~Game() {
    board.destroy();
}

bool Game::start() {
    int w, h;
    
    // Solicitar dimensiones
    do {
        std::cout << "Ingrese ancho del tablero (múltiplo de 8, mínimo 8): ";
        std::cin >> w;
        std::cout << "Ingrese alto del tablero (mínimo 8): ";
        std::cin >> h;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            w = 0;
            h = 0;
        }
    } while (!board.initialize(w, h));
    
    state = GAME_RUNNING;
    generateNewPiece();
    
    return true;
}

void Game::run() {
    while (state == GAME_RUNNING) {
        displayGame();
        
        UserAction action = getUserAction();
        if (action == ACTION_EXIT) {
            state = GAME_EXIT;
            break;
        }
        
        processTurn(action);
    }
    
    if (state == GAME_OVER) {
        std::cout << "\n╔════════════════════╗\n";
        std::cout << "║    GAME OVER!      ║\n";
        std::cout << "╚════════════════════╝\n";
    }
}

UserAction Game::getUserAction() const {
    std::cout << "\nAcción (a=izq, d=der, s=bajar, w=rotar, q=salir): ";
    char c;
    std::cin >> c;
    
    switch (c) {
        case 'a': case 'A': return ACTION_LEFT;
        case 'd': case 'D': return ACTION_RIGHT;
        case 's': case 'S': return ACTION_DOWN;
        case 'w': case 'W': return ACTION_ROTATE;
        case 'q': case 'Q': return ACTION_EXIT;
        default: return ACTION_INVALID;
    }
}

bool Game::canPlace(int piece, int rotation, int x, int y) const {
    unsigned short shape[MAX_PIECE_HEIGHT];
    Pieces::getShape(piece, rotation, shape);
    
    int pieceHeight = Pieces::getHeight(piece, rotation);
    
    // Verificar bordes
    if (y < 0 || y + pieceHeight > board.getHeight()) return false;
    if (x < 0) return false;
    
    // Verificar colisiones con el tablero usando operadores de bits
    for (int row = 0; row < pieceHeight; ++row) {
        unsigned short pieceRow = shape[row];
        if (pieceRow == 0) continue;
        
        int boardRow = y + row;
        
        // Calcular qué bytes del tablero afecta esta fila
        int startByte = x / 8;
        int endByte = (x + 15) / 8; // Máximo 16 bits de ancho
        
        for (int byteIdx = startByte; byteIdx <= endByte && byteIdx < board.getBytesPerRow(); ++byteIdx) {
            unsigned char boardByte = board.getBoard()[boardRow][byteIdx];
            
            // Determinar qué bits de pieceRow corresponden a este byte
            int bitOffsetInPiece = (byteIdx * 8) - x;
            if (bitOffsetInPiece > 15) continue;
            if (bitOffsetInPiece + 8 <= 0) continue;
            
            // Extraer la parte relevante de pieceRow
            unsigned short piecePart;
            if (bitOffsetInPiece >= 0) {
                piecePart = pieceRow >> (16 - 8 - bitOffsetInPiece);
            } else {
                piecePart = pieceRow << (-bitOffsetInPiece);
            }
            piecePart &= 0xFF; // Solo 8 bits
            
            // Verificar colisión: si algún bit está en 1 en ambos
            if ((boardByte & static_cast<unsigned char>(piecePart)) != 0) {
                return false;
            }
        }
    }
    
    return true;
}

void Game::fixCurrentPiece() {
    unsigned short shape[MAX_PIECE_HEIGHT];
    Pieces::getShape(currentPiece, currentRotation, shape);
    
    int pieceHeight = Pieces::getHeight(currentPiece, currentRotation);
    
    // Fijar la pieza en el tablero usando OR de bits
    for (int row = 0; row < pieceHeight; ++row) {
        unsigned short pieceRow = shape[row];
        if (pieceRow == 0) continue;
        
        int boardRow = currentY + row;
        
        int startByte = currentX / 8;
        int endByte = (currentX + 15) / 8;
        
        for (int byteIdx = startByte; byteIdx <= endByte && byteIdx < board.getBytesPerRow(); ++byteIdx) {
            int bitOffsetInPiece = (byteIdx * 8) - currentX;
            
            unsigned short piecePart;
            if (bitOffsetInPiece >= 0) {
                piecePart = pieceRow >> (16 - 8 - bitOffsetInPiece);
            } else {
                piecePart = pieceRow << (-bitOffsetInPiece);
            }
            piecePart &= 0xFF;
            
            // OR para fijar la pieza
            board.getBoard()[boardRow][byteIdx] |= static_cast<unsigned char>(piecePart);
        }
    }
    
    // Limpiar filas completas
    int linesCleared = board.clearFullLines();
    if (linesCleared > 0) {
        std::cout << "¡" << linesCleared << " línea(s) eliminada(s)!\n";
    }
    
    // Generar nueva pieza
    generateNewPiece();
}

void Game::generateNewPiece() {
    currentPiece = Pieces::getRandomPiece();
    currentRotation = 0;
    currentX = (board.getWidth() - Pieces::getWidth(currentPiece, currentRotation)) / 2;
    currentY = 0;
    
    // Verificar Game Over
    if (!canPlace(currentPiece, currentRotation, currentX, currentY)) {
        state = GAME_OVER;
    }
}

bool Game::moveLeft() {
    if (canPlace(currentPiece, currentRotation, currentX - 1, currentY)) {
        currentX--;
        return true;
    }
    return false;
}

bool Game::moveRight() {
    if (canPlace(currentPiece, currentRotation, currentX + 1, currentY)) {
        currentX++;
        return true;
    }
    return false;
}

bool Game::moveDown() {
    if (canPlace(currentPiece, currentRotation, currentX, currentY + 1)) {
        currentY++;
        return true;
    } else {
        // No puede bajar más, fijar pieza
        fixCurrentPiece();
        return false;
    }
}

bool Game::rotate() {
    int newRotation = (currentRotation + 1) % Pieces::getNumRotations(currentPiece);
    if (canPlace(currentPiece, newRotation, currentX, currentY)) {
        currentRotation = newRotation;
        return true;
    }
    return false;
}

void Game::displayGame() const {
    // Limpiar pantalla (simulado)
    for (int i = 0; i < 30; ++i) std::cout << "\n";
    
    std::cout << "=== TETRIS (Versión Bits) ===\n";
    std::cout << "Tablero: " << board.getWidth() << "x" << board.getHeight() << "\n";
    
    // Obtener forma de la pieza actual
    unsigned short shape[MAX_PIECE_HEIGHT];
    Pieces::getShape(currentPiece, currentRotation, shape);
    int pieceHeight = Pieces::getHeight(currentPiece, currentRotation);
    
    // Mostrar tablero con pieza superpuesta
    std::cout << "\n┌";
    for (int i = 0; i < board.getWidth(); ++i) std::cout << "─";
    std::cout << "┐\n";
    
    for (int row = 0; row < board.getHeight(); ++row) {
        std::cout << "│";
        for (int col = 0; col < board.getWidth(); ++col) {
            bool isPiece = false;
            
            // Verificar si esta celda pertenece a la pieza actual
            if (row >= currentY && row < currentY + pieceHeight &&
                col >= currentX && col < currentX + 16) { // Máximo 16 bits
                int pieceRow = row - currentY;
                int pieceCol = col - currentX;
                if (pieceCol >= 0 && pieceCol < 16) {
                    unsigned short pieceRowBits = shape[pieceRow];
                    if (pieceRowBits & (1 << (15 - pieceCol))) {
                        isPiece = true;
                    }
                }
            }
            
            if (isPiece) {
                std::cout << "@"; // Pieza actual
            } else if (board.getBit(row, col)) {
                std::cout << "#"; // Bloques fijos
            } else {
                std::cout << "."; // Vacío
            }
        }
        std::cout << "│\n";
    }
    
    std::cout << "└";
    for (int i = 0; i < board.getWidth(); ++i) std::cout << "─";
    std::cout << "┘\n";
}

void Game::processTurn(UserAction action) {
    bool actionPerformed = false;
    
    switch (action) {
        case ACTION_LEFT:
            actionPerformed = moveLeft();
            break;
        case ACTION_RIGHT:
            actionPerformed = moveRight();
            break;
        case ACTION_DOWN:
            actionPerformed = moveDown();
            // moveDown() ya fija la pieza si no puede bajar
            break;
        case ACTION_ROTATE:
            actionPerformed = rotate();
            break;
        default:
            break;
    }
    
    // Si no se realizó acción o ya se fijó la pieza, continuar
}