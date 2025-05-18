/********************************************************************************
** Form generated from reading UI file 'managepeoplewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGEPEOPLEWINDOW_H
#define UI_MANAGEPEOPLEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManagePeopleWindow
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QFormLayout *formLayout_2;
    QLabel *label_9;
    QLineEdit *firstNameEdit_2;
    QLabel *label_10;
    QLineEdit *lastNameEdit_2;
    QGridLayout *gridLayout_2;
    QLineEdit *birthYearEdit_2;
    QLineEdit *birthMonthEdit_2;
    QLineEdit *birthDayEdit_2;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLineEdit *birthPlaceEdit_2;
    QLabel *label_15;
    QTextEdit *notesEdit_2;
    QLabel *label_16;
    QPushButton *addPersonButton;
    QPushButton *loadButton;
    QPushButton *saveButton;

    void setupUi(QDialog *ManagePeopleWindow)
    {
        if (ManagePeopleWindow->objectName().isEmpty())
            ManagePeopleWindow->setObjectName("ManagePeopleWindow");
        ManagePeopleWindow->resize(966, 593);
        buttonBox = new QDialogButtonBox(ManagePeopleWindow);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(570, 540, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        layoutWidget = new QWidget(ManagePeopleWindow);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(70, 61, 419, 338));
        formLayout_2 = new QFormLayout(layoutWidget);
        formLayout_2->setObjectName("formLayout_2");
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName("label_9");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::LabelRole, label_9);

        firstNameEdit_2 = new QLineEdit(layoutWidget);
        firstNameEdit_2->setObjectName("firstNameEdit_2");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::FieldRole, firstNameEdit_2);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName("label_10");

        formLayout_2->setWidget(1, QFormLayout::ItemRole::LabelRole, label_10);

        lastNameEdit_2 = new QLineEdit(layoutWidget);
        lastNameEdit_2->setObjectName("lastNameEdit_2");

        formLayout_2->setWidget(1, QFormLayout::ItemRole::FieldRole, lastNameEdit_2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        birthYearEdit_2 = new QLineEdit(layoutWidget);
        birthYearEdit_2->setObjectName("birthYearEdit_2");

        gridLayout_2->addWidget(birthYearEdit_2, 1, 2, 1, 1);

        birthMonthEdit_2 = new QLineEdit(layoutWidget);
        birthMonthEdit_2->setObjectName("birthMonthEdit_2");

        gridLayout_2->addWidget(birthMonthEdit_2, 1, 1, 1, 1);

        birthDayEdit_2 = new QLineEdit(layoutWidget);
        birthDayEdit_2->setObjectName("birthDayEdit_2");

        gridLayout_2->addWidget(birthDayEdit_2, 1, 0, 1, 1);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName("label_11");

        gridLayout_2->addWidget(label_11, 0, 0, 1, 1);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName("label_12");

        gridLayout_2->addWidget(label_12, 0, 1, 1, 1);

        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName("label_13");

        gridLayout_2->addWidget(label_13, 0, 2, 1, 1);


        formLayout_2->setLayout(2, QFormLayout::ItemRole::FieldRole, gridLayout_2);

        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName("label_14");

        formLayout_2->setWidget(3, QFormLayout::ItemRole::LabelRole, label_14);

        birthPlaceEdit_2 = new QLineEdit(layoutWidget);
        birthPlaceEdit_2->setObjectName("birthPlaceEdit_2");

        formLayout_2->setWidget(3, QFormLayout::ItemRole::FieldRole, birthPlaceEdit_2);

        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName("label_15");

        formLayout_2->setWidget(4, QFormLayout::ItemRole::LabelRole, label_15);

        notesEdit_2 = new QTextEdit(layoutWidget);
        notesEdit_2->setObjectName("notesEdit_2");

        formLayout_2->setWidget(4, QFormLayout::ItemRole::FieldRole, notesEdit_2);

        label_16 = new QLabel(layoutWidget);
        label_16->setObjectName("label_16");

        formLayout_2->setWidget(2, QFormLayout::ItemRole::LabelRole, label_16);

        addPersonButton = new QPushButton(ManagePeopleWindow);
        addPersonButton->setObjectName("addPersonButton");
        addPersonButton->setGeometry(QRect(240, 400, 111, 24));
        loadButton = new QPushButton(ManagePeopleWindow);
        loadButton->setObjectName("loadButton");
        loadButton->setGeometry(QRect(540, 90, 111, 24));
        saveButton = new QPushButton(ManagePeopleWindow);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(540, 60, 111, 24));

        retranslateUi(ManagePeopleWindow);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ManagePeopleWindow, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ManagePeopleWindow, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ManagePeopleWindow);
    } // setupUi

    void retranslateUi(QDialog *ManagePeopleWindow)
    {
        ManagePeopleWindow->setWindowTitle(QCoreApplication::translate("ManagePeopleWindow", "Dialog", nullptr));
        label_9->setText(QCoreApplication::translate("ManagePeopleWindow", "First name:", nullptr));
        label_10->setText(QCoreApplication::translate("ManagePeopleWindow", "Last name:", nullptr));
        label_11->setText(QCoreApplication::translate("ManagePeopleWindow", "Day:", nullptr));
        label_12->setText(QCoreApplication::translate("ManagePeopleWindow", "Month:", nullptr));
        label_13->setText(QCoreApplication::translate("ManagePeopleWindow", "Year:", nullptr));
        label_14->setText(QCoreApplication::translate("ManagePeopleWindow", "Place of birth:", nullptr));
        label_15->setText(QCoreApplication::translate("ManagePeopleWindow", "Notes:", nullptr));
        label_16->setText(QCoreApplication::translate("ManagePeopleWindow", "Date of birth:", nullptr));
        addPersonButton->setText(QCoreApplication::translate("ManagePeopleWindow", "Add the person", nullptr));
        loadButton->setText(QCoreApplication::translate("ManagePeopleWindow", "Load", nullptr));
        saveButton->setText(QCoreApplication::translate("ManagePeopleWindow", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManagePeopleWindow: public Ui_ManagePeopleWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGEPEOPLEWINDOW_H
