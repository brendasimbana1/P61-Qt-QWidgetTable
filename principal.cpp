#include "principal.h"
#include "ui_principal.h"


#include "QDebug" //para probar

Principal::Principal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    setWindowTitle("Agenda telefónica"); //título de la ventana
    // Configurar la tabla
    ui->tblLista->setColumnCount(4);
    QStringList titulo;
    titulo << "Nombre" << "Apellido" << "Teléfono" << "E-mail"; //cabeceras de la lista
    ui->tblLista->setHorizontalHeaderLabels(titulo); //establecer las cabecerar
    // Leer desde el archivo
    cargarContactos();

}

Principal::~Principal()
{
    delete ui;
}


void Principal::on_btnAgregar_clicked()
{
    // Crear y mostrar el dialogo
    PersonaDialog pd(this);//this: este es el padre del dialogo
    pd.setWindowTitle("Agregar contacto"); //establece el título de la ventana
    // Abrir la ventana y evaluar respuesta
    int res = pd.exec(); //se abre y espera un retorno
    if (res == QDialog::Rejected){ //si se cancela, sale del método
        return;
    }
    // Recuperar el objeto del cuadro de dialogo
    Persona *p = pd.persona();
    /*QString nombre = pd.persona()->nombre(); //Obtiene información de persona dialog
    QString apellido = pd.persona()->apellido();
    QString telefono = pd.persona()->telefono();
    QString email = pd.persona()->email();*/
    //Agregar a la tabla
    int fila = ui->tblLista->rowCount();
    ui->tblLista->insertRow(fila);
    ui->tblLista->setItem(fila, NOMBRE, new QTableWidgetItem(p->nombre()));
    ui->tblLista->setItem(fila, APELLIDO, new QTableWidgetItem(p->apellido()));
    ui->tblLista->setItem(fila, TELEFONO, new QTableWidgetItem(p->telefono()));
    ui->tblLista->setItem(fila, EMAIL, new QTableWidgetItem(p->email()));

}


void Principal::on_btnGuardar_clicked()
{
    // Verificar que exista datos para guardar
    int filas = ui->tblLista->rowCount();
    if (filas == 0){
        QMessageBox::warning(this,"Guardar contactos","Agenda sin datos para guardar");
        return;
    }
    // Abrir el archivo y guardar
    QFile archivo(ARCHIVO);
    if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream salida(&archivo);
        for (int i=0; i<filas; i++) {
            QTableWidgetItem *nombre = ui->tblLista->item(i, NOMBRE); /*QTableWidgetItem *QTableWidget
                                                                        ::item(int row, int column) const*/
            QTableWidgetItem *apellido = ui->tblLista->item(i, APELLIDO);
            QTableWidgetItem *telefono = ui->tblLista->item(i, TELEFONO);
            QTableWidgetItem *email = ui->tblLista->item(i, EMAIL);
            salida << nombre->text() << ";" << apellido->text() << ";";
            salida << telefono->text() << ";" << email->text() << "\n";
        }
        archivo.close();
        QMessageBox::information(this,"Guardar contactos","Contactos guardados con éxito");
    }else{
        QMessageBox::critical(this,"Guardar contactos", "No se puede escribir sobre " + ARCHIVO); //ERROR
    }

}

void Principal::cargarContactos()
{
    // Verificar si el archivo existe
    QFile archivo(ARCHIVO);
    if (!archivo.exists()) //si el archivo existe
        return;

    // cargar datos
    if (archivo.open(QFile::ReadOnly)) {
        QTextStream entrada(&archivo);
        int fila;
        while(!entrada.atEnd()){ //lee hasta el final
            QString linea = entrada.readLine(); //lee la línea
            QStringList datos = linea.split(";"); //separa mediante ";", devuelve una lista de Qstring
            //Agregar a la tabla
            fila = ui->tblLista->rowCount(); //número de filas que tiene
            ui->tblLista->insertRow(fila); //inserta
            ui->tblLista->setItem(fila, NOMBRE, new QTableWidgetItem(datos[NOMBRE]));/*recibe un obj QTableWidget
                                                                                    segun la información de datos*/
            ui->tblLista->setItem(fila, APELLIDO, new QTableWidgetItem(datos[APELLIDO]));
            ui->tblLista->setItem(fila, TELEFONO, new QTableWidgetItem(datos[TELEFONO]));
            ui->tblLista->setItem(fila, EMAIL, new QTableWidgetItem(datos[EMAIL]));
        }
        archivo.close();
    }
}

