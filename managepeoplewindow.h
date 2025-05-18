#ifndef MANAGEPEOPLEWINDOW_H
#define MANAGEPEOPLEWINDOW_H

#include "familytree.h"
#include <QDialog>

namespace Ui {
    class ManagePeopleWindow;
}

class ManagePeopleWindow : public QDialog {
    Q_OBJECT

public:
    explicit ManagePeopleWindow(FamilyTree* tree, QWidget *parent = nullptr);
    ~ManagePeopleWindow();

private:
    Ui::ManagePeopleWindow *ui;
    FamilyTree* tree;
    QString parseBirthDate();

private slots:
    void on_addPersonButton_clicked();
    void on_saveButton_clicked();
    void on_loadButton_clicked();
};

#endif // MANAGEPEOPLEWINDOW_H
