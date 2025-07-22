#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>

namespace gwr::todo {

class DbManager {
public:
    SQLite::Database db;
    DbManager(std::string dbFileName);
};

} // namespace gwr::todo
