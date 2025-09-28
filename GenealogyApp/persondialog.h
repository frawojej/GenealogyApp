#ifndef PERSONDIALOG_H
#define PERSONDIALOG_H

#include <QDialog>
#include "person.h"

namespace Ui {
class PersonDialog;
}

class PersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PersonDialog(QWidget *parent = nullptr);
    ~PersonDialog();

    // Funkcja, która zwróci obiekt Person na podstawie pól formularza
    Person getPerson() const;
    void setPerson(const Person &p);

private:
    Ui::PersonDialog *ui;
};

#endif // PERSONDIALOG_H
