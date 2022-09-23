#include "db.h"
#include <iostream>

int main() {
    std::vector<Student> students{};
    openTable<Student>(students, STUDENTS_FILE_NAME);

    std::cout << students.size();
    saveTable(students, TEST_FILE_NAME);
}

