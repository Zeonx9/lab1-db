#include "table.h"
# define db_test

#ifdef db_test
#include "db.h"
#include <iostream>
#include <fstream>

int main() {
   DataBase db;
   //db.create("../data_test/");
   db.open("../data_test/");

    db.print("students", std::cout);
    std::cout << "\n\n\n";
    db.print("variants", std::cout);
    std::cout << "\n\n\n";

    db.generate("distrib", DataBase::Type::distribution);
    db.print("distrib", std::cout, true);

//    db.generate("students", DataBase::Type::student, "../data/names.txt");
//    db.generate("variants", DataBase::Type::variant, "../data/vars.txt");
//    db.generate("testing_table", DataBase::Type::distribution);
//
//    db.print("testing_table", std::cout);
//    db.print("testing_table", std::cout, true);
//
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

#ifdef g_studs
int main() {
    Table<Student> studs;
    studs.createFrom(FileNames::names);
    studs.save(FileNames::students);
}
#endif

#ifdef g_distr
int main() {
    Table<Distribution> dist;
    Table<Student> studs;
    Table<Variant> vars;
    studs.open(FileNames::students);
    vars.open(FileNames::variants);

    distribute(dist, studs, vars);
    dist.save(FileNames::distributed);
}
#endif
