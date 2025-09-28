#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "person.h"
#include "persondialog.h"
#include "relationdialog.h"

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

    // Dodawanie osoby: nadajemy nowe ID przed dodaniem do wektora
    connect(ui->addPersonButton, &QPushButton::clicked, this, [this]() {
        PersonDialog dlg(this);
        if (dlg.exec() == QDialog::Accepted) {
            Person p = dlg.getPerson();

            // --- Nadanie unikalnego ID ---
            // Zabezpieczenie: jeśli osoba ma już ustawione ID (np. z edycji), nadpisujemy nowym.
            // W normalnym flow z PersonDialog ID jest -1, więc tutaj ustawiamy świeże ID.
            p.setId(m_nextId++);

            m_people.append(p);
            refreshPeopleList();

            qDebug() << "Dodano osobę:" << p.firstName() << p.lastName() << "ID:" << p.id();
            qDebug() << "Łączna liczba osób:" << m_people.size();
        }
    });

    // Obsługa przycisku "Dodaj relację"
    connect(ui->addRelationButton, &QPushButton::clicked, this, [this]() {
        int row = ui->peopleListWidget->currentRow();
        if (row < 0 || row >= m_people.size()) {
            QMessageBox::warning(this, "Błąd", "Nie wybrano osoby bazowej");
            return;
        }

        Person &base = m_people[row];

        RelationDialog dlg(this);
        dlg.setPeopleList(m_people, base.id());

        if (dlg.exec() == QDialog::Accepted) {
            QString type = dlg.relationType();
            int otherId = dlg.selectedPersonId();

            // Znajdź osobę B po ID
            Person *other = nullptr;
            for (Person &p : m_people) {
                if (p.id() == otherId) {
                    other = &p;
                    break;
                }
            }
            if (!other) return;

            QString baseName = QString("%1 %2, ur. %3")
                                   .arg(base.firstName())
                                   .arg(base.lastName())
                                   .arg(base.birthDate().isValid() ? base.birthDate().toString("dd.MM.yyyy") : "?");

            QString otherName = QString("%1 %2, ur. %3")
                                    .arg(other->firstName())
                                    .arg(other->lastName())
                                    .arg(other->birthDate().isValid() ? other->birthDate().toString("dd.MM.yyyy") : "?");

            QString relationText;

            // Aktualizacja relacji
            if (type == "Rodzic") {
                relationText = QString("%1 jest rodzicem %2").arg(otherName, baseName);
            } else if (type == "Dziecko") {
                relationText = QString("%1 jest dzieckiem %2").arg(otherName, baseName);
            } else if (type == "Małżonek") {
                relationText = QString("%1 jest małżonkiem %2").arg(baseName, otherName);
            }

            QMessageBox::information(this, "Relacja dodana", relationText);
        }
    });

    // Obsługa podwójnego kliknięcia na liście osób
    connect(ui->peopleListWidget, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem *item) {
        int row = ui->peopleListWidget->row(item);
        if (row >= 0 && row < m_people.size()) {
            const Person &p = m_people[row];

            QString details;
            details += "Imię: " + p.firstName() + "\n";
            details += "Nazwisko: " + p.lastName() + "\n";
            details += "Nazwisko panieńskie: " + p.maidenName() + "\n";
            details += "Data urodzenia: " + p.birthDate().toString("dd.MM.yyyy") + "\n";
            details += "Miejsce urodzenia: " + p.birthPlace() + "\n";
            details += "Data śmierci: " + (p.deathDate().isValid() ? p.deathDate().toString("dd.MM.yyyy") : "-") + "\n";
            details += "Miejsce śmierci: " + p.deathPlace() + "\n";
            details += "Telefon: " + p.phone() + "\n";
            details += "Zawód: " + p.occupation() + "\n";
            details += "Notatki:\n" + p.notes();

            // Rodzice
            if (!p.parentIds().isEmpty()) {
                details += "\nRodzice:\n";
                for (int pid : p.parentIds()) {
                    for (const Person &cand : m_people) {
                        if (cand.id() == pid) {
                            details += " - " + cand.firstName() + " " + cand.lastName()
                            + ", ur. " + (cand.birthDate().isValid() ? cand.birthDate().toString("dd.MM.yyyy") : "?") + "\n";
                        }
                    }
                }
            }

            // Dzieci
            if (!p.childrenIds().isEmpty()) {
                details += "\nDzieci:\n";
                for (int cid : p.childrenIds()) {
                    for (const Person &cand : m_people) {
                        if (cand.id() == cid) {
                            details += " - " + cand.firstName() + " " + cand.lastName()
                            + ", ur. " + (cand.birthDate().isValid() ? cand.birthDate().toString("dd.MM.yyyy") : "?") + "\n";
                        }
                    }
                }
            }

            // Małżonek
            if (p.spouseId() != -1) {
                for (const Person &cand : m_people) {
                    if (cand.id() == p.spouseId()) {
                        details += "\nMałżonek:\n";
                        details += " - " + cand.firstName() + " " + cand.lastName()
                                   + ", ur. " + (cand.birthDate().isValid() ? cand.birthDate().toString("dd.MM.yyyy") : "?") + "\n";
                    }
                }
            }

            QMessageBox::information(this, "Szczegóły osoby", details);
        }
    });

    connect(ui->editPersonButton, &QPushButton::clicked, this, [this]() {
        int row = ui->peopleListWidget->currentRow();
        if (row < 0 || row >= m_people.size()) {
            QMessageBox::warning(this, "Błąd", "Nie wybrano osoby do edycji");
            return;
        }

        Person &p = m_people[row];
        PersonDialog dlg(this);
        dlg.setPerson(p); // wypełnij formularz istniejącymi danymi

        if (dlg.exec() == QDialog::Accepted) {
            p = dlg.getPerson(); // nadpisz dane osoby
            refreshPeopleList(); // odśwież listę
        }
    });

    // Obsługa przycisku "Usuń osobę"
    connect(ui->deletePersonButton, &QPushButton::clicked, this, [this]() {
        // Pobieramy indeks zaznaczonego wiersza w QListWidget
        int row = ui->peopleListWidget->currentRow();

        // Jeśli nic nie zaznaczono, pokaż komunikat i wyjdź
        if (row < 0 || row >= m_people.size()) {
            QMessageBox::warning(this, "Błąd", "Nie wybrano osoby do usunięcia");
            return;
        }

        // Pobieramy dane osoby, żeby pokazać w komunikacie
        const Person &p = m_people[row];
        QString name = p.firstName() + " " + p.lastName();

        // Pytamy użytkownika, czy na pewno chce usunąć
        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "Potwierdzenie",
            "Czy na pewno chcesz usunąć osobę:\n" + name + "?",
            QMessageBox::Yes | QMessageBox::No
            );

        // Jeśli użytkownik kliknął "Tak"
        if (reply == QMessageBox::Yes) {
            // Usuwamy osobę z wektora
            m_people.removeAt(row);

            // Odświeżamy widok listy
            refreshPeopleList();

            // Informacja w konsoli (debug)
            qDebug() << "Usunięto osobę:" << name;
            qDebug() << "Łączna liczba osób:" << m_people.size();
        }
    });

    // Zapis JSON
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

    // Odczyt JSON
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

        // --- Ustaw licznik ID tak, żeby nowe osoby nie kolidowały z istniejącymi ---
        recomputeNextId();

        qDebug() << "Wczytano osób:" << m_people.size();

        refreshPeopleList(); // odśwież widok listy
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

// --- Odświeżanie listy ---
void MainWindow::refreshPeopleList()
{
    // Czyścimy listę w GUI
    ui->peopleListWidget->clear();

    // Dodajemy każdą osobę z wektora
    for (const Person &p : m_people) {
        // Wyświetlamy imię, nazwisko, datę urodzenia i (opcjonalnie) ID, ułatwia debugowanie i relacje
        QString display = QString("%1 %2, ur. %3 (ID: %4)")
                              .arg(p.firstName())
                              .arg(p.lastName())
                              .arg(p.birthDate().isValid() ? p.birthDate().toString("dd.MM.yyyy") : "?")
                              .arg(p.id());
        ui->peopleListWidget->addItem(display);
    }
}

// --- Przeliczenie m_nextId na podstawie wczytanych danych ---
// Uwaga: dzięki temu unikamy kolizji ID po wczytaniu JSON.
void MainWindow::recomputeNextId()
{
    int maxId = 0;
    for (Person &p : m_people) {
        if (p.id() < 0) {
            // jeśli osoba nie miała ID, nadajemy nowe
            p.setId(m_nextId++);
        }
        if (p.id() > maxId) maxId = p.id();
    }
    m_nextId = maxId + 1;
}
