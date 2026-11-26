#include <QApplication>
#include <QFont>
#include <QStyleFactory>

#include "VentanaPrincipal.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    app.setFont(QFont("Segoe UI", 10));
    app.setApplicationName("Libro de Cálculo Dinámico");

    VentanaPrincipal ventana;
    ventana.show();
    return app.exec();
}
