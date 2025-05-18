#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#pragma once
#include <QString>
#include "familytree.h"

class FileManager {
public:
    // FileManager();
    static bool saveToJson(const QString& path, const FamilyTree& tree);
    static bool loadFromJson(const QString& path, FamilyTree& tree);
};

#endif // FILEMANAGER_H
