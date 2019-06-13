#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QFileDialog>

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
    fil=13;

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
        //ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        //int fila = ui->tableWidget->rowCount()-1;
        //ui->tableWidget->setItem(fila,Nombre,new QTableWidgetItem("Edgar Gonzalez"));
        //ui->tableWidget->setItem(fila,Link,new QTableWidgetItem("  >  "));
    }


}

void MainWindow::on_BotonImg_clicked()
{

    if (ui->comboBoxGalerias!=0){

        ///Busca la imagen
        QString imagen = QFileDialog::getOpenFileName(this, "Imagen - Open file", "", "Imagen Files (*.bmp);;All Files (*.*)");

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

        ///Direccion de la imagen seleccionada
        string DireccionImagen = imagen.toStdString();

        ///Se crea el BinaryData
        BMPtoBinaryData(DireccionImagen);
        //cout<<binaryData<<endl;

        int p;

        for (int i=0; i<DireccionImagen.length();i++){
            if (DireccionImagen[i] == '/'){
                p=i;
            }
        }

        string imagenDeGal = DireccionImagen.substr(p+1,DireccionImagen.length());


        for (int i=0; i<ui->listWidgetGaleria->count();i++){

           if ((ui->listWidgetGaleria->item(i)->text())==ui->comboBoxGalerias->currentText()){
                ui->listWidgetGaleria->insertItem(i+1,"       "+QString::fromStdString(imagenDeGal));

                i=ui->listWidgetGaleria->count();
            }

        }

        ///Agregra a la listViewWig
        /*for (int i=1;i<=3;i++){

            ui->listWidgetGaleria->addItem("    Galeria "+QString::number(i));

            for (int j=1;j<=10;j++){
                ui->listWidgetGaleria->addItem("            Imagen "+QString::number(j));
            }

        }*/
    }

}

void MainWindow::on_BotonGal_clicked()
{
    if (ui->galeria->text()!=0){
        ui->listWidgetGaleria->addItem("    "+ui->galeria->text());
        ui->comboBoxGalerias->addItem("    "+ui->galeria->text());
    }
    ui->galeria->setText("");
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

    //cout << b << endl;

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

