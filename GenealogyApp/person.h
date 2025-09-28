#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDate>
#include <QJsonObject>
#include <QJsonArray>
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

    // --- ID (unikalne) ---
    // Uwaga: ID nadaje MainWindow przy dodawaniu nowej osoby.
    int id() const;             // getter ID
    void setId(int id);         // setter ID (używany przy tworzeniu oraz odczycie z JSON)

    // --- Relacje rodzinne (zapisywane jako ID, nie wskaźniki) ---
    // Dzięki temu relacje są stabilne i łatwo je serializować do JSON.
    const QList<int>& childrenIds() const;
    void addChildId(int childId);

    const QList<int>& parentIds() const;
    void addParentId(int parentId);

    int spouseId() const;
    void setSpouseId(int spouseId);

    // --- Serializacja JSON ---
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

    // --- Unikalny identyfikator osoby ---
    // Domyślnie -1 oznacza, że ID nie zostało jeszcze nadane.
    int m_id = -1;

    // --- Relacje (przechowujemy ID innych osób) ---
    QList<int> m_childrenIds;  // lista ID dzieci
    QList<int> m_parentIds;    // lista ID rodziców
    int m_spouseId = -1;       // ID małżonka (-1 = brak)
};

#endif // PERSON_H
