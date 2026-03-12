#include "pieces.h"
#include <cstdlib>
#include <ctime>

// Inicialización de las constantes (máscaras de bits)
// Formato: cada unsigned short representa una fila de 16 bits
// Los bits se leen de izquierda a derecha (MSB a LSB)

// Pieza I (línea)
const unsigned short Pieces::I_SHAPES[2][4] = {
    {0b1111000000000000, 0b0000000000000000, 0b0000000000000000, 0b0000000000000000}, // Horizontal
    {0b1000000000000000, 0b1000000000000000, 0b1000000000000000, 0b1000000000000000}  // Vertical
};

// Pieza O (cuadrado)
const unsigned short Pieces::O_SHAPES[1][4] = {
    {0b1100000000000000, 0b1100000000000000, 0b0000000000000000, 0b0000000000000000}
};

// Pieza T
const unsigned short Pieces::T_SHAPES[4][4] = {
    {0b1110000000000000, 0b0100000000000000, 0b0000000000000000, 0b0000000000000000}, // 0°
    {0b0100000000000000, 0b1100000000000000, 0b0100000000000000, 0b0000000000000000}, // 90°
    {0b0100000000000000, 0b1110000000000000, 0b0000000000000000, 0b0000000000000000}, // 180°
    {0b1000000000000000, 0b1100000000000000, 0b1000000000000000, 0b0000000000000000}  // 270°
};

// Pieza S
const unsigned short Pieces::S_SHAPES[2][4] = {
    {0b0110000000000000, 0b1100000000000000, 0b0000000000000000, 0b0000000000000000}, // 0°
    {0b1000000000000000, 0b1100000000000000, 0b0100000000000000, 0b0000000000000000}  // 90°
};

// Pieza Z
const unsigned short Pieces::Z_SHAPES[2][4] = {
    {0b1100000000000000, 0b0110000000000000, 0b0000000000000000, 0b0000000000000000}, // 0°
    {0b0100000000000000, 0b1100000000000000, 0b1000000000000000, 0b0000000000000000}  // 90°
};

// Pieza J
const unsigned short Pieces::J_SHAPES[4][4] = {
    {0b1000000000000000, 0b1110000000000000, 0b0000000000000000, 0b0000000000000000}, // 0°
    {0b1100000000000000, 0b1000000000000000, 0b1000000000000000, 0b0000000000000000}, // 90°
    {0b1110000000000000, 0b0010000000000000, 0b0000000000000000, 0b0000000000000000}, // 180°
    {0b0100000000000000, 0b0100000000000000, 0b1100000000000000, 0b0000000000000000}  // 270°
};

// Pieza L
const unsigned short Pieces::L_SHAPES[4][4] = {
    {0b0010000000000000, 0b1110000000000000, 0b0000000000000000, 0b0000000000000000}, // 0°
    {0b1000000000000000, 0b1000000000000000, 0b1100000000000000, 0b0000000000000000}, // 90°
    {0b1110000000000000, 0b1000000000000000, 0b0000000000000000, 0b0000000000000000}, // 180°
    {0b1100000000000000, 0b0100000000000000, 0b0100000000000000, 0b0000000000000000}  // 270°
};

// Alturas
const int Pieces::I_HEIGHTS[2] = {1, 4};
const int Pieces::O_HEIGHTS[1] = {2};
const int Pieces::T_HEIGHTS[4] = {2, 3, 2, 3};
const int Pieces::S_HEIGHTS[2] = {2, 3};
const int Pieces::Z_HEIGHTS[2] = {2, 3};
const int Pieces::J_HEIGHTS[4] = {2, 3, 2, 3};
const int Pieces::L_HEIGHTS[4] = {2, 3, 2, 3};

void Pieces::getShape(int pieceType, int rotation, unsigned short* buffer) {
    // Inicializar buffer con ceros
    for (int i = 0; i < MAX_PIECE_HEIGHT; ++i) {
        buffer[i] = 0;
    }
    
    // Validar rotación
    rotation = rotation % getNumRotations(pieceType);
    
    // Copiar la forma correspondiente
    switch (pieceType) {
        case PIECE_I:
            for (int i = 0; i < 4; ++i) buffer[i] = I_SHAPES[rotation][i];
            break;
        case PIECE_O:
            for (int i = 0; i < 4; ++i) buffer[i] = O_SHAPES[rotation][i];
            break;
        case PIECE_T:
            for (int i = 0; i < 4; ++i) buffer[i] = T_SHAPES[rotation][i];
            break;
        case PIECE_S:
            for (int i = 0; i < 4; ++i) buffer[i] = S_SHAPES[rotation][i];
            break;
        case PIECE_Z:
            for (int i = 0; i < 4; ++i) buffer[i] = Z_SHAPES[rotation][i];
            break;
        case PIECE_J:
            for (int i = 0; i < 4; ++i) buffer[i] = J_SHAPES[rotation][i];
            break;
        case PIECE_L:
            for (int i = 0; i < 4; ++i) buffer[i] = L_SHAPES[rotation][i];
            break;
    }
}

int Pieces::getWidth(int pieceType, int rotation) {
    // Ancho máximo es 3 (excepto I horizontal que es 4)
    unsigned short buffer[MAX_PIECE_HEIGHT];
    getShape(pieceType, rotation, buffer);
    
    int maxWidth = 0;
    for (int i = 0; i < MAX_PIECE_HEIGHT; ++i) {
        unsigned short row = buffer[i];
        for (int bit = 15; bit >= 0; --bit) {
            if (row & (1 << bit)) {
                int col = 15 - bit;
                if (col + 1 > maxWidth) maxWidth = col + 1;
            }
        }
    }
    return maxWidth;
}

int Pieces::getHeight(int pieceType, int rotation) {
    switch (pieceType) {
        case PIECE_I: return I_HEIGHTS[rotation % 2];
        case PIECE_O: return O_HEIGHTS[rotation % 1];
        case PIECE_T: return T_HEIGHTS[rotation % 4];
        case PIECE_S: return S_HEIGHTS[rotation % 2];
        case PIECE_Z: return Z_HEIGHTS[rotation % 2];
        case PIECE_J: return J_HEIGHTS[rotation % 4];
        case PIECE_L: return L_HEIGHTS[rotation % 4];
        default: return 0;
    }
}

int Pieces::getNumRotations(int pieceType) {
    switch (pieceType) {
        case PIECE_I: return 2;
        case PIECE_O: return 1;
        case PIECE_T: return 4;
        case PIECE_S: return 2;
        case PIECE_Z: return 2;
        case PIECE_J: return 4;
        case PIECE_L: return 4;
        default: return 1;
    }
}

int Pieces::getRandomPiece() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seeded = true;
    }
    return std::rand() % NUM_PIECES;
}