#include "filemanager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

bool FileManager::saveToJson(const QString& path, const FamilyTree& tree) {
    QJsonArray peopleArray;

    for (const Person& p : tree.getPeople()) {
        QJsonObject obj;
        obj["firstName"] = p.firstName;
        obj["lastName"] = p.lastName;
        obj["birthDate"] = p.birthDate;
        obj["birthPlace"] = p.birthPlace;
        obj["notesRichText"] = p.notesRichText;
        peopleArray.append(obj);
    }

    QJsonDocument doc(peopleArray);
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) return false;
    file.write(doc.toJson());
    file.close();
    return true;
}

bool FileManager::loadFromJson(const QString& path, FamilyTree& tree) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return false;

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) return false;

    tree.clear();  // czyści stare dane

    QJsonArray arr = doc.array();
    for (const QJsonValue& val : arr) {
        QJsonObject obj = val.toObject();
        Person p;
        p.firstName = obj["firstName"].toString();
        p.lastName = obj["lastName"].toString();
        p.birthDate = obj["birthDate"].toString();
        p.birthPlace = obj["birthPlace"].toString();
        p.notesRichText = obj["notesRichText"].toString();
        tree.addPerson(p);
    }

    return true;
}
