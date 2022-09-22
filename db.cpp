//
// Created by musht on 21.09.2022.
//

#include "db.h"

Entry::Entry(Columns &s, Bytes b) : scheme{s}, bytes{std::move(b)} {}

Entry &Entry::operator=(Entry &&e) noexcept {
    id = e.id;
    scheme = e.scheme;
    bytes = std::move(e.bytes);
    return *this;
}

void Table::add(Entry &e) {
    e.id = ++nextId;
    entries.push_back(e);
}

int Table::find(int key) {
    for (int i = 0; i < entries.size(); ++i) {
        if (entries[i].id == key)
            return i;
    }
    return -1;
}

void Table::remove(int key) {
    int index = find(key);
    if (index < 0)
        throw std::domain_error("NO SUCH ENTRY");

    entries.erase(entries.cbegin() + index);

}
