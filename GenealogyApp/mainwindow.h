#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "person.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Wektor przechowujący wszystkie osoby w pamięci
    QVector<Person> m_people;

    // Licznik następnego ID (inkrementowany przy każdej nowej osobie).
    // Uwaga: po wczytaniu JSON ustawimy go na max(id)+1, żeby nie było kolizji.
    int m_nextId = 1;

    // Funkcja pomocnicza do odświeżania widoku listy
    void refreshPeopleList();

    // (opcjonalnie) funkcja do aktualizacji m_nextId po wczytaniu JSON
    void recomputeNextId();

};
#endif // MAINWINDOW_H
