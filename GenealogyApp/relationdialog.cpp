#include "relationdialog.h"
#include "ui_relationdialog.h"

RelationDialog::RelationDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RelationDialog)
{
    ui->setupUi(this);

    // Wypełniamy typy relacji
    ui->relationTypeCombo->addItem("Rodzic");
    ui->relationTypeCombo->addItem("Dziecko");
    ui->relationTypeCombo->addItem("Małżonek");
}

RelationDialog::~RelationDialog()
{
    delete ui;
}

void RelationDialog::setPeopleList(const QVector<Person> &people, int excludeId)
{
    m_people = people;
    ui->personCombo->clear();

    for (const Person &p : m_people) {
        if (p.id() == excludeId) continue; // nie można wybrać samego siebie
        QString display = QString("%1 %2 (ID: %3)")
                              .arg(p.firstName())
                              .arg(p.lastName())
                              .arg(p.id());
        ui->personCombo->addItem(display, p.id());
    }
}

QString RelationDialog::relationType() const
{
    return ui->relationTypeCombo->currentText();
}

int RelationDialog::selectedPersonId() const
{
    return ui->personCombo->currentData().toInt();
}
