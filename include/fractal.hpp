#ifndef __FRACTAL_HPP__
#define __FRACTAL_HPP__ 1

#include <vector>
#include <complex>
#include <string>

class Mandelbrot {
public:
    // Constructor con parámetros predeterminados
    Mandelbrot(unsigned int w, unsigned int h, float zoom = 200.0f, float moveX = -0.5f, float moveY = 0.0f, int maxIterations = 500);

    // Generar la imagen del fractal de Mandelbrot
    std::vector<unsigned char> generateImage(std::string &imageName);

    // Métodos para ajustar los parámetros
    void setZoom(float zoom);
    void setMoveX(float moveX);
    void setMoveY(float moveY);
    void setMaxIterations(int maxIterations);
    void setRGBsaturation(float r, float g, float b);

private:
    unsigned int width, height;
    float sat_r, sat_g, sat_b;
    float zoom, moveX, moveY;
    int maxIterations;
    std::vector<unsigned char> generateMandelbrotImage();
};

class JuliaSet {
public:
    // Constructor
    JuliaSet(unsigned int w, unsigned int h, float zoom = 200.0f, float moveX = 0.0f, float moveY = 0.0f, float c_real = -0.7f, float c_imag = 0.27015f, int maxIterations = 500);

    // Generar la imagen y devolver los datos RGBA
    std::vector<unsigned char> generateImage(std::string &imageName);

    // Métodos para ajustar los parámetros
    void setZoom(float z);
    void setMoveX(float x);
    void setMoveY(float y);
    void setMaxIterations(int maxIter);
    void setComplexConstant(float c_real, float c_imag);
    void setRGBsaturation(float r, float g, float b);

private:
    unsigned int width, height;
    float zoom, moveX, moveY;
    std::complex<float> c;  // Número complejo constante para Julia
    int maxIterations;
    float sat_r, sat_g, sat_b;  // Saturación RGB

    // Método para generar los datos de la imagen (interno)
    std::vector<unsigned char> generateJuliaSetImage();
};

#endif // FRACTAL_HPP
