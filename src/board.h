#ifndef BOARD_H
#define BOARD_H

// Representación del tablero usando bits
// Cada fila es un arreglo de unsigned char donde cada bit representa una celda
// Ancho del tablero debe ser múltiplo de 8

class Board {
public:
    // Constructor/Destructor
    bool initialize(int width, int height);
    void destroy();
    
    // Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getBytesPerRow() const { return bytesPerRow; }
    unsigned char** getBoard() const { return board; }
    
    // Operaciones del tablero
    void clear();
    void print() const;
    bool isRowFull(int row) const;
    void shiftRowsDown(int fromRow);
    int clearFullLines();
    
    // Acceso a bits
    bool getBit(int row, int col) const;
    void setBit(int row, int col, bool value);
    
private:
    int width;           // Ancho en celdas
    int height;          // Alto en filas
    int bytesPerRow;     // width/8 (bytes por fila)
    unsigned char** board; // Matriz dinámica [height][bytesPerRow]
};

#endif // BOARD_H