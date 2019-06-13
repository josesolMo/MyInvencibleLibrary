#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <string>
#include <vector>



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
        if (subs.length()< space){
            cout << "Syntax error" << endl;
            return;
        }
        string galery = subs.substr(0, space);
        cout << galery << endl;
        subs = subs.substr(space+1);
        vector <string> order;
        if((subs.substr(0,1)).compare("(") == 0){
            size_t columnsEnd = subs.find(")");
            if (subs.length()< columnsEnd){
                cout << "Syntax error" << endl;
                return;
            }
            string columns = subs.substr(1, columnsEnd);
            cout << columns << endl;
            subs = subs.substr(columnsEnd+1);
            while (columns.compare(")") != 0){
                size_t coma = columns.find(",");
                string current;
                if (columns.length()< coma){
                    current = columns.substr(0, columns.length()-1);
                    //cout << current << endl;
                    columns = columns.substr(current.length(),columns.length()-1);
                }
                else {
                    current = columns.substr(0, coma);
                    //cout << current << endl;
                    columns = columns.substr(coma+1);
                    //cout << columns << endl;
                }
                if(current[0] == ' '){
                    current = current.substr(1);
                }
                if (current[current.length()-1] == ' '){
                    current = current.substr(0, current.length()-1);
                }
                cout << current << endl;
                cout << columns << endl;
                current = columnaGET(current);
                if(current.compare("F") == 0){
                    cout << "No existe ese dato en la tabla" << endl;
                    return;
                }
                else {
                    order.push_back(current);
                }
            }
            int C = 0;
            while (C < order.size()){
                cout << order[C] << endl;
                C++;
            }
        }
        else {
            order.push_back("A");
            order.push_back("B");
            order.push_back("C");
            order.push_back("D");
            order.push_back("E");

        }
        size_t values = subs.find("VALUES ");
        if(values > 2){
            cout << "Syntax error" << endl;
            return;
        }

        subs = subs.substr(values+7);
        cout << subs << endl;

        if((subs.substr(0,1)).compare("(") == 0){
            size_t valuesEnd = subs.find(")");
            if (subs.length()< valuesEnd){
                cout << "Syntax error" << endl;
                return;
            }
            string values = subs.substr(1, valuesEnd);
            cout << values << endl;
            int c = 0;
            while (values.compare(")") != 0){
                size_t coma = values.find(",");
                string current;
                if (values.length()< coma){
                    current = values.substr(0, values.length()-1);
                    cout << current << endl;
                    values = values.substr(current.length(),values.length()-1);
                    int min = order.size()-1;
                    if(c != min){
                        cout << "Faltan valores o sobran" << endl;
                        return;
                    }
                }
                else {
                    current = values.substr(0, coma);
                    cout << current << endl;
                    values = values.substr(coma+1);
                    cout << values << endl;
                }
                if(current[0] == '"'){
                    current = current.substr(1);
                }
                if (current[current.length()-1] == '"'){
                    current = current.substr(0, current.length()-1);
                }
                //cout << current << endl;
                //cout << columns << endl;
                addToTable(order[c],current);
                c++;
            }
            ui->LineaCMD->clear();
            return;
        }
        else {
            cout << "Syntax error" << endl;
            return;
        }
    }
    else {
        cout << "Syntax error" << endl;
        return;
    }
}

void MainWindow::funcionSelect(string comando)
{
    string subs = comando;
    cout << subs << endl;
    if (subs[0] == '*'){
        size_t From = subs.find("FROM ");
        if (3 < From){
            cout << "Syntax error" << endl;
            return;
        }
        subs = subs.substr(From+5);
        size_t pycoma = subs.find(";");
        if (subs.length()< pycoma){
            cout << "Syntax error" << endl;
            return;
        }
        string tabla = subs.substr(0, pycoma);
        cout << tabla << endl;
        if(tabla[0] == ' '){
            tabla = tabla.substr(1);
        }
        if (tabla[tabla.length()-1] == ' '){
            tabla = tabla.substr(0, tabla.length()-1);
        }
        subs = subs.substr(pycoma+1);
        cout << subs << endl;
        if(subs.compare("") == 0 || subs.compare(" ") == 0){
            cout << "Imprimir valores de tabla" << endl;
            return;
        }
        else{
            size_t where = subs.find("WHERE ");
            if (2 < where){
                cout << "Syntax error" << endl;
                return;
            }
            subs = subs.substr(where+6);
            if (subs.substr(0,4).compare("NOT ") == 0){
                subs = subs.substr(0,4);
                size_t comand = subs.find("= ");
                if (subs.length() > comand){
                    string column = subs.substr(0, comand);
                    subs = subs.substr(comand+2);
                    cout << column << endl;
                    size_t pycoma = subs.find(";");
                    if (subs.length()< pycoma){
                        cout << "Syntax error" << endl;
                        return;
                    }
                    string value = subs.substr(0, pycoma);
                    cout << value << endl;
                    if(value[0] == '"'){
                        value = value.substr(1);
                    }
                    if (value[value.length()-1] == '"'){
                        value = value.substr(0, value.length()-1);
                    }
                    cout << value << endl;
                    return;
                }

                comand = subs.find("< ");
                if (subs.length() > comand){
                    string column = subs.substr(0, comand);
                    subs = subs.substr(comand+2);
                    cout << column << endl;
                }

                comand = subs.find("> ");
                if (subs.length() > comand){
                    string column = subs.substr(0, comand);
                    subs = subs.substr(comand+2);
                    cout << column << endl;
                }

                comand = subs.find(">= ");
                if (subs.length() > comand){
                    string column = subs.substr(0, comand);
                    subs = subs.substr(comand+3);
                    cout << column << endl;
                }

                comand = subs.find("<= ");
                if (subs.length() > comand){
                    string column = subs.substr(0, comand);
                    subs = subs.substr(comand+3);
                    cout << column << endl;
                }
                else{
                    cout << "Syntax error" << endl;
                    return;
                }

            }
            else {

                size_t comand = subs.find("NOT ");
                if (subs.length() > comand){
                    string column = subs.substr(0, comand);
                    subs = subs.substr(comand+3);
                    cout << column << endl;
                }

                comand = subs.find("BETWEEN ");
                if (subs.length() > comand){
                    string column = subs.substr(0, comand);
                    subs = subs.substr(comand+8);
                    cout << column << endl;
                }

                comand = subs.find("IN ");
                if (subs.length() > comand){
                    string column = subs.substr(0, comand);
                    subs = subs.substr(comand+3);
                    cout << column << endl;
                }

                comand = subs.find("= ");
                if (subs.length() > comand){
                    string column = subs.substr(0, comand);
                    subs = subs.substr(comand+2);
                    cout << column << endl;
                }

                comand = subs.find("< ");
                if (subs.length() > comand){
                    string column = subs.substr(0, comand);
                    subs = subs.substr(comand+2);
                    cout << column << endl;
                }

                comand = subs.find("> ");
                if (subs.length() > comand){
                    string column = subs.substr(0, comand);
                    subs = subs.substr(comand+2);
                    cout << column << endl;
                }

                comand = subs.find(">= ");
                if (subs.length() > comand){
                    string column = subs.substr(0, comand);
                    subs = subs.substr(comand+3);
                    cout << column << endl;
                }

                comand = subs.find("<= ");
                if (subs.length() > comand){
                    string column = subs.substr(0, comand);
                    subs = subs.substr(comand+3);
                    cout << column << endl;
                }

                comand = subs.find("IS ");
                if (subs.length() > comand){
                    string column = subs.substr(0, comand);
                    subs = subs.substr(comand+3);
                    cout << column << endl;
                }

                comand = subs.find("LIKE ");
                if (subs.length() > comand){
                    string column = subs.substr(0, comand);
                    subs = subs.substr(comand+5 );
                    cout << column << endl;
                }
                else{
                    cout << "Syntax error" << endl;
                    return;
                }
            }


            /*
             * COLOCAR TODAS LAS POSIBLES CONDICIONALES[BETWEEN(AND, OR, NOT),IS(NULL, NOT NULL),LIKE]
             */
        }
    }
    else if(subs.find("FROM ") < subs.length()){

    }
    else {
        cout << "Syntax error" << endl;
        return;
    }

}

void MainWindow::funcionUpdate(string comando)
{
    cout << comando << endl;
}

void MainWindow::funcionDelete(string comando)
{
    cout << comando << endl;
}

string MainWindow::columnaGET(string evaluar)
{
    if(evaluar.compare("Fecha") == 0){
        return "A";
    }
    else if(evaluar.compare("Nombre") == 0){
        return "B";

    }
    else if(evaluar.compare("Autor") == 0){
        return "C";

    }
    else if(evaluar.compare("Tamano") == 0){
        return "D";

    }
    else if(evaluar.compare("Descripcion") == 0){
        return "E";

    }
    else{
        return "F";

    }
}

void MainWindow::addToTable(string columna, string value)
{
    if(columna.compare("A") == 0){
        this->fecha = value;
    }
    else if(columna.compare("B") == 0){
        this->nombre = value;
    }
    else if(columna.compare("C") == 0){
        this->autor = value;
    }
    else if(columna.compare("D") == 0){
        this->size = value;
    }
    else if(columna.compare("E") == 0){
        this->descripcion = value;
    }
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
    if(comando.length() < 7){
        cout << "Syntax error" << endl;

    }
    else {
        string subs = comando.substr(0,7);
        string cmd = comando.substr(7);
        if (subs.compare("INSERT ") == 0 || subs.compare("insert ") == 0){
            cout << "Funcion INSERT" << endl;
            //sendJSON("INSERT",cmd);
            funcionInsert(cmd);
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

}

/***int MainWindow::sendJSON(string KEY, string data){
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

}*/

