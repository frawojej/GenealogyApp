#include "familytree.h"

// FamilyTree::FamilyTree() {}

void FamilyTree::addPerson(const Person& person) {
    Person copy = person;
    copy.id = nextId++;
    people[copy.id] = copy;
}

Person* FamilyTree::getPerson(int id) {
    return people.contains(id) ? &people[id] : nullptr;
}

// Proste implementacje placeholder – do rozwinięcia
QVector<Person*> FamilyTree::getAncestors(int, int) {
    return {};
}

QVector<Person*> FamilyTree::getDescendants(int, int) {
    return {};
}
