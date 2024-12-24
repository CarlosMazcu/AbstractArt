#include "../include/fractal.hpp"
#include "../include/image_utils.hpp"
#include <cmath>
#include <vector>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <iomanip>

Mandelbrot::Mandelbrot(unsigned int w, unsigned int h, float zoom, float moveX, float moveY, int maxIterations)
    : width(w), height(h), zoom(zoom), moveX(moveX), moveY(moveY), maxIterations(maxIterations) 
    {
        sat_r = 1.0f;
        sat_g = 0.7f;
        sat_b = 0.5f;
    }

std::vector<unsigned char> Mandelbrot::generateImage(std::string &imageName) {
    std::vector<unsigned char> image = generateMandelbrotImage();
    imageName = "../assets/mandelbrot_" + generateUniqueFileName();
    return image;
}



std::vector<unsigned char> Mandelbrot::generateMandelbrotImage() {
    std::vector<unsigned char> image(width * height * 4); // 4 canales: RGBA

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            float real = (x - width / 2.0f) / zoom + moveX;
            float imag = (y - height / 2.0f) / zoom + moveY;
            std::complex<float> c(real, imag);
            std::complex<float> z(0, 0);
            int iterations = 0;

            while (std::abs(z) <= 2.0f && iterations < maxIterations) {
                z = z * z + c;
                ++iterations;
            }

            // Color basado en el número de iteraciones
            unsigned char color = static_cast<unsigned char>(255 * float(iterations) / maxIterations);

            // Colorear de forma suave (gradientes en los canales RGB)
            unsigned char r = static_cast<unsigned char>(color * sat_r);
            unsigned char g = static_cast<unsigned char>(color * sat_g); // Menos saturación de verde
            unsigned char b = static_cast<unsigned char>(color * sat_b); // Menos saturación de azul

            image[(y * width + x) * 4] = r;   // R
            image[(y * width + x) * 4 + 1] = g; // G
            image[(y * width + x) * 4 + 2] = b; // B
            image[(y * width + x) * 4 + 3] = 255; // A (opacidad)
        }
    }

    return image;
}

// Métodos para ajustar los parámetros
void Mandelbrot::setZoom(float z) {
    zoom = z;
}

void Mandelbrot::setMoveX(float x) {
    moveX = x;
}

void Mandelbrot::setMoveY(float y) {
    moveY = y;
}

void Mandelbrot::setMaxIterations(int maxIter) {
    maxIterations = maxIter;
}

void Mandelbrot::setRGBsaturation(float r, float g, float b)
{
    sat_r = r > 1.0f ? 1.0f : r;
    sat_g = g > 1.0f ? 1.0f : g;
    sat_b = b > 1.0f ? 1.0f : b;
}

JuliaSet::JuliaSet(unsigned int w, unsigned int h, float zoom, float moveX, float moveY, float c_real, float c_imag, int maxIterations)
    : width(w), height(h), zoom(zoom), moveX(moveX), moveY(moveY), c(c_real, c_imag), maxIterations(maxIterations) 
{
    sat_r = 1.0f;
    sat_g = 0.7f;
    sat_b = 0.5f;
}

// Generar la imagen
std::vector<unsigned char> JuliaSet::generateImage(std::string &imageName) {
    std::vector<unsigned char> image = generateJuliaSetImage();
    imageName = "../assets/julia_set_" + generateUniqueFileName();
    return image;
}

// Generar los datos de la imagen del conjunto de Julia
std::vector<unsigned char> JuliaSet::generateJuliaSetImage() {
    std::vector<unsigned char> image(width * height * 4); // 4 canales: RGBA

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            // Convertir coordenadas de píxeles a coordenadas del plano complejo
            float real = (x - width / 2.0f) / zoom + moveX;
            float imag = (y - height / 2.0f) / zoom + moveY;
            std::complex<float> z(real, imag);

            int iterations = 0;
            while (std::abs(z) <= 2.0f && iterations < maxIterations) {
                z = z * z + c;  // Ecuación del conjunto de Julia
                ++iterations;
            }

            // Color basado en el número de iteraciones
            unsigned char color = static_cast<unsigned char>(255 * float(iterations) / maxIterations);

            // Colorear de forma suave (gradientes en los canales RGB)
            unsigned char r = static_cast<unsigned char>(color * sat_r);
            unsigned char g = static_cast<unsigned char>(color * sat_g);
            unsigned char b = static_cast<unsigned char>(color * sat_b);

            image[(y * width + x) * 4] = r;   // R
            image[(y * width + x) * 4 + 1] = g; // G
            image[(y * width + x) * 4 + 2] = b; // B
            image[(y * width + x) * 4 + 3] = 255; // A (opacidad)
        }
    }

    return image;
}

// Métodos para ajustar parámetros
void JuliaSet::setZoom(float z) {
    zoom = z;
}

void JuliaSet::setMoveX(float x) {
    moveX = x;
}

void JuliaSet::setMoveY(float y) {
    moveY = y;
}

void JuliaSet::setMaxIterations(int maxIter) {
    maxIterations = maxIter;
}

void JuliaSet::setComplexConstant(float c_real, float c_imag) {
    c = std::complex<float>(c_real, c_imag);
}

void JuliaSet::setRGBsaturation(float r, float g, float b) {
    sat_r = r > 1.0f ? 1.0f : r;
    sat_g = g > 1.0f ? 1.0f : g;
    sat_b = b > 1.0f ? 1.0f : b;
}