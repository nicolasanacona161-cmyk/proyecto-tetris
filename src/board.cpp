#include "board.h"
#include <iostream>
#include <cstdlib>

bool Board::initialize(int w, int h) {
    // Validaciones: mínimo 8, múltiplo de 8
    if (w < 8 || h < 8 || w % 8 != 0) {
        std::cerr << "Error: El ancho debe ser múltiplo de 8 y mínimo 8\n";
        return false;
    }
    
    width = w;
    height = h;
    bytesPerRow = width / 8;
    
    // Asignar memoria dinámica: arreglo de punteros a filas
    board = new unsigned char*[height];
    if (!board) return false;
    
    // Asignar cada fila
    for (int i = 0; i < height; ++i) {
        board[i] = new unsigned char[bytesPerRow];
        if (!board[i]) {
            // Liberar memoria asignada hasta ahora
            for (int j = 0; j < i; ++j) {
                delete[] board[j];
            }
            delete[] board;
            return false;
        }
    }
    
    clear();
    return true;
}

void Board::destroy() {
    if (board) {
        for (int i = 0; i < height; ++i) {
            delete[] board[i];
        }
        delete[] board;
        board = nullptr;
    }
    width = 0;
    height = 0;
    bytesPerRow = 0;
}

void Board::clear() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < bytesPerRow; ++j) {
            board[i][j] = 0;
        }
    }
}

void Board::print() const {
    // Encabezado
    std::cout << "\n┌";
    for (int i = 0; i < width; ++i) std::cout << "─";
    std::cout << "┐\n";
    
    // Filas del tablero
    for (int i = 0; i < height; ++i) {
        std::cout << "│";
        for (int j = 0; j < width; ++j) {
            if (getBit(i, j)) {
                std::cout << "#";
            } else {
                std::cout << ".";
            }
        }
        std::cout << "│\n";
    }
    
    // Borde inferior
    std::cout << "└";
    for (int i = 0; i < width; ++i) std::cout << "─";
    std::cout << "┘\n";
}

bool Board::getBit(int row, int col) const {
    if (row < 0 || row >= height || col < 0 || col >= width) return false;
    int byteIndex = col / 8;
    int bitIndex = 7 - (col % 8); // MSB primero para consistencia visual
    return (board[row][byteIndex] >> bitIndex) & 1;
}

void Board::setBit(int row, int col, bool value) {
    if (row < 0 || row >= height || col < 0 || col >= width) return;
    int byteIndex = col / 8;
    int bitIndex = 7 - (col % 8);
    
    if (value) {
        board[row][byteIndex] |= (1 << bitIndex);
    } else {
        board[row][byteIndex] &= ~(1 << bitIndex);
    }
}

bool Board::isRowFull(int row) const {
    for (int j = 0; j < bytesPerRow; ++j) {
        if (board[row][j] != 0xFF) return false; // 0xFF = todos bits 1
    }
    return true;
}

void Board::shiftRowsDown(int fromRow) {
    // Mover todas las filas desde fromRow hacia abajo
    for (int i = fromRow; i > 0; --i) {
        // Intercambiar punteros (operación O(1) por fila)
        unsigned char* temp = board[i];
        board[i] = board[i-1];
        board[i-1] = temp;
    }
    // La fila 0 queda vacía
    for (int j = 0; j < bytesPerRow; ++j) {
        board[0][j] = 0;
    }
}

int Board::clearFullLines() {
    int linesCleared = 0;
    int currentRow = height - 1;
    
    while (currentRow >= 0) {
        if (isRowFull(currentRow)) {
            shiftRowsDown(currentRow);
            linesCleared++;
            // No incrementamos currentRow porque la fila que bajó
            // ahora está en currentRow + 1 (la verificamos de nuevo)
        } else {
            currentRow--;
        }
    }
    
    return linesCleared;
}