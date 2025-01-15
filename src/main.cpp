#include <SFML/Graphics.hpp>
#include <filesystem>
#include "../include/image_utils.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb/stb_image_write.h"


int main() {
    unsigned int width = 512;
    unsigned int height = 512;

    Mandelbrot mandelbrot(width, height);
    JuliaSet jl(width, height);
    Newton newton(width, height);
    PerlinNoise perlin(width, height);
    SimplexNoise simplex(width, height);
    GameOfLife game(width, height);

    newton.setMaxIterations(50);
    newton.setRGBsaturation(0.2f, 0.12f, 0.76f);
    newton.setTolerance(1e-3);

    mandelbrot.setZoom(300.0f);
    mandelbrot.setMoveX(-0.5f);
    mandelbrot.setMoveY(0.0f);
    mandelbrot.setMaxIterations(100);
    mandelbrot.setRGBsaturation(0.6f, 0.74f, 0.7f);
    mandelbrot.setScapeRadius(3.0f);

    jl.setComplexConstant(-0.8f, 0.2176f);
    jl.setMaxIterations(100);
    jl.setRGBsaturation(0.5f, 0.0f, 0.35f);
    jl.setScapeRadius(1.2f);

    std::string fileName;

   // std::vector<unsigned char> image_data = perlin.generateImage(fileName);
    //std::vector<unsigned char> image_data = mandelbrot.generateImage(fileName);
    std::vector<unsigned char> image_data = jl.generateImage(fileName);
   // std::vector<unsigned char> image_data = newton.generateImage(fileName);
    //std::vector<unsigned char> image_data = simplex.generateImage(fileName);
    
    // SFML Texture
    sf::Texture texture;
    texture.create(width, height);
    texture.update(image_data.data());
    // sprite to show texture
    sf::Sprite sprite(texture);

    // create window
    sf::RenderWindow window(sf::VideoMode(width, height), "Algorithmic Abstract Art");
    window.setFramerateLimit(60);
    // show window
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        std::vector<unsigned char> image_data = game.generateImage();
        //texture.update(image_data.data());
        //game.nextGeneration();

        window.clear();
        window.draw(sprite);
        window.display();
    }
    //if (!std::filesystem::exists("../assets")) {
        std::filesystem::create_directory("../assets");
    //}

    // save image PNG
   // stbi_write_png(fileName.c_str(), width, height, 4, image_data.data(), width * 4);
    //std::cout << "Imagen guardada como: " << fileName << std::endl;
    return 0;
}