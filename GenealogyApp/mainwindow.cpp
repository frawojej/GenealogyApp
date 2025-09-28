#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "person.h"
#include "persondialog.h"
#include <QDebug>
#include <QPushButton>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFileDialog>
#include <QMessageBox>
#include <QListWidget>

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

            refreshPeopleList(); // odśwież widok listy
        }
    });

    // Zapis
    connect(ui->saveJsonButton, &QPushButton::clicked, this, [this]() {
        QString fileName = QFileDialog::getSaveFileName(this, "Zapisz plik JSON", "", "JSON (*.json)");
        if (fileName.isEmpty()) return;

        QJsonArray arr;
        for (const Person &p : m_people) {
            arr.append(p.toJson());
        }

        QJsonDocument doc(arr);
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(doc.toJson());
            file.close();
        } else {
            QMessageBox::warning(this, "Błąd", "Nie udało się zapisać pliku");
        }
    });

    // Odczyt
    connect(ui->loadJsonButton, &QPushButton::clicked, this, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, "Wczytaj plik JSON", "", "JSON (*.json)");
        if (fileName.isEmpty()) return;

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "Błąd", "Nie udało się otworzyć pliku");
            return;
        }

        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (!doc.isArray()) {
            QMessageBox::warning(this, "Błąd", "Niepoprawny format JSON");
            return;
        }

        m_people.clear();
        for (const QJsonValue &val : doc.array()) {
            if (val.isObject()) {
                m_people.append(Person::fromJson(val.toObject()));
            }
        }
        qDebug() << "Wczytano osób:" << m_people.size();

        refreshPeopleList(); // odśwież widok listy
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshPeopleList()
{
    // Czyścimy listę w GUI
    ui->peopleListWidget->clear();

    // Dodajemy każdą osobę z wektora
    for (const Person &p : m_people) {
        QString display = p.firstName() + " " + p.lastName();
        ui->peopleListWidget->addItem(display);
    }
}
