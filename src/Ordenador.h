#ifndef ORDENADOR_H
#define ORDENADOR_H

//  Ordenador.h - Ordenamiento ascendente / descendente de un rango.

#include "Tipos.h"

class HojaCalculo;
class LibroTrabajo;

class Ordenador {
public:
    // columnaClave: indice ABSOLUTO de columna (debe estar dentro del rango).
    static bool ordenarRango(LibroTrabajo* libro, HojaCalculo* hoja, const Rango& rango, int columnaClave, bool ascendente);
};

#endif // ORDENADOR_H
