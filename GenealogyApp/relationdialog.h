#ifndef RELATIONDIALOG_H
#define RELATIONDIALOG_H

#include <QDialog>
#include "person.h"

namespace Ui {
class RelationDialog;
}

class RelationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RelationDialog(QWidget *parent = nullptr);
    ~RelationDialog();

    // Ustaw listę osób do wyboru (np. z MainWindow)
    void setPeopleList(const QVector<Person> &people, int excludeId);

    // Zwraca wybrany typ relacji
    QString relationType() const;

    // Zwraca ID wybranej osoby
    int selectedPersonId() const;

private:
    Ui::RelationDialog *ui;
    QVector<Person> m_people;
};

#endif // RELATIONDIALOG_H
