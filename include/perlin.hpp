#ifndef __PERLIN_HPP__
#define __PERLIN_HPP__ 1

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
/**
 * @brief Class for generating Perlin noise-based images.
 *
 * This class generates 2D Perlin noise patterns, which can be customized using the scale and mode parameters.
 * The noise values are mapped to an RGBA image.
 */
class PerlinNoise {
public:
    /**
    * @brief Constructor for the PerlinNoise generator.
    *
    * Initializes the Perlin noise generator with the specified image dimensions.
    *
    * @param w Width of the image.
    * @param h Height of the image.
    */
    PerlinNoise(unsigned int w, unsigned int h);

    /**
     * @brief Generates a Perlin noise image.
     *
     * The generated image is stored in a vector with RGBA format, and its name is returned in the parameter.
     *
     * @param imageName A reference to a string where the file name of the image will be stored.
     *
     * @return std::vector<unsigned char> The RGBA pixel data of the generated image.
     */
    std::vector<unsigned char> generateImage(std::string &imageName);
    /**
     * @brief Sets the scale for Perlin noise generation.
     *
     * A larger scale produces larger features in the noise pattern (i.e., "zoomed out" appearance),
     * while a smaller scale creates finer details (i.e., "zoomed in" appearance).
     *
     * @param s The new scale value. Recommended range: 1 to 50. Default: 10.
     */
    void setScale(int s){scale = s;}
    /**
     * @brief Sets the rendering mode for the Perlin noise image.
     *
     * The mode determines how the Perlin noise values are mapped to colors {0 - 3}
     *
     * @param m The new rendering mode. Default: 0.
     */
    void setMode(int m){mode = m;}
    /**
     * @brief Gets the current scale value for Perlin noise generation.
     *
     * @return int The current scale value.
     */
    int getScale(){return scale;}
    /**
     * @brief Gets the current rendering mode for the Perlin noise image.
     *
     * @return int The current mode value (e.g., 0 for grayscale, 1 for color gradient).
     */
    int getMode(){return mode;}
private:
    std::vector<int> p;
    int mode;
    int scale;
    unsigned int width, height;
    /**
     * @brief Computes the Perlin noise value at a given point.
     *
     * @param x The x-coordinate in the noise space.
     * @param y The y-coordinate in the noise space.
     * @return float The Perlin noise value at the given coordinates.
     */
    float noise(float x, float y);
    /**
     * @brief Fade function for smoothing.
     *
     * @param t Input value to fade.
     * @return float Smoothed value.
     */
    float fade(float t);
    /**
     * @brief Linear interpolation between two values.
     *
     * @param a First value.
     * @param b Second value.
     * @param t Weighting factor (0 to 1).
     * @return float Interpolated value.
     */
    float lerp(float a, float b, float t);
    /**
     * @brief Gradient function for noise calculation.
     *
     * @param hash Hash value to determine gradient direction.
     * @param x Relative x-coordinate in grid cell.
     * @param y Relative y-coordinate in grid cell.
     * @return float Gradient value.
     */
    float grad(int hash, float x, float y);
};

/**
 * @class SimplexNoise
 * @brief Generates 2D Simplex noise and visualizes it as an image.
 *
 * The Simplex noise algorithm produces smoother, more natural noise patterns
 * compared to Perlin noise. This implementation allows customization of
 * scale and generates a colorized noise image.
 */
class SimplexNoise
{
public:
    /**
     * @brief Constructor for SimplexNoise.
     *
     * Initializes the noise generator with the specified dimensions
     * and default scale.
     *
     * @param w Width of the generated image (in pixels).
     * @param h Height of the generated image (in pixels).
     */
    SimplexNoise(int w, int h) {
        initializePermutation();
        scale = 10;
        width = w;
        height = h;

    }
    /**
     * @brief Generates a Simplex noise image.
     *
     * Creates a noise-based image using the Simplex algorithm, with colorization
     * based on noise values. The image is saved to a specified file path.
     *
     * @param imageName Reference to a string where the generated image file path will be stored.
     * @return std::vector<unsigned char> A vector containing the pixel data in RGBA format.
     */
    std::vector<unsigned char> generateImage(std::string& imageName);
    /**
     * @brief Sets the scale for the noise pattern.
     *
     * A higher scale creates larger, smoother patterns, while a lower scale results in
     * finer, more detailed noise.
     *
     * @param sc New scale value. Recommended range: 1.0 to 50.0. Default: 10.0.
     */
    void setScale(double sc) { scale = sc; }

private:
    /**
     * @brief Gradient vectors for Simplex noise.
     *
     * These predefined vectors are used to calculate directional gradients
     * for the noise function.
     */
    const std::vector<std::vector<int>> grad2 = {
        {1, 1}, {-1, 1}, {1, -1}, {-1, -1},
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };
    /**
     * @brief Computes the Simplex noise value at a given coordinate.
     *
     * Uses the 2D Simplex noise algorithm to calculate a noise value for the specified
     * point in space.
     *
     * @param xin X-coordinate in noise space.
     * @param yin Y-coordinate in noise space.
     * @return double The noise value (range: approximately -1.0 to 1.0).
     */
    double noise(double xin, double yin);

    /**
     * @brief Computes the dot product of a gradient vector and a coordinate.
     *
     * This helper function projects the gradient vector onto the coordinate.
     *
     * @param g Gradient vector.
     * @param x X-offset.
     * @param y Y-offset.
     * @return double The computed dot product.
     */
    double dot(const std::vector<int>& g, double x, double y) {
        return g[0] * x + g[1] * y;
    }

    /**
     * @brief Initializes the permutation table.
     *
     * This function shuffles the permutation vector used to randomize
     * gradient selection in the noise function.
     */
    void initializePermutation();

    std::vector<int> perm; ///< Permutation table for gradient selection.
    double scale; ///< Scale factor for the noise pattern.
    int width; ///< Width of the noise image (in pixels).
    int height; ///< Height of the noise image (in pixels).
};

#endif
