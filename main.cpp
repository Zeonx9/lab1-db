#include "database.h"
# define g_distr

#ifdef g_vars
int main() {
    Table<Variant> vars;

    std::string path = "c://variants/var";
    for(int i = 0; i < 30; ++i) {
        std::string path_i = path + std::to_string(i);
        vars.add(Variant(path_i, false));
    }

    vars.save(FileNames::variants);
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
