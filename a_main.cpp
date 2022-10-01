#include "db.h"
#include <iostream>
#include <windows.h>
#include <locale>
#include <codecvt>

#define main_loop

#ifdef main_loop

str help() {
    return "=== help page ===\n"
                 "quit(q) - exits dbsm\n"
                 "help(h/?) - prints this message\n"
                 "addtable(at) - adds a table to database\n"
                 "deletetable(dt) - deletes a table from database\n"
                 "regenerate(rg) - regenerates a table\n"
                 "printtable(pt) - prints a table\n"
                 "add(a) - adds an item to a table\n"
                 "remove(r) - removes an item from a table\n"
                 "update(u) - changes an item in a table\n"
                 "printline(pl) - prints an item in a table\n"
                 "backup(bu) - saves current database state to recover it leter\n"
                 "recover(re) - restores saved state of database\n"
                 "close(cl) - closes current database\n"
                 "=== end of help ===\n";
}
str getNameOfTable() {
    str table_name;
    std::cout << ">> type a name of table\n";
    std::cin >> table_name;
    return table_name;
}
str getDirectory() {
    str dir;
    std::cout << ">> type the path to the directory\n";
    std::cin >> dir;
    return dir;
}
str getPath() {
    str path;
    std::cout << ">> type a path or \"-\" to skip\n";
    std::cin >> path;
    if (path == "-")
        path = "";
    return path;
}
str getLineRepr() {
    //std::wstring wline;
    std::cout << ">> type a description of an item\n";
    std::cin.clear();
    std::cin.ignore(1);
    str line;
    std::getline(std::cin, line);
    //std::wcout << wline;
    //std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    //str line = converter.to_bytes(wline);
    //std::cout << line;
    return line;
}
int getKey() {
    int key;
    std::cout << ">> type a key to identify item\n";
    std::cin >> key;
    return key;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand(time(nullptr));
    str command;
    DataBase db;

    while (true) {
        // open or create
        if (!db.isOpened()) {
            std::cout << ">> type \"open\"(o) to open existing database or \"create\"(c) to make a new one\n\"quit\"(q) to exit\n";
            std::cin >> command;

            if (command == "open" or command == "o") {
                db.open(getDirectory());
                if (db.isOpened())
                    std::cout << "<< database has been opened successfully\n";
                continue;
            }
            else if (command == "create" or command == "c") {
                db.create(getDirectory());
                if (!db.isOpened())
                    std::cout << "<< database has been created successfully\n";
                continue;
            }
            else if (command == "quit" or command == "q") {
                std::cout << "<< exiting...\n";
                return 0;
            }
            else {
                std::cerr << "<< unknown command - " << command << "\n";
                continue;
            }
        }

        // get a command;
        std::cout << ">> type a command: \"quit\"(q) to exit and \"help\"(h/?) to get list of commands\n";
        std::cin >> command;

        // check it and execute;
        if (command == "quit" or command == "q") {
            std::cout << "<< closing everything and exiting...\n";
            db.close();
            return 0;
        }
        if (command == "help" or command == "h" or command == "?") {
            std::cout << help();
        }
        else if (command == "addtable" or command == "at") {
            str table_name = getNameOfTable(), type;
            std::cout << ">> type \"student\"(s) to add table of students, \"variant\"(v) to add a table of variants\n(otherwise distribution would be generated)\n";
            std::cin >> type;
            DataBase::Type t = DataBase::Type::distribution;
            if (type == "student" or type == "s")
                t = DataBase::Type::student;
            else if (type == "variant" or type == "v")
                t = DataBase::Type::variant;
            db.generate(table_name, t, getPath());
        }
        else if (command == "deletetable" or command == "dt") {
            db.del(getNameOfTable());
        }
        else if (command == "regenerate" or command == "rg") {
            auto name = getNameOfTable();
            db.regenerate(name, getPath());
        }
        else if (command == "printtable" or command == "pt") {
            db.print(getNameOfTable(), std::cout, true);
        }
        else if (command == "add" or command == "a") {
            auto name = getNameOfTable();
            db.add(name, getLineRepr());
        }
        else if (command == "remove" or command =="r") {
            auto name = getNameOfTable();
            db.remove(name, getKey());
        }
        else if (command == "update" or command == "u") {
            auto name = getNameOfTable();
            auto key = getKey();
            db.update(name, key, getLineRepr());
        }
        else if (command == "printline" or command == "pl") {
            auto name = getNameOfTable();
            db.printLine(name, getKey(), std::cout, true);
        }
        else if (command == "backup" or command == "bu") {
            db.backUp();
        }
        else if (command == "recover" or command == "re") {
            int i = -1;
            std::cout << ">> type the number of backup to be restored, or -1 to to get the last\n";
            std::cin >> i;
            db.recover(i);
        }
        else if (command == "list" or command == "l") {
            std::cout << "0 = table of students, 1 = table of variants, 2 = testing table\n";
            db.listTables();
        }
        else if (command == "close" or command == "cl") {
            db.close();

        }
        else {
            // error message
            std::cerr << "<< unknown command - " << command << "\n";
        }
    }
}
#endif

#ifdef db_test
int main() {
    SetConsoleOutputCP(CP_UTF8);
    DataBase db;
    db.open("../data_test/");

    db.printLine("students", 51, std::cout);
    db.del("students");
    db.del("testing_table");
    db.backUp();

    db.printLine("students", 51, std::cout);
//    db.recover();
//    db.printLine("students", 51, std::cout);

//    db.print("students", std::cout);
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
