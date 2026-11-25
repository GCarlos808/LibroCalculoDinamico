#ifndef COORDENADAS_H
#define COORDENADAS_H

#include <QString>
#include "Tipos.h"

class Coordenadas {
public:
    // 'A'->0 ... 'Z'->25, "AA"->26 ... "AZ"->51.  Devuelve -1 si es invalido.
    static int columnaAIndice(const QString& letras);
    // 0->"A", 25->"Z", 26->"AA"
    static QString indiceAColumna(int indice);

    // "B4" -> fila=3, columna=1.  false si el formato es invalido.
    static bool parsearCelda(const QString& texto, int& fila, int& columna);
    // "A1:B10" -> Rango normalizado.  false si el formato es invalido.
    static bool parsearRango(const QString& texto, Rango& rango);

    // (3,1) -> "B4"
    static QString textoCelda(int fila, int columna);
    // Rango -> "A1:B10"
    static QString textoRango(const Rango& rango);
};

#endif // COORDENADAS_H
