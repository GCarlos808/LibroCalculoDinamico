#ifndef ARCHIVOCSV_H
#define ARCHIVOCSV_H

#include <QString>
#include "Tipos.h"

class HojaCalculo;
class LibroTrabajo;

class ArchivoCSV {
public:
    ArchivoCSV();

    bool exportar(const QString& ruta, const HojaCalculo* hoja, char separador = ';');

    // separador = 0 -> detectar automaticamente (',' o ';').
    // Lo que exceda MAX_FILAS x MAX_COLUMNAS se descarta y se avisa en ultimoAviso().
    bool importar(const QString& ruta, LibroTrabajo* libro, HojaCalculo* hoja,
                  char separador = 0);

    QString ultimoError() const;
    QString ultimoAviso() const;

private:
    QString mensajeError;
    QString mensajeAviso;

    static QString escaparCampo(const QString& texto, char separador);
    static char    detectarSeparador(const QString& primeraLinea);
};

#endif // ARCHIVOCSV_H
