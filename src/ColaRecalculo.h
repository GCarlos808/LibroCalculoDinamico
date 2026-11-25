#ifndef COLARECALCULO_H
#define COLARECALCULO_H

class HojaCalculo;

struct NodoRecalculo {
    HojaCalculo* hoja;
    int fila;
    int columna;
    NodoRecalculo* siguiente;

    NodoRecalculo(HojaCalculo* h, int f, int c) : hoja(h), fila(f), columna(c), siguiente(nullptr) {}
};

class ColaRecalculo {
public:
    ColaRecalculo();
    ~ColaRecalculo();
    ColaRecalculo(const ColaRecalculo&) = delete;
    ColaRecalculo& operator=(const ColaRecalculo&) = delete;

    // Encola al final. Devuelve false si esa celda ya estaba en la cola
    // (evita recalcular dos veces y bucles infinitos).
    bool encolar(HojaCalculo* hoja, int fila, int columna);

    // Saca del frente. Devuelve false si esta vacia.
    bool desencolar(HojaCalculo*& hoja, int& fila, int& columna);

    bool contiene(const HojaCalculo* hoja, int fila, int columna) const;
    bool vacia() const;
    int  cantidad() const;
    void vaciar();

private:
    NodoRecalculo* frente;
    NodoRecalculo* final_;
    int total;
};

#endif // COLARECALCULO_H
