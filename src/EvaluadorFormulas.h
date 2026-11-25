#ifndef EVALUADORFORMULAS_H
#define EVALUADORFORMULAS_H

#include <QString>
#include "Tipos.h"
#include "Celda.h"

class HojaCalculo;
class LibroTrabajo;

enum class TipoToken {
    Numero, Texto, Referencia, Rango,
    Operador, Comparador,
    ParentesisIzq, ParentesisDer,
    Funcion, SeparadorArg
};

// nodo de la pila dinamica (LIFO)
struct NodoToken {
    TipoToken  tipo;
    double valor; // si es numero (o resultado parcial en RPN)
    QString texto; // operador, nombre de funcion, referencia, etc.
    int precedencia;  // mayor = se evalua antes (* y / > + y -)
    NodoToken* siguiente;

    NodoToken() : tipo(TipoToken::Numero), valor(0), precedencia(0), siguiente(nullptr) {}
};

class PilaTokens {
public:
    PilaTokens();
    ~PilaTokens(); // libera todos los nodos
    PilaTokens(const PilaTokens&) = delete;
    PilaTokens& operator=(const PilaTokens&) = delete;

    void push(NodoToken* nodo); // la pila se hace duena del nodo
    NodoToken* pop(); // el llamador libera el nodo; nullptr si vacia
    NodoToken* tope() const;
    bool vacia() const;
    int cantidad() const;
    void vaciar();

private:
    NodoToken* cima;
    int total;
};

// Resultado de evaluar una formula
struct ResultadoEvaluacion {
    bool esTexto;
    double numero;
    QString texto;
    CodigoError error;

    ResultadoEvaluacion()
        : esTexto(false), numero(0), error(CodigoError::Ninguno) {}
};

class EvaluadorFormulas {
public:
    EvaluadorFormulas();
    ~EvaluadorFormulas();

    // Evalua una formula completa (con o sin '=' inicial). NUNCA debe
    // provocar segmentation fault: formulas mal escritas devuelven error.
    ResultadoEvaluacion evaluar(const QString& formula, HojaCalculo* hojaActual, LibroTrabajo* libro);

    // Devuelve una lista NUEVA (NodoRef*) con todas las celdas que la
    // formula referencia (para registrar dependencias). El llamador la
    // libera con liberarListaRefs().
    NodoRef* extraerReferencias(const QString& formula, HojaCalculo* hojaActual, LibroTrabajo* libro);
    static void liberarListaRefs(NodoRef* lista);

    // True si agregar 'formula' en (hoja,fila,columna) crearia un ciclo.
    bool creaReferenciaCircular(const QString& formula, HojaCalculo* hoja, int fila, int columna, LibroTrabajo* libro);

private:
    // Pasos internos sugeridos (cada uno usa PilaTokens, sin STL):
    // 1) tokenizar  2) infijo->postfijo (Shunting-Yard)  3) evaluar RPN

    NodoToken* tokenizar(const QString& formula, CodigoError& error);
    NodoToken* aPostfijo(NodoToken* tokensInfijos, CodigoError& error);
    ResultadoEvaluacion evaluarPostfijo(NodoToken* tokensPostfijos, HojaCalculo* hojaActual, LibroTrabajo* libro);
    static void liberarListaTokens(NodoToken* lista);
};

#endif // EVALUADORFORMULAS_H
