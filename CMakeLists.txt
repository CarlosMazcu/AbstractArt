cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(AbstractArt)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 17)

# Incluir las rutas de los archivos de cabecera de SFML
include_directories(${CMAKE_SOURCE_DIR}/libs/sfml64/include)

# Directorios de las bibliotecas de SFML
link_directories(${CMAKE_SOURCE_DIR}/libs/sfml64/lib)
include_directories(include)

# Especificar los archivos fuente
set(SOURCES
    src/main.cpp  
    src/perlin.cpp
    src/fractal.cpp
    src/image_utils.cpp
    src/conway.cpp

    include/perlin.hpp
    include/fractal.hpp
    include/image_utils.hpp
    include/conway.hpp
)

# Crear el ejecutable
add_executable(AbstractArt ${SOURCES})

target_link_libraries(AbstractArt
    $<$<CONFIG:Debug>:sfml-graphics-d.lib>
    $<$<CONFIG:Debug>:sfml-window-d.lib>
    $<$<CONFIG:Debug>:sfml-system-d.lib>
    $<$<CONFIG:Release>:sfml-graphics.lib>
    $<$<CONFIG:Release>:sfml-window.lib>
    $<$<CONFIG:Release>:sfml-system.lib>
)