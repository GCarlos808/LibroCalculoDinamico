#ifndef TIPOS_H
#define TIPOS_H

//
//  Tipos.h  -  Tipos y constantes COMPARTIDOS por todo el proyecto.

#include <QString>

namespace Config {
    const int COLUMNAS_INICIALES = 26; // A..Z
    const int FILAS_INICIALES = 50; // 1..50
    const int MAX_COLUMNAS = 52; // A..AZ
    const int MAX_FILAS = 100;
    const int LIMITE_HISTORIAL = 50; // el enunciado exige minimo 20
}

enum class TipoContenido { Vacio, Texto, Numero, Formula };

// Errores estandar
enum class CodigoError {
    Ninguno,
    DivCero, // #DIV/0!
    Valor, // #VALOR!
    Ref, // #REF!
    Nombre // #NOMBRE?
};

enum class Alineacion { Izquierda, Centro, Derecha };
enum class FormatoNumerico { General, Moneda, Porcentaje, Decimales };

// Estilo de una celda.
struct EstiloCelda {
    bool negrita;
    bool cursiva;
    Alineacion alineacion;
    unsigned int colorTexto;
    unsigned int colorFondo;
    FormatoNumerico formato;
    int decimales;

    EstiloCelda(): negrita(false), cursiva(false), alineacion(Alineacion::Izquierda), colorTexto(0x000000), colorFondo(0xFFFFFF), formato(FormatoNumerico::General), decimales(2) {}
};

// Rango rectangular de celdas (base 0, extremos incluidos).
struct Rango {
    int fila1, columna1, fila2, columna2;

    Rango() : fila1(0), columna1(0), fila2(0), columna2(0) {}
    Rango(int f1, int c1, int f2, int c2) : fila1(f1), columna1(c1), fila2(f2), columna2(c2) { normalizar(); }

    // Garantiza fila1<=fila2 y columna1<=columna2
    void normalizar() {
        if (fila1 > fila2) { int t = fila1;    fila1 = fila2;       fila2 = t; }
        if (columna1 > columna2) { int t = columna1; columna1 = columna2; columna2 = t; }
    }
    int cantidadFilas() const { return fila2 - fila1 + 1; }
    int cantidadColumnas() const { return columna2 - columna1 + 1; }
    int cantidadCeldas() const { return cantidadFilas() * cantidadColumnas(); }
};

#endif // TIPOS_H
