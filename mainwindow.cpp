#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "person.h"
#include "familytree.h"
#include "managepeoplewindow.h"

#include <QMessageBox>

#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QIODevice>

void MainWindow::on_managePeopleButton_clicked() {
    ManagePeopleWindow *dialog = new ManagePeopleWindow(&tree, this);
    dialog->show();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddPersonClicked() {
    //
}

void MainWindow::onSaveClicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Zapisz dane", "", "JSON Files (*.json)");
    if (fileName.isEmpty())
        return;

    QJsonArray peopleArray;
    for (const Person &p : tree.getPeople()) {
        QJsonObject obj;
        obj["firstName"] = p.firstName;
        obj["lastName"] = p.lastName;
        obj["birthDate"] = p.birthDate;
        obj["birthPlace"] = p.birthPlace;
        obj["notesRichText"] = p.notesRichText;
        peopleArray.append(obj);
    }

    QJsonDocument doc(peopleArray);
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
        QMessageBox::information(this, "Zapisano", "Dane zapisano do pliku.");
    } else {
        QMessageBox::warning(this, "Błąd", "Nie udało się zapisać pliku.");
    }
}

void MainWindow::onLoadClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Wczytaj dane", "", "JSON Files (*.json)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Błąd", "Nie udało się otworzyć pliku.");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        QMessageBox::warning(this, "Błąd", "Niepoprawny format pliku.");
        return;
    }

    tree.clear(); // jeśli masz taką funkcję – wyczyść stare dane
    QJsonArray arr = doc.array();
    for (const QJsonValue &val : arr) {
        QJsonObject obj = val.toObject();
        Person p;
        p.firstName = obj["firstName"].toString();
        p.lastName = obj["lastName"].toString();
        p.birthDate = obj["birthDate"].toString();
        p.birthPlace = obj["birthPlace"].toString();
        p.notesRichText = obj["notesRichText"].toString();
        tree.addPerson(p);
    }

    QMessageBox::information(this, "Wczytano", "Dane zostały wczytane.");
}

