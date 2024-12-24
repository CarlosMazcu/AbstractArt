#include "../include/image_utils.hpp"
#include <chrono>
#include <iomanip>
#include <sstream> 

std::string generateUniqueFileName() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::tm tm = *std::localtime(&time);

    std::stringstream ss;
    ss  << std::put_time(&tm, "%Y%m%d_%H%M%S")
        << ".png";

    return ss.str();
}