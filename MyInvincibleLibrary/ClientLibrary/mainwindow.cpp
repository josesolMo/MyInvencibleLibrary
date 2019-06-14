#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QFileDialog>
#include <unistd.h>


/**
 * Crar el MainWindow.
 * @param -
 * @return grafication
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ///Columnas
    setWindowTitle("Library");

    ///Columnas
    Table (1,1,1,1,1,1,1);

}

MainWindow::~MainWindow()
{
    delete ui;
}


/**
 * Grafica las columnas solicitadas por la barra de comandos.
 * @param File_Id,Nombre,Autor,Year,Tamano,Descripcion,Link
 * @return grafication
 */
void MainWindow::Table(int FID, int N, int At, int An, int T, int D, int L){

    ///Lista de Labels
    QStringList titulos;

    col=0;

    ///Cantidad de columnas
    if (FID==1){
       titulos.append("File_ID");
       FileID=col;
       col+=1;
    }
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

}


/**
 * Envia JSON al servidor para agregar nuevas imagenes.
 * @param -
 * @return grafication
 */
void MainWindow::on_BotonImg_clicked()
{

    if (ui->comboBoxGalerias->count()>0){

        ///Busca la imagen
        QString imagen = QFileDialog::getOpenFileName(this, "Imagen - Open file", "", "Imagen Files (*.bmp);;All Files (*.*)");

        ///Direccion de la imagen seleccionada
        string DireccionImagen = imagen.toStdString();

        ///Se crea el BinaryData
        BMPtoBinaryData(DireccionImagen);

        int p;

        for (int i=0; i<DireccionImagen.length();i++){
            if (DireccionImagen[i] == '/'){
                p=i;
            }
        }


        ///Nombre de la imagen
        string nombreImagen = DireccionImagen.substr(p+1,DireccionImagen.length()-4);
        ///Imagen comprimida en bits
        string BData = binaryData;
        ///Nombre de la galeria
        QString nomGaleria;

        ///Indice de la galeria
        int indice = 0;

        for (int i=0; i<ui->listWidgetGaleria->count();i++){

           if ("    "+(ui->listWidgetGaleria->item(i)->text())==ui->comboBoxGalerias->currentText()){

                ///Indice
                indice=i;

                ///Nombre de la galeria
                nomGaleria = ui->listWidgetGaleria->item(i)->text();

                i=ui->listWidgetGaleria->count()+1;
            }

        }

        ///Objeto JSON
        jObj = json_object_new_object();

        ///Variables para agregar como Key y Data
        string jsonKEY = "NEWIMAGE";
        string jsonData = nombreImagen;

        string jsonKEY2 = "BINARYDATA";
        string jsonData2 = BData;

        string jsonKEY3 = "GALLERY";
        string jsonData3 = nomGaleria.toStdString();

        ///Se agrega la informacion en el JSON
        json_object *jstring = json_object_new_string(jsonData.c_str());
        json_object_object_add(jObj,jsonKEY.c_str(), jstring);

        json_object *jstring2 = json_object_new_string(jsonData2.c_str());
        json_object_object_add(jObj,jsonKEY2.c_str(), jstring2);

        json_object *jstring3 = json_object_new_string(jsonData3.c_str());
        json_object_object_add(jObj,jsonKEY3.c_str(), jstring3);

        ///Se envia el JSON, se utiliza de parametro solo el jObject
        sendJSON(jObj);

        if (newImage=="1"){

            ui->listWidgetGaleria->insertItem(indice+1,"           "+QString::fromStdString(nombreImagen));

            VentanaImagen = new QGraphicsScene(this);

            ///Imagen que se mostrara
            Imag = new QPixmap(imagen);

            ///crear View
            view = new QGraphicsView(VentanaImagen);
            view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            view->setFixedSize(Imag->width(),Imag->height());
            VentanaImagen->setSceneRect(0,0,Imag->width(),Imag->height());
            VentanaImagen->backgroundBrush();

            //Muestra el view
            view->show();

            VentanaImagen->addPixmap(*Imag);

        }

        else if (newImage=="0"){
            QMessageBox::information(this, tr("ERROR"), tr("Selecione Una Nueva Imagen"));
        }

        else{
            QMessageBox::information(this, tr("ERROR"), tr("Selecione Una Nueva Imagen"));
        }

    }

    else{
        QMessageBox::information(this, tr("ERROR"), tr("Selecione Una Galeria"));
    }

}


/**
 * Envia JSON al servidor para agregar nuevas galerias.
 * @param -
 * @return grafication
 */
void MainWindow::on_BotonGal_clicked()
{

    if (ui->galeria->text()!=0){


        ///Objeto JSON
        jObj = json_object_new_object();

        ///Variables para agregar como Key y Data
        string jsonKEY = "NEWGALLERY";
        string jsonData = ui->galeria->text().toStdString();

        ///Se agrega la informacion en el JSON
        json_object *jstring = json_object_new_string(jsonData.c_str());
        json_object_object_add(jObj,jsonKEY.c_str(), jstring);

        ///Se envia el JSON, se utiliza de parametro solo el jObject
        sendJSON(jObj);

        if (NombreGaleria=="1"){

            ui->listWidgetGaleria->addItem(ui->galeria->text());
            ui->listWidgetGaleria->item(ui->listWidgetGaleria->count()-1)->setCheckState(Qt::Unchecked);
            QColor *color = new QColor;
            color->setRgb(23,58,216);
            ui->listWidgetGaleria->item(ui->listWidgetGaleria->count()-1)->setTextColor(*color);

            ui->comboBoxGalerias->addItem("    "+ui->galeria->text());
        }

        else if (NombreGaleria=="0"){
            QMessageBox::information(this, tr("ERROR"), tr("Ya Existe Esta Galeria, Ingrese Una Nueva"));
        }

        ui->galeria->setText("");

    }

    else{
        QMessageBox::information(this, tr("ERROR"), tr("Ingrese Una Galeria Nueva"));
    }

}


/**
 * Envia JSON al servidor con el string.
 * @param -
 * @return grafication
 */
void MainWindow::on_BotonEJECUTAR_clicked()
{
    ui->tableWidget->setRowCount(0);

    if (ui->LineaCMD->toPlainText()!=0){

        /*///Objeto JSON
        jObj = json_object_new_object();

        ///Variables para agregar como Key y Data
        string jsonKEY = "CONSOLE";
        string jsonData = ui->LineaCMD->toPlainText().toStdString();

        ///Se agrega la informacion en el JSON
        json_object *jstring = json_object_new_string(jsonData.c_str());
        json_object_object_add(jObj,jsonKEY.c_str(), jstring);

        ///Se envia el JSON, se utiliza de parametro solo el jObject
        sendJSON(jObj);*/



        ///TEST
        ///Objeto JSON
        jObj = json_object_new_object();

        ///Variables para agregar como Key y Data
        string jsonKEY = "TEST";
        string jsonData = "1";

        ///Se agrega la informacion en el JSON
        json_object *jstring = json_object_new_string(jsonData.c_str());
        json_object_object_add(jObj,jsonKEY.c_str(), jstring);

        ///Se envia el JSON, se utiliza de parametro solo el jObject
        sendJSON(jObj);


        if (console=="1"){

            ///Cantidad de elementos en el array
            int cantArray = json_object_array_length(tablaFinal);


            ///Para Saber cuales columnas aparecen en la tabla
            int f,n,a,c,t,d;
            for(int ii=0;ii<cantArray;ii++){

                struct json_object *COLUMNA;
                COLUMNA = json_object_array_get_idx(tablaFinal,ii);

                string test = json_object_to_json_string(json_object_array_get_idx(COLUMNA,0));

                if (test=="\"FILE_ID\""){
                    f=1;
                }

                if (test=="\"NOMBRE\""){
                    n=1;
                }

                if (test=="\"AUTOR\""){
                    a=1;
                }

                if (test=="\"CREACION\""){
                    c=1;
                }

                if (test=="\"TAMANO\""){
                    t=1;
                }

                if (test=="\"DESCRIPCION\""){
                    d=1;
                }
            }

            Table(f,n,a,c,t,d,1);

            bool add=true;



            for(int i=0;i<cantArray;i++){

                struct json_object *COLUMNA;
                COLUMNA = json_object_array_get_idx(tablaFinal,i);

                int fila = json_object_array_length(COLUMNA);

                string test = json_object_to_json_string(json_object_array_get_idx(COLUMNA,0));

                for(int j=0; j<(fila-1); j++){



                    if (add==true){
                        cout<<"ADD: "<<endl;
                        ///Inserta un nuevo dato
                        ui->tableWidget->insertRow(j);
                    }

                    string datoF = json_object_to_json_string(json_object_array_get_idx(COLUMNA,j+1));
                    QString dato = QString::fromStdString(datoF);

                    if (test=="\"FILE_ID\""){
                        ui->tableWidget->setItem(j,FileID,new QTableWidgetItem(dato));
                    }

                    if (test=="\"NOMBRE\""){
                        ui->tableWidget->setItem(j,Nombre,new QTableWidgetItem(dato));
                    }

                    if (test=="\"AUTOR\""){
                        ui->tableWidget->setItem(j,Autor,new QTableWidgetItem(dato));
                    }

                    if (test=="\"CREACION\""){
                        ui->tableWidget->setItem(j,Year,new QTableWidgetItem(dato));
                    }

                    if (test=="\"TAMANO\""){
                        ui->tableWidget->setItem(j,Size,new QTableWidgetItem(dato));
                    }

                    if (test=="\"DESCRIPCION\""){
                        ui->tableWidget->setItem(j,Descripcion,new QTableWidgetItem(dato));
                    }

                }

                add=false;

            }
        }

        else{
            QMessageBox::information(this, tr("ERROR"), tr("Comando incorrecto"));
        }

        ui->LineaCMD->setText("");

    }

    else{
        QMessageBox::information(this, tr("ERROR"), tr("Complete Correctamente la linea de comando"));
    }


}



/**
 * Convierte un numero decimal a binario.
 * @param d
 * @return binary
 */
string MainWindow::decimalToBinary(int d) {

    int bin = 0;
    int i = 1;

    while(d > 0) {

        bin += (d % 2) * i;
        d /= 2;
        i *= 10;

    }

    ///Lo convierte a string
    QString bb = QString::number(bin);
    string b = bb.toStdString();

    int len = b.length();

    ///Para hacer que siempre tengan 8 digitos
    if (len != 8) {
        int z = 8 - len;
        while (z > 0) {
            b = "0" + b;
            z--;
        }
    }

    return b;

}

/**
 * Hace una lectura de los bytes de la imagen .bmp y guarda cada uno, en binario.
 * @return bitString
 */
string MainWindow::BMPtoBinaryData(string directory) {

    ///Variables para el recorrido
    int byteValue;
    int index = 0;

    ///Para abrir la imagen
    FILE *file;
    file = fopen(directory.c_str(), "rb");


    if (file != NULL) {

        while (byteValue != EOF) {
            if (index >= 0) {

                byteValue = fgetc(file);

                binaryData += decimalToBinary(byteValue);

            }
            index++;
        }

        fclose(file);

    } else {

        printf("\nFile not found.");

        return "";

    }

    return binaryData;

}

/**
 * Envia el JSON al servidor con datos solicitados.
 * @param jObj
 * @return data, conection
 */

int MainWindow::sendJSON(json_object *jObj){
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
        client.sin_addr.s_addr = inet_addr("192.168.100.4"); //192.168.100.6 //192.168.100.18
        memset(client.sin_zero, '\0', sizeof(client.sin_zero));
    }

    if (::connect(fd, (const struct sockaddr *)&client, sizeof(client)) < 0)
    {
        printf("ERROR connecting to server\n");
        return 1;
    }

    if (strcpy(sendBuff, json_object_to_json_string(jObj)) == NULL) {
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


    struct json_object *NEWGALLERY;
    json_object *parsed_jsonNEWGALLERY = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonNEWGALLERY, "NEWGALLERY", &NEWGALLERY);
    if (json_object_get_string(NEWGALLERY) != 0) {
        NombreGaleria = QString::fromStdString(json_object_get_string(NEWGALLERY));
    }

    struct json_object *NEWIMAGE;
    json_object *parsed_jsonNEWIMAGE = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonNEWIMAGE, "NEWIMAGE", &NEWIMAGE);
    if (json_object_get_string(NEWIMAGE) != 0) {
        newImage = QString::fromStdString(json_object_get_string(NEWIMAGE));
    }

    struct json_object *CONSOLE;
    json_object *parsed_jsonCONSOLE = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonCONSOLE, "CONSOLE", &CONSOLE);
    if (json_object_get_string(CONSOLE) != 0) {
        console="1";
        tablaFinal=CONSOLE;
    }

    struct json_object *TEST;
    json_object *parsed_jsonTEST = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonTEST, "TEST", &TEST);
    if (json_object_get_string(TEST) != 0) {
        QString test;
        test = QString::fromStdString(json_object_get_string(TEST));
    }


    ///Se limpian los Buffers
    memset(recvBuff, 0, MAXDATASIZE);
    memset(sendBuff, 0, MAXDATASIZE);

    ::close(fd);

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
        client.sin_addr.s_addr = inet_addr("192.168.100.18"); //192.168.100.6
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


    struct json_object *NEWGALLERY;
    json_object *parsed_jsonNEWGALLERY = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonNEWGALLERY, "NEWGALLERY", &NEWGALLERY);
    if (json_object_get_string(NEWGALLERY) != 0) {
        NombreGaleria = QString::fromStdString(json_object_get_string(NEWGALLERY));
    }



    ///Se limpian los Buffers
    memset(recvBuff, 0, MAXDATASIZE);
    memset(sendBuff, 0, MAXDATASIZE);

    ::close(fd);

}


