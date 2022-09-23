//
// Created by musht on 21.09.2022.
//

#include "scheme.h"


Student::Student(const std::string &s) {
    std::stringstream ss(s);
    ss >> id >> surname >> name >> patronymic;
}

Variant::Variant(const std::string &s) {
    std::stringstream ss(s);
    ss >> id >> path;
}

std::ostream &operator<<(std::ostream &os, const Student &s) {
    os << s.id << " " << s.name << " " << s.surname << " " << s.patronymic;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Variant &v) {
    os << v.id << " " << v.path;
    return os;
}

