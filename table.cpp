//
// Created by musht on 21.09.2022.
//

#include <iostream>
#include "table.h"

// instantiations
template class Table<Student>;
template class Table<Variant>;
template class Table<Distribution>;

// getter & setter
template<typename T>
const std::vector<T> &Table<T>::getTable() const {
    return table;
}

template<typename T>
void Table<T>::setNextId(int s) {
    nextId = s;
}

// property
template<typename T>
int Table<T>::size() const {
    return table.size();
}

// initialization
template<typename T>
void Table<T>::createFrom(const std::string &src) {
    std::ifstream file;
    file.open(src);
    nextId = 0;

    std::string line;
    while (getline(file, line)) {
        add(T(line, false));
    }
}

template<typename T>
void Table<T>::open(const std::string &path) {
    std::ifstream file;
    file.open(path);
    file >> nextId;

    std::string line;
    while (getline(file, line)) {
        table.push_back(T(line, true));
    }
    file.close();
}

// close
template<typename T>
void Table<T>::save(const std::string &path) {
    std::ofstream file;
    file.open(path);
    file << nextId << "\n";
    for (auto& entry: table) {
        file << entry << "\n";
    }
    file.close();
}

// CRUD operations
template<typename T>
void Table<T>::addNoAutoIncrement(T item) {
    table.push_back(item);
}

template<typename T>
void Table<T>::add(T item) {
    item.id = nextId++;
    addNoAutoIncrement(item);
}

template<typename T>
void Table<T>::remove(int key) {
    for (auto it = table.begin(); it < table.end(); ++it) {
        if (it->id == key) {
            table.erase(it);
        }
    }
}

template<typename T>
void Table<T>::update(int key, T &item) {
    item.id = key;
    for (int i = 0; i < table.size(); ++i) {
        if (table[i].id == key) {
            table[i] = item;
        }
    }
}

// fills the distribution table
void distribute(Table<Distribution> &tab, const Table<Student> &studs, const Table<Variant> &vars) {
    // create a distribution engine
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dstr(1, vars.size());

    for (auto it = studs.getTable().begin() + 1; it < studs.getTable().end(); ++it) {
        int rv = vars.getTable()[dstr(rng)].id;
        // std::cout << "student id:" << it->id << " var id:" << rv << "\n";
        Distribution d(it->id, rv);
        tab.addNoAutoIncrement(d);
    }
    tab.setNextId(studs.size() - 1);
}
