//
// Created by musht on 21.09.2022.
//

#ifndef DATABASELABSE_TABLE_H
#define DATABASELABSE_TABLE_H

#include <vector>
#include "scheme.h"

using ifst = std::ifstream;
using ofst = std::ofstream;

template<typename T>
class Table {
private:
    std::vector<T> table;
    int nextId=0;

public:
    int size() const;
    const std::vector<T> &getTable() const;
    T &operator[](unsigned int index);

    void createFrom(const str& src);
    void open(const str& path);
    void save(const str &path);

    T &find(int key, bool &err);
    bool findByStr(const str &line);
    void add(T item, bool autoInc=false);
    void remove(int key);
    void update(int key, T item);

    void clear();

};


#endif //DATABASELABSE_TABLE_H
