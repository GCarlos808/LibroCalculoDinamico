#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

//  VentanaPrincipal.h - Ventana principal tipo suite ofimatica.

#include <QMainWindow>
#include <QString>

class QTabWidget;
class QLineEdit;
class QLabel;
class QToolBar;
class QDockWidget;
class TablaHoja;
class LibroTrabajo;
class HojaCalculo;
class GraficoEstadistico;

class VentanaPrincipal : public QMainWindow {
    Q_OBJECT
public:
    explicit VentanaPrincipal(QWidget* parent = nullptr);
    ~VentanaPrincipal();

private slots:
    // edicion y formato
    void alCambiarCelda(int fila, int columna);
    void alSeleccionarCelda();
    void alConfirmarBarraFormulas();
    void alCambiarPestana(int indice);
    void alAgregarHoja();
    void alActualizarBarraEstado();
    void alDeshacer();
    void alRehacer();

    // archivos y herramientas
    void alNuevoLibro();
    void alAbrirXls3();
    void alGuardarXls3();
    void alGuardarComo();
    void alImportarCSV();
    void alExportarCSV();
    void alOrdenarAscendente();
    void alOrdenarDescendente();
    void alBuscarReemplazar();
    void alGraficarBarras();
    void alGraficarPastel();

private:
    LibroTrabajo* libro;
    TablaHoja* tabla;
    QTabWidget* pestanas;
    QLineEdit* barraFormulas;
    QLabel* indicadorCelda;
    QToolBar* cinta;
    QDockWidget* panelGraficos;
    GraficoEstadistico* grafico;
    QString rutaActual;
};

#endif // VENTANAPRINCIPAL_H
