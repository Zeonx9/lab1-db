//
// Created by musht on 24.09.2022.
//

#ifndef DATABASELABSE_DB_H
#define DATABASELABSE_DB_H

#include "table.h"

class DataBase {
public:
    enum class Type{student, variant, distribution};
private:
    const std::string db_saved_data = "this_file_contain_information_about_db_state.txt";
    std::string root = "../data/";
    std::vector<std::pair<std::string, Type>> names;

    Table<Student> studs;
    Table<Variant> vars;
    Table<Distribution> dstr;

    int find(const std::string &name);

public:
    void create(const std::string &rootFolder);
    void open(const std::string &rootFolder);
    void close();
    void generate(const std::string &name, Type type, const std::string &src="");
    void print(const std::string &name, std::ostream &os, bool toRead=false);
};

#endif //DATABASELABSE_DB_H
