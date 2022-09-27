//
// Created by musht on 21.09.2022.
//
#include <sstream>
#include "scheme.h"

// insertion operators
ost &operator<<(ost &os, const Student &s) {
    os << s.id << " " << s.surname << " " << s.name << " " << s.patronymic;
    return os;
}

ost &operator<<(ost &os, const Variant &v) {
    os << v.id << " " << v.path;
    return os;
}

ost &operator<<(ost &os, const Distribution &d) {
    os << d.id << " " << d.var;
    return os;
}

Student::Student(const str &s, bool withId) {
    id = -1;
    sst ss(s);
    if (withId)
        ss >> id;
    ss >> surname >> name >> patronymic;
}

str Student::toString() const {
    return surname + name + patronymic;
}

Variant::Variant(const str&s, bool withId) {
    id = -1;
    sst ss(s);
    if (withId)
        ss >> id;
    ss >> path;
}

str Variant::toString() const {
    return path;
}

Distribution::Distribution(const str&s, bool withId) {
    id = var = -1;
    sst ss(s);
    ss >> id >> var;
}

Distribution::Distribution(int studId, int varId) {
    id = studId;
    var = varId;
}

str Distribution::toString() const {
    return std::to_string(id) + std::to_string(var);
}
