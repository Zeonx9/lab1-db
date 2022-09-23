//
// Created by musht on 21.09.2022.
//

#ifndef DATABASELABSE_DB_H
#define DATABASELABSE_DB_H

#include <fstream>
#include <vector>
#include "scheme.h"

const std::string
STUDENTS_FILE_NAME = "../data/students.txt",
VARIANTS_FILE_NAME = "../data/variants.txt",
TEST_FILE_NAME = "../data/test.txt";

template<typename T>
void openTable(std::vector<T>& table, const std::string& path) {
    std::ifstream file;
    file.open(path);
    std::string line;
    while (getline(file, line)) {
        T entry(line);
        table.push_back(entry);
    }
    file.close();
}

template<typename T>
void saveTable(std::vector<T> &table, const std::string &path) {
    std::ofstream file;
    file.open(path);
    for (auto& entry: table) {
        file << entry << "\n";
    }
    file.close();
}

#endif //DATABASELABSE_DB_H
