//
// Created by musht on 24.09.2022.
//

#include <iostream>
#include <fstream>
#include <random>
#include <filesystem>
#include "db.h"

int DataBase::find(const str &name) {
    for (int i = 0; i < names.size(); ++i) {
        if (names[i].first == name) {
            return i;
        }
    }
    return -1;
}

void DataBase::create(const str &rootFolder) {
    root = rootFolder;
    std::filesystem::create_directories(root);
}

void DataBase::open(const str &rootFolder) {
    root = rootFolder;

    ifst file(root + db_saved_data);
    if (!file){
        std::cout << "DB not found\n";
        return;
    }
    int n;
    file >> n >> modified;

    for (int i = 0; i < n; ++i) {
        str s; int t;
        file >> s >> t;
        // bind table to
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

void DataBase::close(const str &folder) {
    ofst file((folder.empty() ? root : folder) + db_saved_data);

    // write number of tables
    file << names.size() << " " << modified << "\n";
    for (auto &p: names){
        file << p.first << " " << (int) p.second << "\n";
        auto path = (folder.empty() ? root : folder) + p.first + ".txt";

        // save all opened tables
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

// creates a table and binds it to db object
void DataBase::generate(const str &name, DataBase::Type type, const str &src) {
    for (auto &p: names) {
        if (p.first == name or p.second == type) {
            std::cerr << "\"" << name << "\" table already exists\n";
            return;
        }
    }

    // bind table to db
    auto path = root + name + ".txt";
    names.emplace_back(name, type);

    // create table and put it in the right place
    // saves created table to file
    switch (type) {
        case Type::student :
            if (!src.empty() and studs.size() == 0)
                studs.createFrom(src);
            studs.save(path);
            break;
        case Type::variant :
            if (!src.empty() and vars.size() == 0)
                vars.createFrom(src);
            vars.save(path);
            break;
        case Type::distribution :
            if (studs.size() > 0 and vars.size() > 0) {
                distribute();
                dstr.save(path);
            }
            else
                std::cerr << "No accessible student or variant information to make distribution\n";
    }
}

void DataBase::regenerate(const str &name, Type type, const str &src) {
    del(name);
    generate(name, type, src);
}

void DataBase::distribute() {
    // create a distribution engine
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::mt19937::result_type> rnd(1, vars.size());

    // for each student give the variant randomly
    for (auto &stud: studs.getTable()) {
        // std::cout << "student id:" << it->id << " var id:" << rv << "\n";
        dstr.add(Distribution(stud.id, vars[rnd(rng)].id)); // without changing the id
    }
    modified = false;
}

void DataBase::del(const str &table) {
    auto ind = find(table);
    if (ind == -1) {
        std::cerr << "No such table \"" << table << "\" to delete\n";
        return;
    }

    std::filesystem::remove(root + names[ind].first + ".txt");

    switch (names[ind].second) {
        case Type::student:
            studs.clear();
            break;
        case Type::variant:
            vars.clear();
            break;
        case Type::distribution:
            dstr.clear();
    }

    names.erase(names.begin() + ind);
}

void DataBase::distToReadStr(const Distribution &d, ost &os) {
    auto &s = studs[d.id];
    os << s.surname <<  " " + s.name << " " << s.patronymic << "\t\t" <<  vars[d.var].path;
}


void DataBase::print(const str &name, ost &os, bool toRead)  {
    auto ind = find(name);
    if (ind == -1) {
        std::cerr << "No such table: \"" << name << "\" to print\n";
        return;
    }

    // check for printing distribution to read it
    if (names[ind].second == Type::distribution and toRead) {
        if (modified) {
            std::cerr << "tables were modified, \"" << names[ind].first << "\" should be regenerated\n";
            return;
        }
        for (auto &row : dstr.getTable()) {
            distToReadStr(row, os);
            os << "\n";
        }
        return;
    }

    // print a table
    switch (names[ind].second) {
        case Type::student : {
            for (auto &t : studs.getTable())
                os << t << "\n";
            break;
        }
        case Type::variant : {
            for (auto &t : vars.getTable())
                os << t << "\n";
            break;
        }
        case Type::distribution : {
            for (auto &t : dstr.getTable())
                os << t << "\n";
        }
    }
}

void DataBase::add(const str &table, const str &line) {
    auto ind = find(table);
    if (ind == -1) {
        std::cerr << "add() failed, table not found\n";
        return;
    }
    switch (names[ind].second) {
        case Type::student:
            studs.add(Student(line, false), true);
            break;
        case Type::variant:
            vars.add(Variant(line, false), true);
            break;
        case Type::distribution:
            std::cerr << "add() not allowed for \"" << names[ind].first << "\"\n";
    }
}

void DataBase::remove(const str &table, int key) {
    auto ind = find(table);
    if (ind == -1) {
        std::cerr << "remove() failed, table not found\n";
        return;
    }
    modified = true;
    switch (names[ind].second) {
        case Type::student:
            studs.remove(key);
            break;
        case Type::variant:
            vars.remove(key);
            break;
        case Type::distribution:
            std::cerr << "remove() not allowed for \"" << names[ind].first << "\"\n";
    }
}

void DataBase::update(const str &table, int key, const str &line) {
    auto ind = find(table);
    if (ind == -1) {
        std::cerr << "update() failed, table not found\n";
        return;
    }
    modified = true;
    switch (names[ind].second) {
        case Type::student:
            studs.update(key, Student(line, false));
            break;
        case Type::variant:
            vars.update(key, Variant(line, false));
            break;
        case Type::distribution:
            std::cerr << "upadate() not allowed for \"" << names[ind].first << "\"\n";
    }
}

void DataBase::printLine(const str &table, int key, ost& os, bool toRead) {
    auto ind = find(table);
    if (ind == -1) {
        std::cerr << "printLine() failed, table not found\n";
        return;
    }
    bool notFound;
    switch (names[ind].second) {
        case Type::student: {
            auto &s = studs.find(key, notFound);
            if (notFound) {
                std::cerr << "key not found\n";
                return;
            }
                os << s << "\n";
            break;
        } case Type::variant: {
            auto &v = vars.find(key, notFound);
            if (notFound) {
                std::cerr << "key not found\n";
                return;
            }
            os << v << "\n";
            break;
        } case Type::distribution: {
            auto &d = dstr.find(key, notFound);
            if (notFound) {
                std::cerr << "key not found\n";
                return;
            }
            if (toRead) {
                if (modified) {
                    std::cerr << "tables were modified, \"" << names[ind].first << "\" should be regenerated\n";
                    return;
                }
                distToReadStr(d, os);
                os << "\n";
            }
            else
                os << d << "\n";
        }
    }
}

void DataBase::backUp() {
    auto folder = root + back_up_folder;
    std::filesystem::create_directories(folder);
    close(folder);
}

void DataBase::recover() {
    auto prevRoot = root;
    for (auto &p : names) {
        del(p.first);
    }
    open(root + back_up_folder);
    root = prevRoot;
}


