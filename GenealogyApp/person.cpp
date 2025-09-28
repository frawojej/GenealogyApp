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

// --- ID ---
int Person::id() const { return m_id; }
void Person::setId(int id) { m_id = id; }

// --- Relacje rodzinne (ID) ---
const QList<int>& Person::childrenIds() const { return m_childrenIds; }
void Person::addChildId(int childId) {
    // Prosta ochrona przed duplikatami
    if (!m_childrenIds.contains(childId)) {
        m_childrenIds.append(childId);
    }
}

const QList<int>& Person::parentIds() const { return m_parentIds; }
void Person::addParentId(int parentId) {
    if (!m_parentIds.contains(parentId)) {
        m_parentIds.append(parentId);
    }
}

int Person::spouseId() const { return m_spouseId; }
void Person::setSpouseId(int spouseId) { m_spouseId = spouseId; }

// --- Serializacja JSON ---
QJsonObject Person::toJson() const {
    QJsonObject obj;

    // Dane osobowe
    obj["id"] = m_id; // zapisujemy ID osoby
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

    // Relacje: zapisujemy listy ID
    QJsonArray childrenArray;
    for (int id : m_childrenIds) childrenArray.append(id);
    obj["children"] = childrenArray;

    QJsonArray parentsArray;
    for (int id : m_parentIds) parentsArray.append(id);
    obj["parents"] = parentsArray;

    obj["spouse"] = m_spouseId; // -1 jeśli brak

    return obj;
}

Person Person::fromJson(const QJsonObject &obj) {
    Person p;

    // ID
    p.m_id = obj["id"].toInt(-1);

    // Dane osobowe
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

    // Relacje
    QJsonArray childrenArray = obj["children"].toArray();
    for (const QJsonValue &val : childrenArray) p.m_childrenIds.append(val.toInt());

    QJsonArray parentsArray = obj["parents"].toArray();
    for (const QJsonValue &val : parentsArray) p.m_parentIds.append(val.toInt());

    p.m_spouseId = obj["spouse"].toInt(-1);

    return p;
}
