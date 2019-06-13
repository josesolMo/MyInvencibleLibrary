#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <stdio.h>
#include <json-c/json.h>
#include <json-c/debug.h>
#include <json-c/json_object.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <strings.h>
#include <unistd.h>
#include <cstring>

#define PORT 3550
#define MAXDATASIZE 1000

using namespace std;

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

    int sendJSON(string KEY, string data);

private slots:
    void on_BotonImg_clicked();

    void on_BotonGal_clicked();

    void on_BotonEJECUTAR_clicked();

private:
    Ui::MainWindow *ui;

    ///Cantidad de columnas
    int num,num2,col,fil;
    int Nombre,Autor,Year,Size,Descripcion,Link;

    void funcionInsert(string comando);
    void funcionSelect(string comando);
    void funcionUpdate(string comando);
    void funcionDelete(string comando);

    string columnaGET(string evaluar);

    void addToTable(string columna, string value);

    string fecha;
    string autor;
    string nombre;
    string descripcion;
    string size;

    string insertD;
    string selectD;
    string deleteD;
    string updateD;
};

#endif // MAINWINDOW_H
