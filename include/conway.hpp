#ifndef __CONWAY_HPP__
#define __CONWAY_HPP__ 1

#include <vector>

/**
 * @class GameOfLife
 * @brief Simulates Conway's Game of Life, a cellular automaton.
 *
 * This class models the Game of Life on a 2D grid, supporting state evolution
 * and generating visual output as an image.
 */
class GameOfLife {
public:
    /**
     * @brief Constructs a GameOfLife instance with a given grid size.
     *
     * The grid is initialized with random cells (alive or dead) based on a fixed probability.
     *
     * @param w Width of the grid.
     * @param h Height of the grid.
     */
    GameOfLife(unsigned int w, unsigned int h);
    /**
     * @brief Advances the grid to the next generation.
     *
     * Applies the rules of Conway's Game of Life:
     * - A live cell with 2 or 3 neighbors survives.
     * - A dead cell with exactly 3 neighbors becomes alive.
     * - All other cells die or remain dead.
     */
    void nextGeneration();
    /**
     * @brief Generates an RGBA image of the current grid state.
     *
     * Each cell is mapped to a pixel:
     * - Alive cells are white.
     * - Dead cells are black.
     *
     * @return std::vector<unsigned char> A vector containing the image in RGBA format.
     */
    std::vector<unsigned char> generateImage();

private:
    unsigned int width; /**< Width of the grid. */
    unsigned int height; /**< Height of the grid. */
    std::vector<std::vector<int>> grid; /**< 2D grid representing cell states (0 = dead, 1 = alive). */
    /**
     * @brief Counts the number of alive neighbors for a given cell.
     *
     * Uses toroidal wrapping to handle edges, allowing neighbors to wrap around
     * to the opposite side of the grid.
     *
     * @param x X-coordinate of the cell.
     * @param y Y-coordinate of the cell.
     * @return int Number of alive neighbors.
     */
    int countNeighbors(int x, int y);
};

#endif