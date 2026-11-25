#ifndef CELDA_H
#define CELDA_H

#include <QString>
#include "Tipos.h"

class HojaCalculo;

// ---- Lista enlazada SIMPLE de dependencias (NodoRef*)

struct NodoRef {
    HojaCalculo* hoja;
    int fila;
    int columna;
    NodoRef* siguiente;

    NodoRef(HojaCalculo* h, int f, int c) : hoja(h), fila(f), columna(c), siguiente(nullptr) {}
};

class Celda {
public:
    Celda();
    ~Celda();
    Celda(const Celda&) = delete;
    Celda& operator=(const Celda&) = delete;

    void establecerContenido(const QString& textoCrudo);
    QString contenidoCrudo() const;
    TipoContenido tipo() const;

    void establecerResultadoNumero(double valor);
    void establecerResultadoTexto(const QString& texto);
    void establecerError(CodigoError codigo);
    double valorNumerico() const;
    bool esNumerica() const;  // true si su resultado es un numero valido
    CodigoError error() const;
    QString textoMostrado() const; // aplica estilo numerico y errores (#DIV/0!...)

    // estilo
    EstiloCelda& estilo();
    const EstiloCelda& estilo() const;

    // dependientes
    bool agregarDependiente(HojaCalculo* hoja, int fila, int columna); // sin duplicados
    const NodoRef* dependientes() const;
    void limpiarDependientes();

    // utilidades
    void vaciar(); // contenido + estilo + resultado
    void copiarDesde(const Celda& otra); // contenido + estilo (NO dependientes)

private:
    QString contenido;
    TipoContenido tipoContenido;
    double valor;
    QString textoResultado;
    bool resultadoEsTexto;
    CodigoError codigoError;
    EstiloCelda estiloCelda;
    NodoRef* listaDependientes; // cabeza de la lista simple
};

#endif // CELDA_H
