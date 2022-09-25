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
    bool modified = false;
    std::vector<std::pair<str, Type>> names;


    Table<Student> studs;
    Table<Variant> vars;
    Table<Distribution> dstr;

public:
    int find(const str &name);

    void create(const str &rootFolder);
    void open(const str &rootFolder);
    void close();

    void generate(const str &name, Type type, const str &src="");
    void regenerate(const str &name, Type type, const str &src="");
    void del(const str &table);
    void distribute();
    void distToReadStr(const Distribution &d, ost &os);
    void print(const str &name, ost &os, bool toRead=false);

    void add(const str &table, const str &line);
    void remove(const str &table, int key);
    void update(const str &table, int key, const str &line);
    void printLine(const str &table, int key, ost& os, bool toRead=false);
};

#endif //DATABASELABSE_DB_H
