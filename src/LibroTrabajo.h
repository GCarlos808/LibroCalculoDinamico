#ifndef LIBROTRABAJO_H
#define LIBROTRABAJO_H

//  REGLA DE ORO: la interfaz (y Ordenador, BuscadorReemplazo, CSV...)
//  NUNCA escribe directo en Celda para cambiar contenido. Siempre llama a establecerContenidoCelda(),

#include <QObject>
#include <QString>
#include "Tipos.h"

class HojaCalculo;
class EvaluadorFormulas;
class PilaHistorial;
class ColaRecalculo;

// Lista enlazada DOBLE de hojas (NodoHoja*)
struct NodoHoja {
    HojaCalculo* hoja;
    NodoHoja* anterior;
    NodoHoja* siguiente;

    explicit NodoHoja(HojaCalculo* h): hoja(h), anterior(nullptr), siguiente(nullptr) {}
};

class LibroTrabajo : public QObject {
    Q_OBJECT
public:
    explicit LibroTrabajo(QObject* parent = nullptr);
    ~LibroTrabajo(); //liberar hojas, pilas y colas

    HojaCalculo* agregarHoja(const QString& nombre = QString()); // "Hoja N" por default
    bool eliminarHoja(HojaCalculo* hoja); // nunca deja el libro sin hojas
    bool renombrarHoja(HojaCalculo* hoja, const QString& nuevoNombre);
    HojaCalculo* buscarHoja(const QString& nombre) const; // nullptr si no existe
    HojaCalculo* buscarPorId(int id) const;
    HojaCalculo* hojaEnPosicion(int indice) const;
    int cantidadHojas() const;
    const NodoHoja* primerNodo() const;

    HojaCalculo* hojaActiva() const;
    void establecerHojaActiva(HojaCalculo* hoja);
    HojaCalculo* hojaSiguiente() const;
    HojaCalculo* hojaAnterior() const;

    // edicion (punto de entrada unico)
    void establecerContenidoCelda(HojaCalculo* hoja, int fila, int columna, const QString& texto, bool registrarEnHistorial = true);
    void aplicarEstilo(HojaCalculo* hoja, int fila, int columna, const EstiloCelda& estilo, bool registrarEnHistorial = true);

    // Agrupa varias ediciones en UNA sola accion de deshacer
    // (ej.: ordenar un rango, buscar y reemplazar todo, pegar un bloque).
    void iniciarGrupoAcciones(const QString& descripcion);
    void finalizarGrupoAcciones();

    bool deshacer();
    bool rehacer();

    // estructura (filas/columnas)
    bool insertarFila(HojaCalculo* hoja, int antesDe);
    bool eliminarFila(HojaCalculo* hoja, int fila);
    bool insertarColumna(HojaCalculo* hoja, int antesDe);
    bool eliminarColumna(HojaCalculo* hoja, int columna);

    // eecalculo
    void reconstruirDependencias();
    void recalcularTodo();

    // - Nuevo libro / abrir archivo -
    void reiniciar(); // libera todo y deja UNA hoja vacia

    // componentes internos (los comparten otros modulos)
    EvaluadorFormulas* evaluador() const;
    PilaHistorial* historial() const;
    ColaRecalculo* cola() const;

signals:
    void celdaActualizada(HojaCalculo* hoja, int fila, int columna);
    void estructuraCambiada(HojaCalculo* hoja); // filas/columnas insertadas o eliminadas
    void hojasCambiaron(); // agregar / eliminar / renombrar
    void hojaActivaCambio(HojaCalculo* hoja);

private:
    NodoHoja* cabeza;
    NodoHoja* cola_;
    NodoHoja* nodoActivo;
    int numHojas;
    int siguienteIdHoja;
    EvaluadorFormulas* motor;
    PilaHistorial*     pilas;
    ColaRecalculo*     colaRecalculo;

    void liberarHojas();
};

#endif // LIBROTRABAJO_H
