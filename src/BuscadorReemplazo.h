#ifndef BUSCADORREEMPLAZO_H
#define BUSCADORREEMPLAZO_H

#include <QString>

class HojaCalculo;
class LibroTrabajo;

class BuscadorReemplazo {
public:
    BuscadorReemplazo();

    void configurar(const QString& textoBuscar,
                    bool distinguirMayusculas = false,
                    bool celdaCompleta = false);

    // Busca a partir de la posicion (fila,columna) EXCLUSIVE, por filas,
    // y da la vuelta al inicio. Si encuentra, actualiza fila/columna.
    bool buscarSiguiente(const HojaCalculo* hoja, int& fila, int& columna) const;

    bool reemplazarEnCelda(LibroTrabajo* libro, HojaCalculo* hoja,
                           int fila, int columna, const QString& reemplazo);

    // Devuelve cuantas celdas cambio. Un solo grupo de acciones (un Ctrl+Z).
    int  reemplazarTodo(LibroTrabajo* libro, HojaCalculo* hoja,
                        const QString& reemplazo);

private:
    QString buscado;
    bool mayusculas;
    bool completa;
    bool coincide(const QString& texto) const;
};

#endif // BUSCADORREEMPLAZO_H
