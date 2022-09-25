#include "db.h"
#include <iostream>
#include <windows.h>

#define db_test

#ifdef db_test
int main() {
    SetConsoleOutputCP(CP_UTF8);
    DataBase db;
    db.open("../data_test/");

    db.generate("testing_table", DataBase::Type::distribution);
    db.print("testing_table", std::cout, true);

    db.print("students", std::cout);
    db.close();
}
#endif

#ifdef g_db
int main() {
    SetConsoleOutputCP(CP_UTF8);
    DataBase db;
    db.create("../data_test/");

    db.generate("students", DataBase::Type::student, "../data/names.txt");
    db.generate("variants", DataBase::Type::variant, "../data/vars.txt");
    db.generate("testing_table", DataBase::Type::distribution);

    db.print("testing_table", std::cout, true);

    db.close();
}
#endif

#ifdef g_vars
int main() {
    std::ofstream file;
    file.open("../data/vars.txt");
    std::string path = "c://variants/var";
    for(int i = 0; i < 30; ++i) {
        file << path << i << "\n"
    }
    file.close();
}
#endif
