//
// Created by musht on 21.09.2022.
//

#ifndef DATABASELABSE_SCHEME_H
#define DATABASELABSE_SCHEME_H

#include <string>
#include <sstream>
#include <ostream>

class Student{
public:
    int id;
    std::string name, surname, patronymic;
    Student(const std::string &s, bool withId);

    friend std::ostream &operator<<(std::ostream &os, const Student &s);
};

class Variant{
public:
    int id;
    std::string path;

    Variant(const std::string &s, bool withId);

    friend std::ostream &operator<<(std::ostream &os, const Variant &v);
};

class Distribution {
public:
    int id, var;
    Distribution(const std::string &s, bool withId);
    Distribution(int studId, int varId);

    friend std::ostream &operator<<(std::ostream &os, const Distribution &d);
};

#endif //DATABASELABSE_SCHEME_H
