//
// Created by musht on 21.09.2022.
//

#ifndef DATABASELABSE_DB_H
#define DATABASELABSE_DB_H
#include "scheme.h"

class Entry {
private:
    Columns& scheme;
    Bytes bytes;

public:
    int id=-1;

    Entry(Columns& s, Bytes b);;
    Entry(const Entry& e)=default;

    Entry& operator=(Entry&& e) noexcept;

};

class Table {
private:
    std::vector<Entry> entries;
    int nextId=0;

public:
    Table()= default;

    void add(Entry& e);
    int find(int key);
    void remove(int key);
};


typedef std::unordered_map<std::string, Table> MapOfTables;

class DataBase{
    MapOfTables tables;
};

#endif //DATABASELABSE_DB_H
