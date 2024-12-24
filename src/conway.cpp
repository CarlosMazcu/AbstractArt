#include "../include/conway.hpp"
#include <cstdlib>
#include <ctime>


GameOfLife::GameOfLife(unsigned int w, unsigned int h): width(w), height(h) {
    grid.resize(height, std::vector<int>(width, 0));
    //srand(time(0)); // Semilla para valores aleatorios
    srand(54); // Semilla fija

    // Inicializar la cuadrícula con valores aleatorios
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            //grid[y][x] = rand() % 2; // Célula viva (1) o muerta (0)
            grid[y][x] = (rand() % 100 < 30) ? 1 : 0;
        }
    }
}

int GameOfLife::countNeighbors(int x, int y) {
    int count = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue; // Saltar la celda actual
            int nx = (x + dx + width) % width;  // Borde toroidal en X
            int ny = (y + dy + height) % height; // Borde toroidal en Y
            count += grid[ny][nx];
        }
    }
    return count;
}

void GameOfLife::nextGeneration() {
    std::vector<std::vector<int>> newGrid(height, std::vector<int>(width, 0));

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            int neighbors = countNeighbors(x, y);

            if (grid[y][x] == 1) { // Celda viva
                newGrid[y][x] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else { // Celda muerta
                newGrid[y][x] = (neighbors == 3) ? 1 : 0;
            }
        }
    }

    grid = newGrid; // Actualizar la cuadrícula
}

std::vector<unsigned char> GameOfLife::generateImage() {
    std::vector<unsigned char> image(width * height * 4, 0); // Imagen negra (RGBA)

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            int idx = (y * width + x) * 4;
            if (grid[y][x] == 1) {
                image[idx] = 255;     // Rojo
                image[idx + 1] = 255; // Verde
                image[idx + 2] = 255; // Azul
                image[idx + 3] = 255; // Alfa
            }
        }
    }
    return image;
}