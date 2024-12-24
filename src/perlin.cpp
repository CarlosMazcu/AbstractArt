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
    std::mt19937 gen(rd());  
    std::uniform_int_distribution<int> dis(0, 255);  

    for (int i = 0; i < 256; i++) {
        p[i] = dis(gen);  
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

    imageName = "../assets/simplex_noise_" + generateUniqueFileName();

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

std::vector<unsigned char> SimplexNoise::generateImage(std::string& imageName)
{
    std::vector<unsigned char> i(width * height * 4);
    for (unsigned int y = 0; y < height; y++) {
        float ny = y / static_cast<float>(height) * scale;
        for (unsigned int x = 0; x < width; x++) {
            double nx = x / static_cast<float>(width) * scale;
            double n = noise(nx, ny);

            unsigned char r = static_cast<unsigned char>(255 * (n > 0.5f ? (1 - n) : n));
            unsigned char g = static_cast<unsigned char>(255 * (n));
            unsigned char b = static_cast<unsigned char>(255 * (1 - std::fabs(n - 0.5f)));

            i[(y * width + x) * 4] = r;               i[(y * width + x) * 4 + 1] = g;  
            i[(y * width + x) * 4 + 2] = b;
            i[(y * width + x) * 4 + 3] = 255;
        }
    }
    imageName = "../assets/simplex_noise_" + generateUniqueFileName();
    return i;
}

double SimplexNoise::noise(double xin, double yin)
{

	const double F2 = 0.5 * (sqrt(3.0) - 1.0);
	const double G2 = (3.0 - sqrt(3.0)) / 6.0;

	// Calcular skew (desplazamiento) del grid
	double s = (xin + yin) * F2;
	int i = floor(xin + s);
	int j = floor(yin + s);

	// Unskew para encontrar la posición en el grid
	double t = (i + j) * G2;
	double X0 = i - t;
	double Y0 = j - t;
	double x0 = xin - X0;
	double y0 = yin - Y0;

	// Determinar qué triángulo estamos
	int i1, j1;
	if (x0 > y0) { i1 = 1; j1 = 0; }
	else { i1 = 0; j1 = 1; }

	// Coordenadas de los otros vértices
	double x1 = x0 - i1 + G2;
	double y1 = y0 - j1 + G2;
	double x2 = x0 - 1.0 + 2.0 * G2;
	double y2 = y0 - 1.0 + 2.0 * G2;

	// Índices para gradientes
	int ii = i & 255;
	int jj = j & 255;
	int gi0 = perm[ii + perm[jj]] % 8;
	int gi1 = perm[ii + i1 + perm[jj + j1]] % 8;
	int gi2 = perm[ii + 1 + perm[jj + 1]] % 8;

	// Contribuciones de cada vértice
	double t0 = 0.5 - x0 * x0 - y0 * y0;
	double n0 = t0 < 0 ? 0.0 : pow(t0, 4) * dot(grad2[gi0], x0, y0);

	double t1 = 0.5 - x1 * x1 - y1 * y1;
	double n1 = t1 < 0 ? 0.0 : pow(t1, 4) * dot(grad2[gi1], x1, y1);

	double t2 = 0.5 - x2 * x2 - y2 * y2;
	double n2 = t2 < 0 ? 0.0 : pow(t2, 4) * dot(grad2[gi2], x2, y2);

	// Sumar contribuciones y escalar
	return 70.0 * (n0 + n1 + n2);
}

void SimplexNoise::initializePermutation()
{
    perm.resize(512);
    for (int i = 0; i < 256; ++i) perm[i] = i;

    std::random_device rd; // Semilla
    std::mt19937 generator(rd());
    for (int i = 255; i > 0; --i) {
        std::uniform_int_distribution<int> distribution(0, i);
        int j = distribution(generator);
        std::swap(perm[i], perm[j]);
    }

    for (int i = 0; i < 256; ++i) perm[256 + i] = perm[i];
}
