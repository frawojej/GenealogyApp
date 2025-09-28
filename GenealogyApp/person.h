#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDate>
#include <QJsonObject>
#include <QList>

// Klasa reprezentująca jedną osobę w drzewie genealogicznym
class Person {
public:
    Person() = default;
    Person(const QString &firstName,
           const QString &lastName,
           const QDate &birthDate,
           const QString &birthPlace);

    // Gettery i settery
    QString firstName() const;
    void setFirstName(const QString &name);

    QString lastName() const;
    void setLastName(const QString &name);

    QString maidenName() const;
    void setMaidenName(const QString &name);

    QDate birthDate() const;
    void setBirthDate(const QDate &date);

    QString birthPlace() const;
    void setBirthPlace(const QString &place);

    QDate deathDate() const;
    void setDeathDate(const QDate &date);

    QString deathPlace() const;
    void setDeathPlace(const QString &place);

    QString phone() const;
    void setPhone(const QString &phone);

    QString occupation() const;
    void setOccupation(const QString &occ);

    QString notes() const;
    void setNotes(const QString &n);

    // Relacje rodzinne
    void addChild(Person* child);
    const QList<Person*>& children() const;

    void setSpouse(Person* spouse);
    Person* spouse() const;

    void addParent(Person* parent);
    const QList<Person*>& parents() const;

    // Serializacja JSON
    QJsonObject toJson() const;
    static Person fromJson(const QJsonObject &obj);

private:
    // Dane osobowe
    QString m_firstName;
    QString m_lastName;
    QString m_maidenName;
    QDate m_birthDate;
    QString m_birthPlace;
    QDate m_deathDate;
    QString m_deathPlace;
    QString m_phone;
    QString m_occupation;
    QString m_notes;

    // Relacje
    QList<Person*> m_children;
    QList<Person*> m_parents;
    Person* m_spouse = nullptr;
};

#endif // PERSON_H
