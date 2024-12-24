#ifndef __CONWAY_HPP__
#define __CONWAY_HPP__ 1

#include <vector>


class GameOfLife {
public:
    GameOfLife(unsigned int w, unsigned int h);
    void nextGeneration();
    std::vector<unsigned char> generateImage();

private:
    unsigned int width, height;
    std::vector<std::vector<int>> grid;

    int countNeighbors(int x, int y);
};

#endif