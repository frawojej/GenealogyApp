#include "managepeoplewindow.h"
#include "ui_managepeoplewindow.h"
#include "person.h"
#include "filemanager.h"

#include <QMessageBox>
#include <QFileDialog>


QString ManagePeopleWindow::parseBirthDate() {
    QString dayStr = ui->birthDayEdit_2->text().trimmed();
    QString monthStr = ui->birthMonthEdit_2->text().trimmed().toLower();
    QString yearStr = ui->birthYearEdit_2->text().trimmed();

    // Walidacja roku
    bool yearOk;
    int year = yearStr.toInt(&yearOk);
    if (!yearOk || year < 1000 || year > 9999)
        return "";

    // Walidacja dnia
    bool dayOk;
    int day = dayStr.toInt(&dayOk);
    if (!dayOk || day < 1 || day > 31)
        return "";

    // Zamiana miesiąca tekstowego na liczbę
    QMap<QString, int> monthMap = {
        {"01", 1}, {"1", 1}, {"jan", 1}, {"sty", 1},
        {"02", 2}, {"2", 2}, {"feb", 2}, {"lut", 2},
        {"03", 3}, {"3", 3}, {"mar", 3},
        {"04", 4}, {"4", 4}, {"apr", 4}, {"kwi", 4},
        {"05", 5}, {"5", 5}, {"may", 5}, {"maj", 5},
        {"06", 6}, {"6", 6}, {"jun", 6}, {"cze", 6},
        {"07", 7}, {"7", 7}, {"jul", 7}, {"lip", 7},
        {"08", 8}, {"8", 8}, {"aug", 8}, {"sie", 8},
        {"09", 9}, {"9", 9}, {"sep", 9}, {"wrz", 9},
        {"10", 10}, {"oct", 10}, {"paz", 10},
        {"11", 11}, {"nov", 11}, {"lis", 11},
        {"12", 12}, {"dec", 12}, {"gru", 12}
    };

    if (!monthMap.contains(monthStr))
        return "";

    int month = monthMap.value(monthStr);

    // Dni w miesiącu
    QMap<int, int> daysInMonth = {
        {1, 31}, {2, 28}, {3, 31}, {4, 30},
        {5, 31}, {6, 30}, {7, 31}, {8, 31},
        {9, 30}, {10, 31}, {11, 30}, {12, 31}
    };

    // Rok przestępny
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
        daysInMonth[2] = 29;

    if (day > daysInMonth[month])
        return "";

    return QString("%1-%2-%3")
        .arg(year, 4, 10, QChar('0'))
        .arg(month, 2, 10, QChar('0'))
        .arg(day, 2, 10, QChar('0'));
}

ManagePeopleWindow::ManagePeopleWindow(FamilyTree* tree, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ManagePeopleWindow)
    , tree(tree)
{
    ui->setupUi(this);
}

ManagePeopleWindow::~ManagePeopleWindow()
{
    delete ui;
}

void ManagePeopleWindow::on_addPersonButton_clicked() {
    Person p;
    p.firstName = ui->firstNameEdit_2->text();
    p.lastName = ui->lastNameEdit_2->text();
    p.birthDate = parseBirthDate();

    if (p.birthDate.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Data urodzenia jest niepoprawna.");
        return;
    }

    p.birthPlace = ui->birthPlaceEdit_2->text();
    p.notesRichText = ui->notesEdit_2->toHtml();

    tree->addPerson(p);

    QMessageBox::information(this, "Dodano", "Osoba została dodana.");
}

void ManagePeopleWindow::on_saveButton_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Zapisz plik", "", "JSON (*.json)");
    if (fileName.isEmpty()) return;

    if (FileManager::saveToJson(fileName, *tree)) {
        QMessageBox::information(this, "Sukces", "Zapisano do pliku.");
    } else {
        QMessageBox::warning(this, "Błąd", "Nie udało się zapisać.");
    }
}

void ManagePeopleWindow::on_loadButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Wczytaj plik", "", "JSON (*.json)");
    if (fileName.isEmpty()) return;

    if (FileManager::loadFromJson(fileName, *tree)) {
        QMessageBox::information(this, "Sukces", "Wczytano dane.");
    } else {
        QMessageBox::warning(this, "Błąd", "Nie udało się wczytać.");
    }
}
