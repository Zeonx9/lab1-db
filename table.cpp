//
// Created by musht on 21.09.2022.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
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

// property
template<typename T>
int Table<T>::size() const {
    return table.size();
}

// operator
template<typename T>
T &Table<T>::operator[](unsigned int index) {
    return table[index];
}

// initialization
template<typename T>
void Table<T>::createFrom(const str &src) {
    ifst file(src);
    nextId = 0;

    str line;
    while (getline(file, line)) {
        // create the Entry and put it in the table
        add(T(line, false), true);
    }
}

template<typename T>
void Table<T>::open(const str &path) {
    ifst file(path);
    // get the first line and take the nextId number
    str line;
    std::getline(file, line);
    sst ss(line);
    ss >> nextId;

    // scan entries
    while (getline(file, line)) {
        table.push_back(T(line, true));
    }
    file.close();
}

// close
template<typename T>
void Table<T>::save(const str &path) {
    ofst file(path);
    // file should be truncated before writing
    // first line in the file is the ID which should the next added element has
    // then line by line is entries of the table
    file << nextId << "\n";
    for (auto &entry : table) {
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
void distribute(Table<Distribution> &tab,
                Table<Student> &studs,
                Table<Variant> &vars) {
    // create a distribution engine
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dstr(1, vars.size());

    // for each student give the variant randomly
    for (auto &stud: studs.getTable()) {
        // std::cout << "student id:" << it->id << " var id:" << rv << "\n";
        tab.add(Distribution(stud.id, vars[dstr(rng)].id)); // without changing the id
    }
}
