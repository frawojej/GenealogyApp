#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "person.h"
#include "persondialog.h"
#include <QDebug>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->addPersonButton, &QPushButton::clicked, this, [this]() {
        PersonDialog dlg(this);
        if (dlg.exec() == QDialog::Accepted) {
            Person p = dlg.getPerson();
            m_people.append(p);

            qDebug() << "Dodano osobę:" << p.firstName() << p.lastName();
            qDebug() << "Łączna liczba osób:" << m_people.size();
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
