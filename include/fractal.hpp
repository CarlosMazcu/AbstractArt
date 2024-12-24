#ifndef __FRACTAL_HPP__
#define __FRACTAL_HPP__ 1

#include <vector>
#include <complex>
#include <string>

class Mandelbrot {
public:
    Mandelbrot(unsigned int w, unsigned int h, float zoom = 200.0f, float moveX = -0.5f, float moveY = 0.0f, int maxIterations = 500);

    // Generar la imagen del fractal de Mandelbrot
    std::vector<unsigned char> generateImage(std::string &imageName);

    // Métodos para ajustar los parámetros
    void setZoom(float zoom);
    void setMoveX(float moveX);
    void setMoveY(float moveY);
    void setMaxIterations(int maxIterations);
    void setRGBsaturation(float r, float g, float b);
    void setScapeRadius(float r);

private:
    unsigned int width, height;
    float sat_r, sat_g, sat_b;
    float scapeRadius;
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
    void setScapeRadius(float r);

private:
    unsigned int width, height;
    float zoom, moveX, moveY;
    float scapeRadius;
    std::complex<float> c;  // Número complejo constante para Julia
    int maxIterations;
    float sat_r, sat_g, sat_b;  // Saturación RGB

    // Método para generar los datos de la imagen (interno)
    std::vector<unsigned char> generateJuliaSetImage();
};



class Newton {

public:
    // Constructor
    Newton(unsigned int w, unsigned int h, float zoom = 1.0f, float moveX = 0.0f, float moveY = 0.0f, int maxIter = 100, float tol = 1e-6);

    // Generar imagen del fractal y devolver datos RGBA
    std::vector<unsigned char> generateImage(std::string& imageName);

    // Generar el fractal de Newton
    std::vector<unsigned char> generateNewtonImage();

    // Métodos para ajustar los parámetros
    void setZoom(float z) { zoom = z; }
    void setMoveX(float x) { moveX = x; }
    void setMoveY(float y) { moveY = y; }
    void setMaxIterations(int maxIter) { maxIterations = maxIter; }
    void setTolerance(float tol) { tolerance = tol; }
    void setRGBsaturation(float r, float g, float b) {
        sat_r = (r > 1.0f) ? 1.0f : r;
        sat_g = (g > 1.0f) ? 1.0f : g;
        sat_b = (b > 1.0f) ? 1.0f : b;
    }
    private:
        unsigned int width, height;  // Dimensiones de la imagen
        int maxIterations;          // Máximo de iteraciones
        float zoom;                 // Zoom para el fractal
        float moveX, moveY;         // Traslación del fractal
        float tolerance;            // Tolerancia para convergencia
        float sat_r, sat_g, sat_b;  // Saturación de colores RGB
};


#endif // FRACTAL_HPP
