#include "App.h"

void App::setup() {
    // anything we need? db cnxn?
    // for now, get some dummy entries
    entries.push_back({"finish todo list"});
}
// no args -> list(), 1 arg ('list') -> list(), else -> add(s)
// List: list(), prompt: "1. Add, 2. Remove, 3. Toggle Done: ?"
// Add: prompt: "Todo text: ?" -> add(s) --> list()
// Remove: prompt "Remove which: ?" -> validate number
//          if num OK: remove, -> Mode::List
//          if not OK: prompt "No todo with that number: ?" --> (don't change mode)
// Done: prompt "Mark which done: ?" -> validate num
//          if num OK: mark done [mark(bool)] -> Mode::List
//          if not OK: prompt "No todo with that number: ?"


void App::run() {
    switch(mode) {
    case Mode::List: {
        list();
        auto choice = promptForAction();       
        switch (choice) {
            case 1: {
                mode = Mode::Add;
                break;
            }
            case 2: {
                mode = Mode::Remove;
                break;
            }
            case 3: {
                mode = Mode::Done;
                break;
            }
            case 4: {
                exit(0);
                break;
            }
        }
        break;
    }
    case Mode::Add:
        std::cout << "In Mode::Add" << std::endl;
        promptForAdd();
        break;
    case Mode::Remove:
        std::cout << "In Mode::Remove" << std::endl;
        promptForRemove();
        break;
    case Mode::Done:
        std::cout << "In Mode::Done" << std::endl;
        promptForDone();
        break;
    }

    run();
}

void App::promptForAdd() {
    std::cout << "Add TODO: > ";
    std::string s;
    std::getline(std::cin, s);
    add(s);
    mode = Mode::List;
}
void App::promptForRemove() {
    std::cout << "prompt for remove" << std::endl;
    mode = Mode::List;

}
void App::promptForDone() {
    std::cout << "prompt for mark done" << std::endl;
    mode = Mode::List;
}


int App::promptForAction() {
    std::cout << "1. Add, 2. Remove, 3. Toggle Done, 4. Exit > ";
        
    std::string s;
    std::getline(std::cin, s);
    int i;
    try
    {
        i = std::stoi(s);
    }
    catch (std::invalid_argument const& ex)
    {
        std::cout << "std::invalid_argument::what(): " << ex.what() << '\n';
    }
    catch (std::out_of_range const& ex)
    {
        std::cout << "std::out_of_range::what(): " << ex.what() << '\n';
    }

    return i;
}

void App::list() {
    size_t i{0};
    for (auto entry : entries ) {
        ++i;
        std::cout << i << ".\t" << entry.body << std::endl;
    }
}

void App::add(std::string &content)
{
    entries.push_back({content});
}
