#include "persondialog.h"
#include "ui_persondialog.h"

PersonDialog::PersonDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PersonDialog)
{
    ui->setupUi(this);
}

PersonDialog::~PersonDialog()
{
    delete ui;
}

Person PersonDialog::getPerson() const
{
    Person p;
    // Pobieramy dane z pól formularza i zapisujemy do obiektu Person
    p.setFirstName(ui->firstNameEdit->text());
    p.setLastName(ui->lastNameEdit->text());
    p.setMaidenName(ui->maidenNameEdit->text());
    p.setBirthDate(ui->birthDateEdit->date());
    p.setBirthPlace(ui->placeOfBirthEdit->text());
    p.setDeathDate(ui->deathDateEdit->date());
    p.setDeathPlace(ui->placeOfDeathEdit->text());
    p.setPhone(ui->phoneNumberEdit->text());
    p.setOccupation(ui->occupationEdit->text());
    p.setNotes(ui->notesEdit->toPlainText());

    return p;
}

void PersonDialog::setPerson(const Person &p)
{
    ui->firstNameEdit->setText(p.firstName());
    ui->lastNameEdit->setText(p.lastName());
    ui->maidenNameEdit->setText(p.maidenName());
    ui->birthDateEdit->setDate(p.birthDate());
    ui->placeOfBirthEdit->setText(p.birthPlace());
    ui->deathDateEdit->setDate(p.deathDate().isValid() ? p.deathDate() : QDate::currentDate());
    ui->placeOfDeathEdit->setText(p.deathPlace());
    ui->phoneNumberEdit->setText(p.phone());
    ui->occupationEdit->setText(p.occupation());
    ui->notesEdit->setPlainText(p.notes());
}
