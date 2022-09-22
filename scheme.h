//
// Created by musht on 21.09.2022.
//

#ifndef DATABASELABSE_SCHEME_H
#define DATABASELABSE_SCHEME_H

#include <string>
#include <vector>
#include <unordered_map>

typedef std::unordered_map<std::string, int> Columns;
typedef std::vector<char> Bytes;

const Columns student {{"name", 20}, {"surname", 20}, {"patronymic", 20}};
const Columns variant {{"path", 40}};

class Student {
    int id;
    std::string name, surname, patronymic;
};

class Variant {
    int id;
    std::string path;
};


#endif //DATABASELABSE_SCHEME_H
