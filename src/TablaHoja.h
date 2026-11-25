#ifndef TABLAHOJA_H
#define TABLAHOJA_H

//  TablaHoja.h - QTableWidget propio para capturar teclado explicito
#include <QTableWidget>

class TablaHoja : public QTableWidget {
    Q_OBJECT
public:
    explicit TablaHoja(QWidget* parent = nullptr);

signals:
    void solicitaDeshacer();
    void solicitaRehacer();
    void solicitaCopiar();
    void solicitaPegar();
    void solicitaLimpiar(); // tecla Supr
    void solicitaGuardar(); // Ctrl+S

protected:
    void keyPressEvent(QKeyEvent* evento) override;
};

#endif // TABLAHOJA_H
