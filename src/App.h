#pragma once

#include <iostream>
#include <string>
#include <vector>

typedef struct Entry {
    std::string body;
} Entry;

enum class Mode {
    List, Add, Remove, Done
};


class App {
public:
    App() = default;
    Mode mode;
    void setup();
    void run();
    void list();
    void add(std::string &content);
    std::vector<Entry> entries;
    int promptForAction();
    void promptForAdd();
    void promptForRemove();
    void promptForDone();
};


