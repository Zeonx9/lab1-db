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
    const str back_up_folder = "backup";
    str root = "../data/";
    bool modified = false, opened = false;;
    int backUpNumber = 0;

    std::vector<std::pair<str, Type>> names;

    Table<Student> studs;
    Table<Variant> vars;
    Table<Distribution> dstr;

    void distToReadStr(const Distribution &d, ost &os);
    void distribute();

public:
    int find(const str &name);
    bool isOpened() const;
    void clear();

    void create(const str &rootFolder);
    void open(const str &rootFolder, bool bu=false);
    void close(const str &folder="");

    void generate(const str &name, Type type, const str &src="");
    void regenerate(const str &name, const str &src="");
    void del(const str &table);
    void print(const str &name, ost &os, bool toRead=false);

    void add(const str &table, const str &line);
    void remove(const str &table, int key);
    void update(const str &table, int key, const str &line);
    void printLine(const str &table, int key, ost& os, bool toRead=false);

    void backUp();
    void recover(int i=-1);
    void listTables();
};

#endif //DATABASELABSE_DB_H
