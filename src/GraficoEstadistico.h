#ifndef GRAFICOESTADISTICO_H
#define GRAFICOESTADISTICO_H

#include <QWidget>
#include <QString>
#include <QChartView>
#include "Tipos.h"

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
QT_CHARTS_USE_NAMESPACE
#endif

class HojaCalculo;

enum class TipoGrafico { Barras, Pastel };

class GraficoEstadistico : public QWidget {
    Q_OBJECT
public:
    explicit GraficoEstadistico(QWidget* parent = nullptr);
    ~GraficoEstadistico();

    bool establecerRango(const HojaCalculo* hoja, const Rango& rango, TipoGrafico tipo, const QString& titulo = QString());

    void mostrarBarras(const QString& titulo, const QString* etiquetas, const double* valores, int cantidad);
    void mostrarPastel(const QString& titulo, const QString* etiquetas, const double* valores, int cantidad);

    void limpiar();
    bool guardarImagen(const QString& ruta) const;   // PNG / JPG

private:
    QChartView* vista;

    void reemplazarGrafico(QChart* nuevo);   // libera el grafico anterior (evita fugas)
};

#endif // GRAFICOESTADISTICO_H
