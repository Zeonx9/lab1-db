//
// Created by musht on 21.09.2022.
//

#include "scheme.h"

// insertion operators
std::ostream &operator<<(std::ostream &os, const Student &s) {
    os << s.id << " " << s.name << " " << s.surname << " " << s.patronymic;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Variant &v) {
    os << v.id << " " << v.path;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Distribution &d) {
    os << d.id << " " << d.var;
    return os;
}

Student::Student(const std::string &s, bool withId) : Entry() {
    std::stringstream ss(s);
    id = -1;
    if (withId)
        ss >> id;
    ss >> surname >> name >> patronymic;
}

Variant::Variant(const std::string &s, bool withId) : Entry() {
    std::stringstream ss(s);
    id = -1;
    if (withId)
        ss >> id;
    ss >> path;
}

Distribution::Distribution(const std::string &s, bool withId) : Entry() {
    std::stringstream ss(s);
    id = var = -1;
    ss >> id >> var;
}

Distribution::Distribution(int studId, int varId) : Entry() {
    id = studId;
    var = varId;
}
