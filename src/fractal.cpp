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
        scapeRadius = 2.0f;
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

            while (std::abs(z) <= scapeRadius && iterations < maxIterations) {
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

void Mandelbrot::setScapeRadius(float r)
{
    if (r < 1.2f)
    {
        scapeRadius = 1.2f;
    }
    else if (r > 4.0f)
    {
        scapeRadius = 4.0f;
    }
    else {
        scapeRadius = r;
    }

}

JuliaSet::JuliaSet(unsigned int w, unsigned int h, float zoom, float moveX, float moveY, float c_real, float c_imag, int maxIterations)
    : width(w), height(h), zoom(zoom), moveX(moveX), moveY(moveY), c(c_real, c_imag), maxIterations(maxIterations) 
{
    sat_r = 1.0f;
    sat_g = 0.7f;
    sat_b = 0.5f;
    scapeRadius = 2.0f;
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
            while (std::abs(z) <= scapeRadius && iterations < maxIterations) {
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

void JuliaSet::setScapeRadius(float r)
{
    if (r < 1.2f )
    {
        scapeRadius = 1.2f;
    }
    else if(r > 4.0f)
    {
        scapeRadius = 4.0f;
    }
    else {
        scapeRadius = r;
    }
 
}

Newton::Newton(unsigned int w, unsigned int h, float zoom, float moveX, float moveY, int maxIter, float tol)
        : width(w), height(h), zoom(zoom), moveX(moveX), moveY(moveY), maxIterations(maxIter), tolerance(tol) {
        sat_r = 1.0f;
        sat_g = 0.7f;
        sat_b = 0.5f;
}

std::vector<unsigned char> Newton::generateImage(std::string& imageName)
{
    std::vector<unsigned char> image = generateNewtonImage();
    imageName = "../assets/newton_" + generateUniqueFileName();
    return image;
}

std::vector<unsigned char> Newton::generateNewtonImage() {
    std::vector<unsigned char> image(width * height * 4); // 4 canales: RGBA

    // Para cada píxel de la imagen
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            // Convertir las coordenadas a un espacio complejo
            float real = (x - width / 2.0f) / zoom + moveX;
            float imag = (y - height / 2.0f) / zoom + moveY;
            std::complex<double> z(real, imag);

            int iterations = 0;
            const int maxIterations = 100;  // Número máximo de iteraciones para el método de Newton
            double tolerance = 1e-6;  // Tolerancia de convergencia

            // Iteración de Newton
            while (iterations < maxIterations) {
                // f(z) = z^3 - 1
                std::complex<double> fz = std::pow(z, 3) - std::complex<double>(1.0);
                std::complex<double> fz_prime = 3.0 * std::pow(z, 2); // Derivada de f(z): 3z^2
                std::complex<double> z_new = z - fz / fz_prime;

                // Verificar la convergencia
                if (std::abs(z_new - z) < tolerance) {
                    break;
                }

                z = z_new;  // Actualizar z
                ++iterations;
            }

            // Mapear el número de iteraciones a un valor de color
            unsigned char color = static_cast<unsigned char>(255 * float(iterations) / maxIterations);

            // Colorear la imagen con una saturación específica
            unsigned char r = static_cast<unsigned char>(color * sat_r);
            unsigned char g = static_cast<unsigned char>(color * sat_g);
            unsigned char b = static_cast<unsigned char>(color * sat_b);

            // Asignar los valores a la imagen
            image[(y * width + x) * 4] = r;   // R
            image[(y * width + x) * 4 + 1] = g; // G
            image[(y * width + x) * 4 + 2] = b; // B
            image[(y * width + x) * 4 + 3] = 255; // A (opacidad)
        }
    }

    return image;
}
