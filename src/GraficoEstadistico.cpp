#include "GraficoEstadistico.h"
#include "HojaCalculo.h"
#include "Celda.h"
#include "Coordenadas.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QPixmap>
#include <QChart>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QPieSeries>
#include <QPieSlice>

GraficoEstadistico::GraficoEstadistico(QWidget* parent) : QWidget(parent), vista(new QChartView(this)) {
    QVBoxLayout* disposicion = new QVBoxLayout(this);
    disposicion->setContentsMargins(0, 0, 0, 0);
    disposicion->addWidget(vista);
    vista->setRenderHint(QPainter::Antialiasing);
}

GraficoEstadistico::~GraficoEstadistico() {

}

void GraficoEstadistico::reemplazarGrafico(QChart* nuevo) {
    QChart* anterior = vista->chart();
    vista->setChart(nuevo);
    delete anterior;
}

bool GraficoEstadistico::establecerRango(const HojaCalculo* hoja, const Rango& rangoEntrada, TipoGrafico tipo, const QString& titulo){
    if (hoja == nullptr) return false;

    Rango rango = rangoEntrada;
    rango.normalizar();
    if (!hoja->coordenadaValida(rango.fila1, rango.columna1) ||
        !hoja->coordenadaValida(rango.fila2, rango.columna2))
        return false;

    const bool unaColumna = (rango.cantidadColumnas() == 1);
    const int  colEtiqueta = rango.columna1;
    const int  colValor    = unaColumna ? rango.columna1 : rango.columna1 + 1;

    // 1: contar filas graficables
    int cantidad = 0;
    for (int f = rango.fila1; f <= rango.fila2; ++f) {
        const Celda* c = hoja->celda(f, colValor);
        if (c != nullptr && c->esNumerica()) {
            if (tipo == TipoGrafico::Pastel && c->valorNumerico() <= 0) continue;
            ++cantidad;
        }
    }
    if (cantidad == 0) return false;

    // 2: copiar a arreglos dinamicos propios
    QString* etiquetas = new QString[cantidad];
    double*  valores   = new double[cantidad];
    int i = 0;
    for (int f = rango.fila1; f <= rango.fila2 && i < cantidad; ++f) {
        const Celda* cv = hoja->celda(f, colValor);
        if (cv == nullptr || !cv->esNumerica()) continue;
        if (tipo == TipoGrafico::Pastel && cv->valorNumerico() <= 0) continue;

        valores[i] = cv->valorNumerico();
        if (unaColumna) {
            etiquetas[i] = Coordenadas::textoCelda(f, colEtiqueta);
        } else {
            const Celda* ce = hoja->celda(f, colEtiqueta);
            etiquetas[i] = (ce != nullptr && !ce->textoMostrado().isEmpty())
                               ? ce->textoMostrado()
                               : Coordenadas::textoCelda(f, colEtiqueta);
        }
        ++i;
    }

    if (tipo == TipoGrafico::Barras) mostrarBarras(titulo, etiquetas, valores, cantidad);
    else                             mostrarPastel(titulo, etiquetas, valores, cantidad);

    delete[] etiquetas;
    delete[] valores;
    return true;
}

void GraficoEstadistico::mostrarBarras(const QString& titulo, const QString* etiquetas, const double* valores, int cantidad)
{
    QBarSet* conjunto = new QBarSet(tr("Valores"));
    for (int i = 0; i < cantidad; ++i)
        conjunto->append(valores[i]);

    QBarSeries* serie = new QBarSeries();
    serie->append(conjunto); // la serie se hace duena del QBarSet

    QChart* grafico = new QChart();
    grafico->addSeries(serie); // el grafico se hace duenio de la serie
    grafico->setTitle(titulo.isEmpty() ? tr("Grafico de barras") : titulo);
    grafico->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis* ejeX = new QBarCategoryAxis();
    for (int i = 0; i < cantidad; ++i) ejeX->append(etiquetas[i]);
    grafico->addAxis(ejeX, Qt::AlignBottom); // el grafico se hace duenio del eje
    serie->attachAxis(ejeX);

    QValueAxis* ejeY = new QValueAxis();
    grafico->addAxis(ejeY, Qt::AlignLeft);
    serie->attachAxis(ejeY);

    grafico->legend()->setVisible(false);
    reemplazarGrafico(grafico);
}

void GraficoEstadistico::mostrarPastel(const QString& titulo, const QString* etiquetas, const double* valores, int cantidad) {
    double total = 0;
    for (int i = 0; i < cantidad; ++i)
        total += valores[i];

    QPieSeries* serie = new QPieSeries();
    for (int i = 0; i < cantidad; ++i) {
        QPieSlice* porcion = serie->append(etiquetas[i], valores[i]);   // la serie se hace duena de la porcion
        if (total > 0)
            porcion->setLabel(QString("%1 (%2%)").arg(etiquetas[i]).arg(valores[i] / total * 100.0, 0, 'f', 1));
    }
    serie->setLabelsVisible(true);

    QChart* grafico = new QChart();
    grafico->addSeries(serie);
    grafico->setTitle(titulo.isEmpty() ? tr("Grafico de pastel") : titulo);
    grafico->setAnimationOptions(QChart::SeriesAnimations);
    grafico->legend()->setAlignment(Qt::AlignRight);
    reemplazarGrafico(grafico);
}

void GraficoEstadistico::limpiar() {
    reemplazarGrafico(new QChart());
}

bool GraficoEstadistico::guardarImagen(const QString& ruta) const {
    return vista->grab().save(ruta);
}
