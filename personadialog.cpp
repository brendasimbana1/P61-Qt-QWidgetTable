#include "personadialog.h"
#include "ui_personadialog.h"

PersonaDialog::PersonaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonaDialog)
{
    ui->setupUi(this);
}

PersonaDialog::~PersonaDialog()
{
    delete ui;
}

/*QString PersonaDialog::nombre()
{
    return ui->inNombre->text(); //devuelve la información del LineEdit
}

QString PersonaDialog::apellido()
{
    return ui->inApellido->text();
}

QString PersonaDialog::telefono()
{
    return ui->inTelefono->text();
}

QString PersonaDialog::email()
{
    return ui->inEmail->text();
}*/

void PersonaDialog::on_buttonBox_accepted()
{
    /*REFACTORIZACIÓN: Se cambia el código para mejorar la funcionalidad dentro de el, no cambia sus funciones
    externas*/
    QString nombre =  ui->inNombre->text();
    QString apellido =  ui->inApellido->text();
    QString telefono =  ui->inTelefono->text();
    /*if (!telefono.contains("1", Qt::CaseInsensitive)){
        QMessageBox::warning(this, "Adventencia", "El campo del telefono debe contener solo numeros");
        return;
    }*/
    QString email =  ui->inEmail->text();

    if (nombre.isEmpty()|| apellido.isEmpty() || telefono.isEmpty() || email.isEmpty()){
        QMessageBox::warning(this, "Adventencia", "Todos los campos deben estar llenos");
        return;
    }
    this->m_persona = new Persona(nombre, apellido, telefono, email);
    accept();
}


void PersonaDialog::on_buttonBox_rejected()
{
    reject();
}

Persona *PersonaDialog::persona() const
{
    return m_persona;
}

