#ifndef __PERLIN_HPP__
#define __PERLIN_HPP__ 1

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
class PerlinNoise {
public:
    PerlinNoise(unsigned int w, unsigned int h);
    std::vector<unsigned char> generateImage(std::string &imageName);
    
    void setScale(int s){scale = s;}
    void setMode(int m){mode = m;}

    int getScale(){return scale;}
    int getMode(){return mode;}
private:
    std::vector<int> p;
    int mode;
    int scale;
    unsigned int width, height;

    float noise(float x, float y);
    float fade(float t);
    float lerp(float a, float b, float t);
    float grad(int hash, float x, float y);
};

class SimplexNoise
{
public:
    SimplexNoise(int w, int h) {
        initializePermutation();
        scale = 10;
        width = w;
        height = h;

    }
    std::vector<unsigned char> generateImage(std::string& imageName);
    void setScale(double sc) { scale = sc; }

private:
    const std::vector<std::vector<int>> grad2 = {
        {1, 1}, {-1, 1}, {1, -1}, {-1, -1},
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    double noise(double xin, double yin);

    std::vector<int> perm; // Permutación de gradientes

    double dot(const std::vector<int>& g, double x, double y) {
        return g[0] * x + g[1] * y;
    }

    void initializePermutation();

    double scale;
    int width, height;
};

#endif
