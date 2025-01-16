#ifndef __IMAGE_UTILS_HPP__
#define __IMAGE_UTILS_HPP__ 1
#include "perlin.hpp"
#include "fractal.hpp"
#include "conway.hpp"

/**
 * @brief Generates a unique file name based on the current timestamp.
 *
 * This function creates a file name in the format "YYYYMMDD_HHMMSS.png",
 * where:
 * - YYYY: Year
 * - MM: Month
 * - DD: Day
 * - HH: Hour (24-hour format)
 * - MM: Minute
 * - SS: Second
 *
 * The timestamp ensures that each generated file name is unique to the second.
 *
 * @return std::string A string containing the generated file name, ending with ".png".
 */
std::string generateUniqueFileName();

#endif