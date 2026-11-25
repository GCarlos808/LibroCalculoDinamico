#ifndef PILAHISTORIAL_H
#define PILAHISTORIAL_H

//  PilaHistorial.h - Pilas de Deshacer / Rehacer (NodoAccion*).

#include <QString>
#include "Tipos.h"

enum class TipoAccion { Contenido, Formato };

struct NodoAccion {
    TipoAccion tipo;
    int idHoja; // id (no puntero): sobrevive a renombrar/eliminar hojas
    int fila;
    int columna;
    QString contenidoAnterior;
    QString contenidoNuevo;
    EstiloCelda estiloAnterior;
    EstiloCelda estiloNuevo;
    QString descripcion; // texto para el panel "Historial"
    int idGrupo; // 0 = accion sola; >0 = parte de un grupo (se deshacen juntas)
    NodoAccion* siguiente;

    NodoAccion()
        : tipo(TipoAccion::Contenido), idHoja(0), fila(0), columna(0),
          idGrupo(0), siguiente(nullptr) {}
};

// pila LIFO primitiva
class PilaAcciones {
public:
    PilaAcciones();
    ~PilaAcciones();
    PilaAcciones(const PilaAcciones&) = delete;
    PilaAcciones& operator=(const PilaAcciones&) = delete;

    void push(NodoAccion* nodo);
    NodoAccion* pop(); // el llamador es duenio del nodo
    const NodoAccion* tope() const;
    bool vacia() const;
    int cantidad() const;
    void vaciar(); // libera todos los nodos
    void eliminarMasAntigua(); // para respetar el limite

private:
    NodoAccion* cima;
    int total;
};

// deshacer + rehacer
class PilaHistorial {
public:
    PilaHistorial();
    ~PilaHistorial();
    PilaHistorial(const PilaHistorial&) = delete;
    PilaHistorial& operator=(const PilaHistorial&) = delete;

    // Registra una accion nueva (toma posesion del nodo). Vacia "rehacer".
    void registrar(NodoAccion* accion);

    // Mueve el tope de una pila a la otra y lo devuelve para que LibroTrabajo aplique los valores "anteriores" / "nuevos".
    NodoAccion* deshacer();
    NodoAccion* rehacer();

    bool puedeDeshacer() const;
    bool puedeRehacer() const;
    const NodoAccion* topeDeshacer() const;
    const NodoAccion* topeRehacer() const;

    int  nuevoIdGrupo(); // incrementa y devuelve
    void limpiar(); // al abrir/crear un libro nuevo

private:
    PilaAcciones pilaDeshacer;
    PilaAcciones pilaRehacer;
    int contadorGrupos;
};

#endif // PILAHISTORIAL_H
