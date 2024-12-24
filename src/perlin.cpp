#include <vector>
#include <cmath>
#include <iostream>
#include "../include/perlin.hpp"
#include "../include/image_utils.hpp"

PerlinNoise::PerlinNoise(unsigned int w, unsigned int h) {
    width = w;
    height = h;
    scale = 20;
    mode = 2;
    p = std::vector<int>(512);
    
    std::random_device rd;
    std::mt19937 gen(rd());  // Motor de números aleatorios
    std::uniform_int_distribution<int> dis(0, 255);  // Distribución uniforme entre 0 y 255

    for (int i = 0; i < 256; i++) {
        p[i] = dis(gen);  // Asignamos valores aleatorios
    }

    for (int i = 0; i < 256; i++) {
        p[i + 256] = p[i];
    }
}

float PerlinNoise::noise(float x, float y) {
    int X = static_cast<int>(floor(x)) & 255;
    int Y = static_cast<int>(floor(y)) & 255;

    float xf = x - floor(x);
    float yf = y - floor(y);

    float u = fade(xf);
    float v = fade(yf);

    int aa = p[X] + Y;
    int ab = p[X] + Y + 1;
    int ba = p[X + 1] + Y;
    int bb = p[X + 1] + Y + 1;

    float x1 = lerp(grad(p[aa], xf, yf), grad(p[ba], xf - 1, yf), u);
    float x2 = lerp(grad(p[ab], xf, yf - 1), grad(p[bb], xf - 1, yf - 1), u);

    return (lerp(x1, x2, v) + 1) / 2; 
}

 std::vector<unsigned char> PerlinNoise::generateImage(std::string &imageName)
 {
     std::vector<unsigned char> i(width * height * 4); // 4 channels: RGBA
    if (mode > 3) mode = 0;
    unsigned char color = 0;
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    for (unsigned int y = 0; y < height; y++) {
        float ny = y / static_cast<float>(height) * scale;
        for (unsigned int x = 0; x < width; x++) {
            float nx = x / static_cast<float>(width) * scale; 
            float n = noise(nx, ny);
            switch (mode)
            {
            case 0:
                color = static_cast<unsigned char>(n * 255);
                i[(y * width + x) * 4] = color;     // R
                i[(y * width + x) * 4 + 1] = color; // G
                i[(y * width + x) * 4 + 2] = color; // B
                i[(y * width + x) * 4 + 3] = color;   // A 
                break;
            case 1:

                r = static_cast<unsigned char>(std::sin(n * 6.28f) * 128 + 128);  // Red
                g = static_cast<unsigned char>(std::cos(n * 6.28f) * 128 + 128);  // Green
                b = static_cast<unsigned char>(std::sin(n * 3.14f) * 128 + 128); // Blue

                i[(y * width + x) * 4] = r;       // R
                i[(y * width + x) * 4 + 1] = g;   // G
                i[(y * width + x) * 4 + 2] = b;
                i[(y * width + x) * 4 + 3] = 255;
                break;
            case 2:
                color = static_cast<unsigned char>((n + 1.0f) * 128);

                i[(y * width + x) * 4] = color;       // R
                i[(y * width + x) * 4 + 1] = 255 - color; // G (invertido)
                i[(y * width + x) * 4 + 2] = (color + 128) % 256; // B (variando)
                i[(y * width + x) * 4 + 3] = 255;     // A (opacidad)
                break;
            case 3:
                r = static_cast<unsigned char>(255 * (n > 0.5f ? (1 - n) : n));
                g = static_cast<unsigned char>(255 * (n));
                b = static_cast<unsigned char>(255 * (1 - std::fabs(n - 0.5f)));

                i[(y * width + x) * 4] = r;       // R
                i[(y * width + x) * 4 + 1] = g;   // G
                i[(y * width + x) * 4 + 2] = b;
                i[(y * width + x) * 4 + 3] = 255;
                break;
            default:
                break;
            }

        }
    }

    imageName = "../assets/perling_noise_image_" + generateUniqueFileName();

    return i;
 }

float PerlinNoise::fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoise::lerp(float a, float b, float t) {
    return a + t * (b - a);
}

float PerlinNoise::grad(int hash, float x, float y) {
    int h = hash & 15; 
    float u = h < 8 ? x : y;
    return (h & 1 ? -u : u);
}
