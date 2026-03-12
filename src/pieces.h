#ifndef PIECES_H
#define PIECES_H

// Tipos de piezas disponibles
enum PieceType {
    PIECE_I = 0,
    PIECE_O,
    PIECE_T,
    PIECE_S,
    PIECE_Z,
    PIECE_J,
    PIECE_L,
    NUM_PIECES
};

// Cada pieza tiene hasta 4 filas de ancho, representadas en bytes
// Usamos unsigned short (16 bits) para soportar hasta 16 columnas
// Esto permite tableros de hasta 16 de ancho (mínimo 8, múltiplo de 8)
#define MAX_PIECE_WIDTH 16
#define MAX_PIECE_HEIGHT 4

class Pieces {
public:
    // Obtener la forma de una pieza en una rotación específica
    // buffer debe tener tamaño MAX_PIECE_HEIGHT
    static void getShape(int pieceType, int rotation, unsigned short* buffer);
    
    // Obtener dimensiones de la pieza
    static int getWidth(int pieceType, int rotation);
    static int getHeight(int pieceType, int rotation);
    
    // Número de rotaciones por pieza
    static int getNumRotations(int pieceType);
    
    // Generar pieza aleatoria
    static int getRandomPiece();
    
private:
    // Máscaras de bits para cada pieza en cada rotación
    // Almacenadas como unsigned short (16 bits)
    static const unsigned short I_SHAPES[2][4];     // I: 2 rotaciones
    static const unsigned short O_SHAPES[1][4];     // O: 1 rotación
    static const unsigned short T_SHAPES[4][4];     // T: 4 rotaciones
    static const unsigned short S_SHAPES[2][4];     // S: 2 rotaciones
    static const unsigned short Z_SHAPES[2][4];     // Z: 2 rotaciones
    static const unsigned short J_SHAPES[4][4];     // J: 4 rotaciones
    static const unsigned short L_SHAPES[4][4];     // L: 4 rotaciones
    
    // Alturas de cada pieza por rotación
    static const int I_HEIGHTS[2];
    static const int O_HEIGHTS[1];
    static const int T_HEIGHTS[4];
    static const int S_HEIGHTS[2];
    static const int Z_HEIGHTS[2];
    static const int J_HEIGHTS[4];
    static const int L_HEIGHTS[4];
};

#endif // PIECES_H