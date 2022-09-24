//
// Created by musht on 24.09.2022.
//

#include <iostream>
#include "db.h"

int DataBase::find(const std::string &name) {
    for (int i = 0; i < names.size(); ++i) {
        if (names[i].first == name) {
            return i;
        }
    }
    return -1;
}

void DataBase::create(const std::string &rootFolder) {
    root = rootFolder;
}

void DataBase::generate(const std::string &name, DataBase::Type type, const std::string &src) {
    if (find(name) != -1) {
        std::cout << "such table already exists\n";
        return;
    }

    auto path = root + name + ".txt";
    names.emplace_back(name, type);
    switch (type) {
        case Type::student : {
            if (!src.empty() and studs.size() == 0)
                studs.createFrom(src);
            studs.save(path);
        }
            break;
        case Type::variant : {
            vars.save(path);
        }
            break;
        case Type::distribution : {
            if (studs.size() > 0 and vars.size() > 0)
                distribute(dstr, studs, vars);
            else
                std::cout << "No accesible student or variant information to make distribution\n";
            dstr.save(path);
        }
    }
}

void DataBase::print(const std::string &name, std::ostream &os, bool toRead) {
    auto ind = find(name);
    if (ind == -1) {
        std::cout << "No such table\n";
        return;
    }

    if (names[ind].second == Type::distribution and toRead) {
        for (auto row = dstr.getTable().begin() + 1; row < dstr.getTable().end(); ++row) {
            Student s = studs.getTable()[row->id];
            os << s.surname << " " << s.name << " " << s.patronymic << "\t" << vars.getTable()[row->var].path << "\n";
        }
        return;
    }
    switch (names[ind].second) {
        case Type::student : {
            for (int i = 1; i < studs.size(); ++i) {
                os << studs.getTable()[i] << "\n";
            }
            break;
        }
        case Type::variant : {
            for (int i = 1; i < studs.size(); ++i) {
                os << vars.getTable()[i] << "\n";
            }
            break;
        }
        case Type::distribution : {
            for (int i = 1; i < studs.size(); ++i) {
                os << dstr.getTable()[i] << "\n";
            }
        }
    }
}

void DataBase::close() {
    std::ofstream file;
    file.open(root + db_saved_data);
    file << names.size() << "\n";
    for (auto &p: names){
        file << p.first << " " << (int) p.second << "\n";
        auto path = root + p.first + ".txt";
        switch (p.second) {
            case Type::student:
                studs.save(path);
                break;
            case Type::variant:
                vars.save(path);
                break;
            case Type::distribution:
                dstr.save(path);
        }
    }

    file.close();
}

void DataBase::open(const std::string &rootFolder) {
    root = rootFolder;

    std::ifstream file;
    file.open(root + db_saved_data);
    if (!file){
        std::cout << "DB not found\n";
        return;
    }

    int n;
    file >> n;
    for (int i = 0; i < n; ++i) {
        std::string s;
        int t;
        file >> s >> t;
        names.emplace_back(s, (Type) t);
        auto path = root + s + ".txt";
        switch ((Type) t) {
            case Type::student:
                studs.open(path);
                break;
            case Type::variant:
                vars.open(path);
                break;
            case Type::distribution:
                dstr.open(path);
        }
    }
    file.close();
}

