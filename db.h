//
// Created by musht on 24.09.2022.
//

#ifndef DATABASELABSE_DB_H
#define DATABASELABSE_DB_H

#include "table.h"

// main db class
class DataBase {
public:
    enum class Type{student, variant, distribution};
private:
    const str db_saved_data = "this_file_contain_information_about_db_state.txt";
    str root = "../data/";
    std::vector<std::pair<str, Type>> names;

    Table<Student> studs;
    Table<Variant> vars;
    Table<Distribution> dstr;

    int find(const str &name);

public:
    void create(const str &rootFolder);
    void open(const str &rootFolder);
    void close();

    void generate(const str &name, Type type, const str &src="");
    void print(const str &name, ost &os, bool toRead=false);

    void add(const str &table, const str &line);
    void remove(const str &table, int key);
    void update(const str &table, int key, const str &line);
    void printLine(const str &table, int key);
};

#endif //DATABASELABSE_DB_H
