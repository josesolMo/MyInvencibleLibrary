#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <string>
#include <cstdlib>
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <json-c/json.h>
#include <json-c/debug.h>
#include <json-c/json_object.h>
#include <QMessageBox>

#define PORT 3550
#define MAXDATASIZE 999999

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

    void Table(int FID, int N, int At, int An, int T, int D, int L);

    string decimalToBinary(int d);
    string decimalToHex(int d);
    string BMPtoBinaryData(string directory);

    string hexDataToBMP(string name, string hexData);

    int hexToDecimal(string h);

    int sendJSON(json_object *jObj);
    //int sendJSON(string KEY, string data);

    void Iniciar();

private slots:
    void on_BotonImg_clicked();

    void on_BotonGal_clicked();

    void on_BotonEJECUTAR_clicked();

    void on_BotonRolback_clicked();

    void on_BotonCommit_clicked();

    void on_BotonIniciar_clicked();

    void on_BotonGal_Delete_clicked();

    void on_BotonLink_clicked();

private:
    Ui::MainWindow *ui;

    ///Cantidad de columnas
    int num,num2,col,fil;
    int Nombre,Autor,Year,Size,Descripcion,Link,FileID;

    ///Imagen
    QPixmap* Imag;

    ///QGraphicsView
    QGraphicsView * view;

    ///La ventana de la imagen
    QGraphicsScene* VentanaImagen;

    ///Instancia estática del contenedor del BinaryData
    string binaryData;

    ///Objeto JSON para sendJSON()
    json_object *jObj;

    ///Keys SENDJSON
    QString nombreGaleria, newImage, console, iniciar, rollBack, commit,selectImageHexa;

    ///Keys para completar la tabla de comandos
    QString NombreS,AutorS,YearS,SizeS,DescripcionS,FileIDS;

    ///json object para graficar la tabla
    struct json_object *tablaFinal;

    ///json object para graficar las galerias
    struct json_object *GaleriasEnBD;

    ///Valor para iniciar el IDE
    bool ValorInicial;

};

#endif // MAINWINDOW_H
