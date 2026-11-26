#include "VentanaPrincipal.h"

#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QKeySequence>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QStyle>

namespace {

QString pedirArchivo(QWidget* padre, bool guardar, const QString& titulo,
                     const QString& filtro, const QString& sugerido)
{
    if (guardar)
        return QFileDialog::getSaveFileName(padre, titulo, sugerido, filtro);
    return QFileDialog::getOpenFileName(padre, titulo, sugerido, filtro);
}

} // namespace

VentanaPrincipal::VentanaPrincipal(QWidget* parent)
    : QMainWindow(parent),
      libro(nullptr),
      tabla(nullptr),
      pestanas(nullptr),
      barraFormulas(nullptr),
      indicadorCelda(nullptr),
      cinta(nullptr),
      panelGraficos(nullptr),
      grafico(nullptr)
{
    setWindowTitle("Libro de Cálculo Dinámico");
    resize(1100, 700);
    setMinimumSize(800, 500);

    crearMenuPrincipal();
    aplicarEstilo();

    // La cuadrícula, la cinta y la barra de fórmulas entran en las siguientes partes.
    QLabel* portada = new QLabel(
        "Libro de Cálculo Dinámico\n\nElige una opción del menú para empezar", this);
    portada->setObjectName("portada");
    portada->setAlignment(Qt::AlignCenter);
    setCentralWidget(portada);

    statusBar()->showMessage("Listo");
}

VentanaPrincipal::~VentanaPrincipal()
{
}

void VentanaPrincipal::crearMenuPrincipal()
{
    const QStyle* estilo = style();
    const QIcon iconoNuevo    = estilo->standardIcon(QStyle::SP_FileIcon);
    const QIcon iconoAbrir    = estilo->standardIcon(QStyle::SP_DialogOpenButton);
    const QIcon iconoGuardar  = estilo->standardIcon(QStyle::SP_DialogSaveButton);
    const QIcon iconoSalir    = estilo->standardIcon(QStyle::SP_DialogCloseButton);
    const QIcon iconoDeshacer = estilo->standardIcon(QStyle::SP_ArrowBack);
    const QIcon iconoRehacer  = estilo->standardIcon(QStyle::SP_ArrowForward);

    QMenu* archivo = menuBar()->addMenu("&Archivo");
    QAction* nuevo = archivo->addAction(iconoNuevo, "&Nuevo libro");
    nuevo->setShortcut(QKeySequence::New);
    nuevo->setStatusTip("Crea un libro en blanco");
    connect(nuevo, &QAction::triggered, this, &VentanaPrincipal::alNuevoLibro);

    QAction* abrir = archivo->addAction(iconoAbrir, "&Abrir...");
    abrir->setShortcut(QKeySequence::Open);
    abrir->setStatusTip("Abre un libro en formato nativo .xls3");
    connect(abrir, &QAction::triggered, this, &VentanaPrincipal::alAbrirXls3);

    QAction* guardar = archivo->addAction(iconoGuardar, "&Guardar");
    guardar->setShortcut(QKeySequence::Save);
    guardar->setStatusTip("Guarda el libro en formato .xls3");
    connect(guardar, &QAction::triggered, this, &VentanaPrincipal::alGuardarXls3);

    QAction* guardarComo = archivo->addAction("Guardar &como...");
    guardarComo->setShortcut(QKeySequence::SaveAs);
    guardarComo->setStatusTip("Guarda el libro .xls3 con otro nombre");
    connect(guardarComo, &QAction::triggered, this, &VentanaPrincipal::alGuardarComo);

    archivo->addSeparator();

    QAction* importar = archivo->addAction("&Importar CSV...");
    importar->setStatusTip("Trae una hoja desde un archivo .csv");
    connect(importar, &QAction::triggered, this, &VentanaPrincipal::alImportarCSV);

    QAction* exportar = archivo->addAction("&Exportar CSV...");
    exportar->setStatusTip("Exporta la hoja activa a un archivo .csv");
    connect(exportar, &QAction::triggered, this, &VentanaPrincipal::alExportarCSV);

    archivo->addSeparator();

    QAction* salir = archivo->addAction(iconoSalir, "&Salir");
    salir->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));
    salir->setStatusTip("Cierra el programa");
    connect(salir, &QAction::triggered, this, &QWidget::close);

    QMenu* edicion = menuBar()->addMenu("&Edición");
    QAction* deshacer = edicion->addAction(iconoDeshacer, "&Deshacer");
    deshacer->setShortcut(QKeySequence::Undo);
    deshacer->setStatusTip("Revierte la última acción (Ctrl+Z)");
    connect(deshacer, &QAction::triggered, this, &VentanaPrincipal::alDeshacer);

    QAction* rehacer = edicion->addAction(iconoRehacer, "&Rehacer");
    rehacer->setShortcut(QKeySequence::Redo);
    rehacer->setStatusTip("Reaplica la acción deshecha (Ctrl+Y)");
    connect(rehacer, &QAction::triggered, this, &VentanaPrincipal::alRehacer);

    edicion->addSeparator();

    QAction* buscar = edicion->addAction("&Buscar y reemplazar...");
    buscar->setShortcut(QKeySequence::Find);
    buscar->setStatusTip("Busca y reemplaza texto en la hoja activa");
    connect(buscar, &QAction::triggered, this, &VentanaPrincipal::alBuscarReemplazar);

    QMenu* datos = menuBar()->addMenu("&Datos");
    QAction* ascendente = datos->addAction("Ordenar de &A a Z");
    ascendente->setStatusTip("Ordena el rango seleccionado de menor a mayor");
    connect(ascendente, &QAction::triggered, this, &VentanaPrincipal::alOrdenarAscendente);

    QAction* descendente = datos->addAction("Ordenar de &Z a A");
    descendente->setStatusTip("Ordena el rango seleccionado de mayor a menor");
    connect(descendente, &QAction::triggered, this, &VentanaPrincipal::alOrdenarDescendente);

    QMenu* graficos = menuBar()->addMenu("&Gráficos");
    QAction* barras = graficos->addAction("Gráfico de &barras");
    barras->setStatusTip("Grafica el rango seleccionado en barras");
    connect(barras, &QAction::triggered, this, &VentanaPrincipal::alGraficarBarras);

    QAction* pastel = graficos->addAction("Gráfico de &pastel");
    pastel->setStatusTip("Grafica el rango seleccionado en pastel");
    connect(pastel, &QAction::triggered, this, &VentanaPrincipal::alGraficarPastel);

    QMenu* hoja = menuBar()->addMenu("&Hoja");
    QAction* nuevaHoja = hoja->addAction("&Nueva hoja");
    nuevaHoja->setStatusTip("Agrega una pestaña al libro");
    connect(nuevaHoja, &QAction::triggered, this, &VentanaPrincipal::alAgregarHoja);

    QMenu* ayuda = menuBar()->addMenu("A&yuda");
    QAction* acerca = ayuda->addAction("&Acerca de...");
    acerca->setStatusTip("Información del proyecto");
    connect(acerca, &QAction::triggered, this, [this]() {
        QMessageBox::about(
            this,
            "Acerca de",
            "Libro de Cálculo Dinámico\n"
            "Proyecto final de Programación 3\n\n"
            "Hoja de cálculo tipo Excel.\n"
            "Interfaz gráfica y eventos.");
    });
}

void VentanaPrincipal::aplicarEstilo()
{
    QFile archivo(":/estilo.qss");
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    setStyleSheet(QString::fromUtf8(archivo.readAll()));
}

void VentanaPrincipal::alCambiarCelda(int, int) {}

void VentanaPrincipal::alSeleccionarCelda() {}

void VentanaPrincipal::alConfirmarBarraFormulas() {}

void VentanaPrincipal::alCambiarPestana(int) {}

void VentanaPrincipal::alAgregarHoja()
{
    statusBar()->showMessage("Nueva hoja: se conecta cuando estén las pestañas del libro.");
}

void VentanaPrincipal::alActualizarBarraEstado() {}

void VentanaPrincipal::alDeshacer()
{
    statusBar()->showMessage("Deshacer: se conecta con el historial del libro.");
}

void VentanaPrincipal::alRehacer()
{
    statusBar()->showMessage("Rehacer: se conecta con el historial del libro.");
}

void VentanaPrincipal::alNuevoLibro()
{
    rutaActual.clear();
    statusBar()->showMessage("Libro nuevo. La cuadrícula se arma en la siguiente parte.");
}

void VentanaPrincipal::alAbrirXls3()
{
    const QString ruta = pedirArchivo(
        this, false, "Abrir libro",
        "Libro de cálculo (*.xls3);;Todos los archivos (*)",
        rutaActual);
    if (ruta.isEmpty())
        return;

    rutaActual = ruta;
    statusBar()->showMessage("Archivo elegido: " + ruta + "  ·  la carga la hace el módulo de archivos");
}

void VentanaPrincipal::alGuardarXls3()
{
    if (rutaActual.isEmpty()) {
        alGuardarComo();
        return;
    }
    statusBar()->showMessage("Guardar en " + rutaActual + "  ·  la escritura la hace el módulo de archivos");
}

void VentanaPrincipal::alGuardarComo()
{
    const QString ruta = pedirArchivo(
        this, true, "Guardar libro",
        "Libro de cálculo (*.xls3)",
        rutaActual.isEmpty() ? QString("libro.xls3") : rutaActual);
    if (ruta.isEmpty())
        return;

    rutaActual = ruta;
    statusBar()->showMessage("Se guardará en " + ruta + "  ·  la escritura la hace el módulo de archivos");
}

void VentanaPrincipal::alImportarCSV()
{
    const QString ruta = pedirArchivo(
        this, false, "Importar CSV",
        "CSV (*.csv);;Todos los archivos (*)",
        QString());
    if (ruta.isEmpty())
        return;
    statusBar()->showMessage("CSV elegido: " + ruta + "  ·  la importación la hace el módulo de archivos");
}

void VentanaPrincipal::alExportarCSV()
{
    const QString ruta = pedirArchivo(
        this, true, "Exportar CSV",
        "CSV (*.csv)",
        QString("hoja.csv"));
    if (ruta.isEmpty())
        return;
    statusBar()->showMessage("CSV de salida: " + ruta + "  ·  la exportación la hace el módulo de archivos");
}

void VentanaPrincipal::alOrdenarAscendente()
{
    statusBar()->showMessage("Ordenar A-Z: se aplica al rango cuando exista la cuadrícula.");
}

void VentanaPrincipal::alOrdenarDescendente()
{
    statusBar()->showMessage("Ordenar Z-A: se aplica al rango cuando exista la cuadrícula.");
}

void VentanaPrincipal::alBuscarReemplazar()
{
    statusBar()->showMessage("Buscar y reemplazar: el cuadro se agrega con la cuadrícula.");
}

void VentanaPrincipal::alGraficarBarras()
{
    statusBar()->showMessage("Gráfico de barras: se conecta cuando haya un rango seleccionado.");
}

void VentanaPrincipal::alGraficarPastel()
{
    statusBar()->showMessage("Gráfico de pastel: se conecta cuando haya un rango seleccionado.");
}
