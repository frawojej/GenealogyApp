#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "person.h"
#include <QDebug>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Po kliknięciu przycisku dodajemy przykładową osobę
    connect(ui->addPersonButton, &QPushButton::clicked, this, [this]() {
        Person p("Jan", "Kowalski", QDate(1990, 5, 12), "Rybnik");
        p.setOccupation("Inżynier");
        p.setPhone("123-456-789");

        m_people.append(p);

        qDebug() << "Dodano osobę:" << p.firstName() << p.lastName();
        qDebug() << "Łączna liczba osób:" << m_people.size();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
