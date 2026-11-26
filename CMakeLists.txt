cmake_minimum_required(VERSION 3.16)
project(LibroCalculo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Qt 6 con el modulo Charts (instalar "Qt Charts" en el Maintenance Tool)
find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)

# Solo los .cpp. AUTOMOC detecta el .h desde el #include.
# Un .h con Q_OBJECT listado aqui, sin su .cpp, rompe el enlace.
file(GLOB PROYECTO_FUENTES CONFIGURE_DEPENDS
     ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Usa HojaCalculo, Celda y Coordenadas, que todavia no tienen .cpp.
list(FILTER PROYECTO_FUENTES EXCLUDE REGEX "GraficoEstadistico\\.cpp$")

qt_add_executable(LibroCalculo ${PROYECTO_FUENTES} ${CMAKE_SOURCE_DIR}/src/recursos.qrc)
target_link_libraries(LibroCalculo PRIVATE Qt6::Widgets Qt6::Charts)
