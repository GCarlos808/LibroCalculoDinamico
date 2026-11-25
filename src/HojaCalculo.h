#ifndef HOJACALCULO_H
#define HOJACALCULO_H

#include <QString>
#include "Tipos.h"
#include "Celda.h"

class HojaCalculo {
public:
    HojaCalculo(const QString& nombre, int filas    = Config::FILAS_INICIALES, int columnas = Config::COLUMNAS_INICIALES);
    ~HojaCalculo(); // delete[] de toda la matriz
    HojaCalculo(const HojaCalculo&) = delete;
    HojaCalculo& operator=(const HojaCalculo&) = delete;

    int id() const; // unico en el libro; NO cambia al renombrar
    void establecerId(int nuevoId); // lo asigna LibroTrabajo
    QString nombre() const;
    void establecerNombre(const QString& nuevoNombre);

    // dimensiones
    int filas() const;
    int columnas() const;
    bool coordenadaValida(int fila, int columna) const;

    Celda* celda(int fila, int columna);
    const Celda* celda(int fila, int columna) const;

    // Redimensionamiento dinamico (sin perder datos
    // Devuelven false si se excede MAX_FILAS / MAX_COLUMNAS o el indice es invalido.
    // "antesDe" = indice donde queda la nueva fila/columna vacia.
    bool insertarFila(int antesDe);
    bool eliminarFila(int fila);
    bool insertarColumna(int antesDe);
    bool eliminarColumna(int columna);

    // impieza
    void limpiarCelda(int fila, int columna);
    void limpiarRango(const Rango& rango);

private:
    Celda** matrizCeldas;
    int numFilas;
    int numColumnas;
    int idHoja;
    QString nombreHoja;

    Celda** reservarMatriz(int filas, int columnas) const;
    void liberarMatriz(Celda** matriz, int filas);
};

#endif // HOJACALCULO_H
