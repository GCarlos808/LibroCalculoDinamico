#include <QApplication>
#include <QLabel>

// reemplazar por VentanaPrincipal cuando exista su .cpp
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QLabel etiqueta("Libro de Calculo Dinamico - esqueleto");
    etiqueta.resize(320, 80);
    etiqueta.show();
    return app.exec();
}
