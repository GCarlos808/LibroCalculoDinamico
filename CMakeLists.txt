cmake_minimum_required(VERSION 3.16)
project(LibroCalculo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Qt 6 con el modulo Charts (instalar "Qt Charts" en el Maintenance Tool)
find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)

# Todos los .cpp y .h dentro de src/ (se re-evalua al agregar archivos)
file(GLOB PROYECTO_FUENTES CONFIGURE_DEPENDS
     ${CMAKE_SOURCE_DIR}/src/*.cpp
     ${CMAKE_SOURCE_DIR}/src/*.h)

qt_add_executable(LibroCalculo ${PROYECTO_FUENTES})
target_link_libraries(LibroCalculo PRIVATE Qt6::Widgets Qt6::Charts)
