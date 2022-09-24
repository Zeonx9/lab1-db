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
        // create the Entry and put it in the table
        add(T(line, false), true);
    }
}

template<typename T>
void Table<T>::open(const std::string &path) {
    std::ifstream file;
    file.open(path);

    // get the first line and take the nextId number
    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    ss >> nextId;

    // scan entries
    while (getline(file, line)) {
        table.push_back(T(line, true));
    }
    file.close();
}

// close
template<typename T>
void Table<T>::save(const std::string &path) {
    std::ofstream file;
    // file should be truncated before writing
    // first line in the file is the ID which should the next added element has
    // then line by line is entries of the table
    file.open(path, std::ios::trunc);
    file << nextId << "\n";
    for (auto &entry: table) {
        file << entry << "\n";
    }
    file.close();
}

// CRUD operations
template<typename T>
void Table<T>::add(T item, bool autoInc) {
    if (autoInc) {
        item.id = nextId;
        ++nextId;
    }
    table.push_back(item);
}

template<typename T>
void Table<T>::remove(int key) {
    for (auto it = table.begin(); it < table.end(); ++it) {
        if (it->id == key) {
            table.erase(it);
            return;
        }
    }
}

template<typename T>
void Table<T>::update(int key, T &item) {
    item.id = key;
    for (int i = 0; i < table.size(); ++i) {
        if (table[i].id == key) {
            table[i] = item;
            return;
        }
    }
}

// fills the distribution table
void distribute(Table<Distribution> &tab, const Table<Student> &studs, const Table<Variant> &vars) {
    // create a distribution engine
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dstr(1, vars.size());

    // for each student give the variant randomly
    for (auto &stud: studs.getTable()) {
        int rv = vars.getTable()[dstr(rng)].id;
        // std::cout << "student id:" << it->id << " var id:" << rv << "\n";
        Distribution d(stud.id, rv);
        tab.add(d, false); // without changing the id
    }
}
