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

#endif
