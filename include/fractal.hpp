#ifndef __FRACTAL_HPP__
#define __FRACTAL_HPP__ 1

#include <vector>
#include <complex>
#include <string>

class Mandelbrot {
public:
    /**
     * @brief Constructor of the Mandelbrot class.
     *
     * Initializes the parameters of the Mandelbrot set, including image dimensions,
     * zoom level, X and Y offsets, maximum number of iterations, and the escape radius.
     *
     * @param w Width of the image.
     * @param h Height of the image.
     * @param zoom Zoom factor for viewing the Mandelbrot set (default value: 200.0).
     * @param moveX Offset in the X direction (default value: -0.5).
     * @param moveY Offset in the Y direction (default value: 0.0).
     * @param maxIterations Maximum number of iterations to determine the point's escape (default value: 500).
     *
     * Recommended values for `maxIterations` range from 100 to 1000 for a good balance
     * between detail and performance. Higher values (>2000) provide more detail but at the
     * cost of longer computation times. The `scapeRadius` value should be between 2.0 and 4.0,
     * with 2.0 being the mathematically necessary minimum for the Mandelbrot set.
     */
    Mandelbrot(unsigned int w, unsigned int h, float zoom = 200.0f, float moveX = -0.5f, float moveY = 0.0f, int maxIterations = 500);

    /**
     * @brief Generates the Mandelbrot set image.
     *
     * This method calculates the values for each pixel in the image based on the Mandelbrot set
     * equation and returns the generated image as a vector of bytes.
     *
     * @param imageName File name where the generated image will be saved. The name is generated automatically.
     *
     * @return std::vector<unsigned char> A vector representing the generated image in RGBA format.
     */
    std::vector<unsigned char> generateImage(std::string &imageName);

    /**
    * @brief Sets the zoom level for the Mandelbrot fractal.
    * @param z The new zoom value.
    */
    void setZoom(float zoom);
    /**
    * @brief Sets the horizontal offset for the Mandelbrot fractal.
    * @param x The new horizontal offset value.
    */
    void setMoveX(float moveX);
    /**
    * @brief Sets the vertical offset for the Mandelbrot fractal.
    * @param y The new vertical offset value.
    */
    void setMoveY(float moveY);
    /**
     * @brief Adjusts the maximum number of iterations.
     *
     * @param maxIter The new value for the maximum number of iterations.
     *
     * Recommended values for `maxIterations` range from 100 to 1000 for a good balance
     * between quality and performance. Higher values provide more detail but increase computation time.
     */
    void setMaxIterations(int maxIterations);
    /**
    * @brief Sets the RGB saturation levels for coloring the Mandelbrot fractal.
    * @param r The red saturation level (range: 0.0f to 1.0f).
    * @param g The green saturation level (range: 0.0f to 1.0f).
    * @param b The blue saturation level (range: 0.0f to 1.0f).
    */
    void setRGBsaturation(float r, float g, float b);
    /**
     * @brief Adjusts the escape radius for the Mandelbrot set.
     *
     * @param r The new escape radius value.
     *
     * The `scapeRadius` value should typically be between 2.0 and 4.0. A value lower than 2.0
     * will result in fewer points escaping, potentially distorting the image, while values greater
     * than 4.0 may increase computation time unnecessarily.
     */
    void setScapeRadius(float r);

private:
    unsigned int width, height;
    float sat_r, sat_g, sat_b;
    float scapeRadius;
    float zoom, moveX, moveY;
    int maxIterations;
    /**
     * @brief Generates the complete Mandelbrot set image.
     *
     * This method computes the Mandelbrot set for each pixel, based on the maximum number of iterations
     * (`maxIterations`) and the escape radius (`scapeRadius`), and generates the pixel color based on
     * how quickly the point escapes.
     *
     * @return std::vector<unsigned char> A vector of bytes representing the generated image in RGBA format.
     *
     * The image is generated using the current parameters such as zoom, offsets, and escape radius.
     * The color of each pixel is based on the number of iterations required for a point to escape
     * and is smoothened using the `sat_r`, `sat_g`, and `sat_b` parameters.
     */
    std::vector<unsigned char> generateMandelbrotImage();
};

class JuliaSet {
public:
    /**
     * @brief Constructor for the JuliaSet class.
     *
    * Initializes the parameters of the Julia set image, including image dimensions, 
    * zoom level, X and Y offsets, the complex constant `c` (used in the Julia set formula),
    * and the maximum number of iterations.
    * 
    * @param w Width of the image.
    * @param h Height of the image.
    * @param zoom Zoom factor for viewing the Julia set (default value: 200.0).
    * @param moveX Offset in the X direction (default value: -0.5).
    * @param moveY Offset in the Y direction (default value: 0.0).
    * @param c_real Real part of the complex constant `c` (default value: -0.7).
    * @param c_imag Imaginary part of the complex constant `c` (default value: 0.27015).
    * @param maxIterations Maximum number of iterations per point (default value: 500).
    * 
    * Recommended values for `maxIterations` range from 100 to 1000 for a good balance 
    * between detail and performance. Higher values (>2000) provide more detail but at the 
    * cost of longer computation times. The complex constant `c` typically ranges between 
    * -2.0 and 2.0 for both the real and imaginary components. Typical values like 
    * `(-0.7, 0.27015)` generate the classic Julia set. The `scapeRadius` value should be 
    * between 2.0 and 4.0, with 2.0 being the mathematically necessary minimum.
    */
    JuliaSet(unsigned int w, unsigned int h, float zoom = 200.0f, float moveX = 0.0f, float moveY = 0.0f, 
        float c_real = -0.7f, float c_imag = 0.27015f, int maxIterations = 500);

    /**
     * @brief Generates the Julia set image.
     *
     * This method calculates the values for each pixel in the image based on the Julia set,
     * and returns the generated image as a vector of bytes.
     *
     * @param imageName File name where the generated image will be saved. The name is generated automatically.
     *
     * @return std::vector<unsigned char> A vector representing the generated image in RGBA format.
     */
    std::vector<unsigned char> generateImage(std::string &imageName);

    /**
    * @brief Adjusts the zoom factor for viewing the Julia set.
    *
    * @param z The new zoom value. A higher value shows a more "zoomed in" image.
    */
    void setZoom(float z);
    /**
    * @brief Sets the horizontal offset for the Julia Set fractal.
    * @param x The new horizontal offset value.
    */
    void setMoveX(float x);
    /**
    * @brief Sets the vertical offset for the Julia Set fractal.
    * @param y The new vertical offset value.
    */
    void setMoveY(float y);
    /**
     * @brief Adjusts the maximum number of iterations.
     *
     * @param maxIter The new value for the maximum number of iterations.
     *
     * Recommended values for `maxIterations` range from 100 to 1000 for a good balance
     * between quality and performance. Higher values provide more detail but increase computation time.
     */
    void setMaxIterations(int maxIter);
    /**
     * @brief Adjusts the complex constant `c` used in the Julia set equation.
     *
     * @param c_real The real part of the complex constant `c`.
     * @param c_imag The imaginary part of the complex constant `c`.
     *
     * Typical values for `c` range from -2.0 to 2.0 for both components.
     */
    void setComplexConstant(float c_real, float c_imag);
    /**
     * @brief Adjusts the RGB color saturation in the image.
     *
     * @param r Red saturation (value between 0 and 1).
     * @param g Green saturation (value between 0 and 1).
     * @param b Blue saturation (value between 0 and 1).
     *
     * Saturation values greater than 1.0 are clamped to 1.0.
     */
    void setRGBsaturation(float r, float g, float b);
    /**
     * @brief Adjusts the escape radius for the Julia set.
     *
     * @param r The new escape radius value.
     *
     * The `scapeRadius` value should typically be between 2.0 and 4.0. A value too low may produce unwanted artifacts,
     * while a value too high makes the image lose details.
     */
    void setScapeRadius(float r);

private:
    unsigned int width, height;
    float zoom, moveX, moveY;
    float scapeRadius;
    std::complex<float> c;  // Número complejo constante para Julia
    int maxIterations;
    float sat_r, sat_g, sat_b;  // Saturación RGB

    /**
     * @brief Generates the complete Julia set image.
     *
     * This method calculates the Julia set for each pixel in the image. For each point in the image,
     * it computes the number of iterations required for the point to escape according to the Julia set formula,
     * then assigns a color based on the number of iterations.
     *
     * @return std::vector<unsigned char> A vector of bytes representing the generated image in RGBA format.
     *
     * The image is generated using the current parameters such as zoom, offsets, and the complex constant `c`.
     * The color of each pixel is based on the number of iterations required to escape, and the color is smoothened
     * using the `sat_r`, `sat_g`, and `sat_b` parameters. The `scapeRadius` value controls when a point is considered
     * to have "escaped", and typical values are between 2.0 and 4.0.
     */
    std::vector<unsigned char> generateJuliaSetImage();
};



class Newton {

public:
    /**
     * @brief Constructor for the Newton fractal generator.
     *
     * Initializes the parameters for generating the Newton fractal, including the image dimensions,
     * zoom level, X and Y offsets, maximum number of iterations, and convergence tolerance.
     *
     * @param w Width of the image.
     * @param h Height of the image.
     * @param zoom Zoom factor for viewing the Newton fractal (default value: 200.0).
     * @param moveX Offset in the X direction (default value: -0.5).
     * @param moveY Offset in the Y direction (default value: 0.0).
     * @param maxIter Maximum number of iterations to determine the convergence of each point (default value: 100).
     * @param tol Convergence tolerance (default value: 1e-6).
     *
     * Recommended values for `maxIterations` range from 50 to 200 for a good balance
     * between performance and detail. Higher values (>500) provide more precision but increase computation time.
     * The `tolerance` value is typically between 1e-6 and 1e-10, depending on the desired precision.
     */
    Newton(unsigned int w, unsigned int h, float zoom = 1.0f, float moveX = 0.0f, float moveY = 0.0f, int maxIter = 100, float tol = 1e-6);

    /**
     * @brief Generates the Newton fractal image.
     *
     * This method computes the values for each pixel in the image based on the Newton method
     * and returns the generated image as a vector of bytes.
     *
     * @param imageName File name where the generated image will be saved. The name is generated automatically.
     *
     * @return std::vector<unsigned char> A vector representing the generated image in RGBA format.
     */
    std::vector<unsigned char> generateImage(std::string& imageName);

    /**
     * @brief Generates the complete Newton fractal image.
     *
     * This method computes the Newton fractal for each pixel based on the maximum number of iterations
     * (`maxIterations`) and the convergence tolerance (`tolerance`), and generates the pixel color based on
     * how quickly the point converges to a root.
     *
     * @return std::vector<unsigned char> A vector of bytes representing the generated image in RGBA format.
     *
     * The image is generated using the current parameters such as zoom, offsets, and convergence tolerance.
     * The color of each pixel is based on the number of iterations needed to converge, with the colors
     * being smoothened using the `sat_r`, `sat_g`, and `sat_b` parameters.
     */
    std::vector<unsigned char> generateNewtonImage();

    /**
     * @brief Adjusts the zoom factor for viewing the Newton fractal.
     *
     * @param z The new zoom value. A higher value shows a more "zoomed in" image.
     */
    void setZoom(float z) { zoom = z; }
    /**
     * @brief Adjusts the X offset for the Newton fractal.
     *
     * @param x The new X offset value.
     */
    void setMoveX(float x) { moveX = x; }
    /**
     * @brief Adjusts the Y offset for the Newton fractal.
     *
     * @param y The new Y offset value.
     */
    void setMoveY(float y) { moveY = y; }
    /**
     * @brief Adjusts the maximum number of iterations for Newton's method.
     *
     * @param maxIter The new value for the maximum number of iterations.
     *
     * Recommended values for `maxIterations` range from 50 to 200 for a good balance
     * between performance and detail. Higher values provide more precision but increase computation time.
     */
    void setMaxIterations(int maxIter) { maxIterations = maxIter; }
    /**
     * @brief Adjusts the convergence tolerance for Newton's method.
     *
     * @param tol The new convergence tolerance value.
     *
     * The `tolerance` value is typically between 1e-6 and 1e-10. A higher tolerance value
     * (e.g., 1e-6) results in faster computations with less accuracy, while smaller values
     * (e.g., 1e-10) improve precision but require more iterations.
     */
    void setTolerance(float tol) { tolerance = tol; }
    /**
     * @brief Adjusts the RGB color saturation in the image.
     *
     * @param r Red saturation (value between 0 and 1).
     * @param g Green saturation (value between 0 and 1).
     * @param b Blue saturation (value between 0 and 1).
     *
     * Saturation values greater than 1.0 are clamped to 1.0.
     */
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
