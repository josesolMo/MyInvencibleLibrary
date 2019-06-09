#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <string>


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
    string subs = comando.substr(0,5);
    if (subs.compare("INTO ") == 0 ||subs.compare("into ") == 0){
        subs = comando.substr(5);
        size_t space = subs.find(" ");
        string galery = subs.substr(0, space+1);
        cout << galery << endl;
    }
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
        //sendJSON("INSERT",cmd);
        funcionInsert(cmd);
        ui->LineaCMD->clear();
    }else if (subs.compare("SELECT ") == 0 || subs.compare("select ") == 0){
        cout << "Funcion SELECT" << endl;
        //sendJSON("SELECT",cmd);
        funcionSelect(cmd);
        ui->LineaCMD->clear();
    }else if (subs.compare("UPDATE ") == 0 || subs.compare("update ") == 0){
        cout << "Funcion UPDATE" << endl;
        //sendJSON("UPDATE",cmd);
        funcionUpdate(cmd);
        ui->LineaCMD->clear();
    }else if (subs.compare("DELETE ") == 0 || subs.compare("delete ") == 0){
        cout << "Funcion DELETE" << endl;
        //sendJSON("DELETE",cmd);
        funcionDelete(cmd);
        ui->LineaCMD->clear();
    }else {
        cout << "Syntax error" << endl;
    }
}

int MainWindow::sendJSON(string KEY, string data){
    char* str;
    int fd, numbytes;
    struct sockaddr_in client;

    fd = socket(AF_INET, SOCK_STREAM, 0);

    char sendBuff[MAXDATASIZE];
    char recvBuff[MAXDATASIZE];

    struct hostent *he;

    if (fd < 0)
    {
        printf("Error : Could not create socket\n");
        return 1;
    }
    else
    {
        client.sin_family = AF_INET;
        client.sin_port = htons(PORT);
        client.sin_addr.s_addr = inet_addr("192.168.100.6"); //192.168.100.6
        memset(client.sin_zero, '\0', sizeof(client.sin_zero));
    }

    if (::connect(fd, (const struct sockaddr *)&client, sizeof(client)) < 0)
    {
        printf("ERROR connecting to server\n");
        return 1;
    }


    json_object *jobj = json_object_new_object();

    json_object *jstring = json_object_new_string(data.c_str());

    json_object_object_add(jobj,KEY.c_str(), jstring);


    if (strcpy(sendBuff, json_object_to_json_string(jobj)) == NULL) {
        printf("ERROR strcpy()");
        exit(-1);
    }

    if (write(fd, sendBuff, strlen(sendBuff)) == -1)
    {
        printf("ERROR write()");
        exit(-1);
    }

    if ((numbytes=recv(fd,recvBuff,MAXDATASIZE,0)) < 0){

        printf("Error en recv() \n");
        exit(-1);
    }

    struct json_object *INSERTD;
    json_object *parsed_jsonInsertD = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonInsertD, "INSERT", &INSERTD);
    if (json_object_get_string(INSERTD) != 0) {
        insertD = json_object_get_string(INSERTD);;
    }

    struct json_object *SELECTD;
    json_object *parsed_jsonSelectD = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonSelectD, "SELECT", &SELECTD);
    if (json_object_get_string(SELECTD) != 0) {
        selectD = json_object_get_string(SELECTD);;
    }

    struct json_object *UPDATED;
    json_object *parsed_jsonUpdateD = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonUpdateD, "UPDATE", &UPDATED);
    if (json_object_get_string(UPDATED) != 0) {
        updateD = json_object_get_string(UPDATED);;
    }

    struct json_object *DELETED;
    json_object *parsed_jsonDeleteD = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonDeleteD, "DELETE", &DELETED);
    if (json_object_get_string(DELETED) != 0) {
        deleteD = json_object_get_string(DELETED);;
    }

    ///Se limpian los Buffers
    memset(recvBuff, 0, MAXDATASIZE);
    memset(sendBuff, 0, MAXDATASIZE);

    ::close(fd);

}
