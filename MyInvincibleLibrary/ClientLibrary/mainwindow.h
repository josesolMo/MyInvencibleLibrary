#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void Table(int N, int At, int An, int T, int D, int L);

private slots:
    void on_BotonImg_clicked();

    void on_BotonGal_clicked();

private:
    Ui::MainWindow *ui;

    ///Cantidad de columnas
    int num,num2,col,fil;
    int Nombre,Autor,Year,Size,Descripcion,Link;
};

#endif // MAINWINDOW_H
