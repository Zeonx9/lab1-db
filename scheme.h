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

    explicit Student(const std::string& s);

    friend std::ostream &operator<<(std::ostream &os, const Student &s);
};

class Variant{
public:
    int id;
    std::string path;

    explicit Variant(const std::string &s);

    friend std::ostream &operator<<(std::ostream &os, const Variant &v);
};

#endif //DATABASELABSE_SCHEME_H
