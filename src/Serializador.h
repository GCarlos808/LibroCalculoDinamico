#ifndef SERIALIZADOR_H
#define SERIALIZADOR_H

//  Serializador.h - Guardar / cargar el libro completo en formato NATIVO .xls3 (texto estructurado) usando fstream.

#include <QString>

class LibroTrabajo;

class Serializador {
public:
    Serializador();

    // queda en ultimoError().
    bool guardar(const QString& ruta, const LibroTrabajo* libro);

    // Si el archivo esta corrupto, no debe dejar el libro a medias.
    bool cargar(const QString& ruta, LibroTrabajo* libro);

    QString ultimoError() const;

private:
    QString mensajeError;

    static QString escapar(const QString& texto);
    static QString desescapar(const QString& texto);
};

#endif // SERIALIZADOR_H
