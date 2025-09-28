#include "person.h"

// Konstruktor z podstawowymi danymi
Person::Person(const QString &firstName,
               const QString &lastName,
               const QDate &birthDate,
               const QString &birthPlace)
    : m_firstName(firstName),
    m_lastName(lastName),
    m_birthDate(birthDate),
    m_birthPlace(birthPlace) {}

// --- Gettery i settery ---
QString Person::firstName() const { return m_firstName; }
void Person::setFirstName(const QString &name) { m_firstName = name; }

QString Person::lastName() const { return m_lastName; }
void Person::setLastName(const QString &name) { m_lastName = name; }

QString Person::maidenName() const { return m_maidenName; }
void Person::setMaidenName(const QString &name) { m_maidenName = name; }

QDate Person::birthDate() const { return m_birthDate; }
void Person::setBirthDate(const QDate &date) { m_birthDate = date; }

QString Person::birthPlace() const { return m_birthPlace; }
void Person::setBirthPlace(const QString &place) { m_birthPlace = place; }

QDate Person::deathDate() const { return m_deathDate; }
void Person::setDeathDate(const QDate &date) { m_deathDate = date; }

QString Person::deathPlace() const { return m_deathPlace; }
void Person::setDeathPlace(const QString &place) { m_deathPlace = place; }

QString Person::phone() const { return m_phone; }
void Person::setPhone(const QString &phone) { m_phone = phone; }

QString Person::occupation() const { return m_occupation; }
void Person::setOccupation(const QString &occ) { m_occupation = occ; }

QString Person::notes() const { return m_notes; }
void Person::setNotes(const QString &n) { m_notes = n; }

// --- Relacje ---
void Person::addChild(Person* child) { m_children.append(child); }
const QList<Person*>& Person::children() const { return m_children; }

void Person::setSpouse(Person* spouse) { m_spouse = spouse; }
Person* Person::spouse() const { return m_spouse; }

void Person::addParent(Person* parent) { m_parents.append(parent); }
const QList<Person*>& Person::parents() const { return m_parents; }

// --- Serializacja JSON ---
QJsonObject Person::toJson() const {
    QJsonObject obj;
    obj["firstName"] = m_firstName;
    obj["lastName"] = m_lastName;
    obj["maidenName"] = m_maidenName;
    obj["birthDate"] = m_birthDate.toString(Qt::ISODate);
    obj["birthPlace"] = m_birthPlace;
    obj["deathDate"] = m_deathDate.isValid() ? m_deathDate.toString(Qt::ISODate) : "";
    obj["deathPlace"] = m_deathPlace;
    obj["phone"] = m_phone;
    obj["occupation"] = m_occupation;
    obj["notes"] = m_notes;
    return obj;
}

Person Person::fromJson(const QJsonObject &obj) {
    Person p;
    p.m_firstName = obj["firstName"].toString();
    p.m_lastName = obj["lastName"].toString();
    p.m_maidenName = obj["maidenName"].toString();
    p.m_birthDate = QDate::fromString(obj["birthDate"].toString(), Qt::ISODate);
    p.m_birthPlace = obj["birthPlace"].toString();
    p.m_deathDate = QDate::fromString(obj["deathDate"].toString(), Qt::ISODate);
    p.m_deathPlace = obj["deathPlace"].toString();
    p.m_phone = obj["phone"].toString();
    p.m_occupation = obj["occupation"].toString();
    p.m_notes = obj["notes"].toString();
    return p;
}
