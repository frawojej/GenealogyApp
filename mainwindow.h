#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>
#include "familytree.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FamilyTree tree;
    QString parseBirthDate();

private slots:
    void onAddPersonClicked();  // <- DODAJ TO
    void onSaveClicked();
    void onLoadClicked();
    void on_managePeopleButton_clicked();
};

#endif // MAINWINDOW_H
