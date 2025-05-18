#ifndef FAMILYTREE_H
#define FAMILYTREE_H

#pragma once
#include <QMap>
#include "person.h"

class FamilyTree {
public:
    // FamilyTree();
    void addPerson(const Person &p);
    QList<Person> getPeople() const {
        return people.values();
    }
    void clear() {
        people.clear();
        nextId = 0;
    }
    Person* getPerson(int id);
    QVector<Person*> getAncestors(int id, int depth = -1);
    QVector<Person*> getDescendants(int id, int depth = -1);
private:
    QMap<int, Person> people;
    int nextId = 0;
};

#endif // FAMILYTREE_H
