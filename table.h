//
// Created by musht on 21.09.2022.
//

#ifndef DATABASELABSE_TABLE_H
#define DATABASELABSE_TABLE_H

#include "scheme.h"
#include <fstream>
#include <vector>
#include <random>

template<typename T>
class Table {
private:
    std::vector<T> table;
    int nextId=0;

public:
    int size() const;
    const std::vector<T> &getTable() const;
    void setNextId(int nextId);

    void createFrom(const std::string& src);
    void open(const std::string& path);
    void save(const std::string &path);

    void add(T item, bool autoInc);
    void remove(int key);
    void update(int key, T&item);
};

void distribute(Table<Distribution> &tab, const Table<Student> &studs, const Table<Variant> &vars);

#endif //DATABASELABSE_TABLE_H
