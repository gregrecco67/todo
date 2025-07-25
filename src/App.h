#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <DbManager.h>
#include <SQLiteCpp/SQLiteCpp.h>

namespace gwr::todo
{

typedef struct Entry
{
    std::string body;
} Entry;

enum class Mode
{
    List,
    Add,
    Remove,
    Mark
};

typedef struct Todo
{
    int id;
    std::string todo;
    bool done;
} Todo;

class App
{
  public:
    App() = default;
    Mode mode;
    void setup();
    void run();
    void list();
    void add(std::string &content);
    void remove(int id);
    void markDone(int id, bool done);
    std::vector<Todo> todos;
    int promptForAction();
    void promptForAdd();
    void promptForRemove();
    void promptForMark();
    void clear_screen();
    int intFromString(std::string &s);
    int intFromCmd(std::string &c);
    std::string divider{"----- ----- ----- ----- ----- ----- ----- ----- ----- -----"};
// connection / status
#ifdef IS_LINUX
    DbManager dbm{"/home/grecco/.config/todo/app.sqlite3"};
#endif
#ifdef IS_MACOS
    DbManager dbm{"/Users/grecco/Library/Application Support/todo/app.sqlite3"};
#endif
};

} // namespace gwr::todo
