#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ///Columnas
    setWindowTitle("Library");

    ///Columnas
    Table (1,1,1,1,1,1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Table(int N, int At, int An, int T, int D, int L){

    ///Lista de Labels
    QStringList titulos;

    col=0;
    fil=20;

    ///Cantidad de columnas
    if (N==1){
       titulos.append("Nombre");
       Nombre=col;
       col+=1;
    }
    if (At==1){
       titulos.append("Autor");
       Autor=col;
       col+=1;
    }
    if (An==1){
       titulos.append("Año");
       Year=col;
       col+=1;
    }
    if (T==1){
       titulos.append("Tamaño");
       Size=col;
       col+=1;
    }
    if (D==1){
       titulos.append("Descripción");
       Descripcion=col;
       col+=1;
    }
    if (L==1){
       titulos.append("Link");
       Link=col;
       col+=1;
    }

    num = 840/col;
    num2 = 441/13;

    ui->tableWidget->setColumnCount(col);
    ui->tableWidget->setHorizontalHeaderLabels(titulos);

    ///Modifica el tam de las columnas
    for (int i=0;i<col;i++){
        ui->tableWidget->setColumnWidth(i,num);
    }

    //ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Nombre"));

    for (int i=0;i<fil;i++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        int fila = ui->tableWidget->rowCount()-1;
        ui->tableWidget->setItem(fila,Nombre,new QTableWidgetItem("Edgar Gonzalez"));
        ui->tableWidget->setItem(fila,Link,new QTableWidgetItem("  >  "));
    }


}

void MainWindow::funcionInsert(string comando)
{
    cout << comando << endl;
}

void MainWindow::funcionSelect(string comando)
{
    cout << comando << endl;
}

void MainWindow::funcionUpdate(string comando)
{
    cout << comando << endl;
}

void MainWindow::funcionDelete(string comando)
{
    cout << comando << endl;
}

///BOTONES

void MainWindow::on_BotonImg_clicked()
{
    ///Agregra a la listViewWig
    /*for (int i=1;i<=3;i++){

        ui->listWidgetGaleria->addItem("    Galeria "+QString::number(i));

        for (int j=1;j<=10;j++){
            ui->listWidgetGaleria->addItem("            Imagen "+QString::number(j));
        }

    }*/

    ui->listWidgetGaleria->addItem("            "+ui->imagen->text());

}

void MainWindow::on_BotonGal_clicked()
{
    ui->listWidgetGaleria->addItem("    "+ui->galeria->text());
}

void MainWindow::on_BotonEJECUTAR_clicked()
{
    string comando = ui->LineaCMD->toPlainText().toStdString();
    string subs = comando.substr(0,7);
    string cmd = comando.substr(7);
    if (subs.compare("INSERT ") == 0 || subs.compare("insert ") == 0){
        cout << "Funcion INSERT" << endl;
        funcionInsert(cmd);
        ui->LineaCMD->clear();
    }else if (subs.compare("SELECT ") == 0 || subs.compare("select ") == 0){
        cout << "Funcion SELECT" << endl;
        funcionSelect(cmd);
        ui->LineaCMD->clear();
    }else if (subs.compare("UPDATE ") == 0 || subs.compare("update ") == 0){
        cout << "Funcion UPDATE" << endl;
        funcionUpdate(cmd);
        ui->LineaCMD->clear();
    }else if (subs.compare("DELETE ") == 0 || subs.compare("delete ") == 0){
        cout << "Funcion DELETE" << endl;
        funcionDelete(cmd);
        ui->LineaCMD->clear();
    }else {
        cout << "Syntax error" << endl;
    }
}

