#ifndef PERSON_H
#define PERSON_H

#pragma once
#include <QString>
#include <QStringList>
#include <QVector>

class Person {
public:
    // Person();
    int id;
    QString firstName;
    QStringList middleNames;
    QString lastName;
    QString maidenName;

    QString birthDate;
    QString deathDate;
    QString birthPlace;
    QString deathPlace;
    QString burialPlace;
    QString occupation;
    QString education;
    QString baptism;
    QString notesRichText;

    QString photoPath;
    QStringList galleryPhotos;

    int fatherId = -1;
    int motherId = -1;
    QVector<int> childrenIds;
};

#endif // PERSON_H
