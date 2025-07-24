#include "App.h"
#include <exception>

namespace gwr::todo
{

void App::setup()
{
    // for now, get some dummy entries
    SQLite::Statement st{dbm.db, "SELECT * from todos where 1;"};
    todos.clear();
    while (st.executeStep())
    {
        Todo todo{.id = st.getColumn("id").getInt(), .todo = st.getColumn("todo").getString(), .done = (st.getColumn("done").getInt() == 1)};
        todos.push_back(todo);
    }
}

void App::run()
{
    switch (mode)
    {
    case Mode::List:
    {
        list();
        auto choice = promptForAction();
        switch (choice)
        {
        case 1:
        {
            mode = Mode::Add;
            break;
        }
        case 2:
        {
            mode = Mode::Remove;
            break;
        }
        case 3:
        {
            mode = Mode::Mark;
            break;
        }
        case 4:
        {
            exit(0);
            break;
        }
        }
        break;
    }
    case Mode::Add:
        promptForAdd();
        break;
    case Mode::Remove:
        promptForRemove();
        break;
    case Mode::Mark:
        promptForMark();
        break;
    }

    run();
}

void App::promptForAdd()
{
    std::cout << "What needs done? ";
    std::string s;
    std::getline(std::cin, s);
    add(s);
    mode = Mode::List;
}
void App::promptForRemove()
{
    std::cout << "Remove which? ";
    std::string s;
    std::getline(std::cin, s);
    int i{-1};
    try
    {
        i = std::stoi(s);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception thrown: " << e.what() << std::endl;
    }
    if (i != -1 && i <= todos.size())
    {
        remove(todos[i - 1].id);
    }
    setup();
    std::cout << divider << std::endl;
    mode = Mode::List;
}
void App::promptForMark()
{
    std::cout << "Mark which done/undone? ";
    std::string s;
    std::getline(std::cin, s);
    int i{-1};
    try
    {
        i = std::stoi(s);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception thrown: " << e.what() << std::endl;
    }
    if (i != -1 && i <= todos.size())
    {
        markDone(i - 1, !todos[i - 1].done);
    }
    setup();
    std::cout << divider << std::endl;
    mode = Mode::List;
}

int App::promptForAction()
{
    std::cout << "\033[1m\033[4mA\033[22m\033[24mdd, \033[1m\033[4mR\033[22m\033[24memove,  \033[1m\033[4mM\033[22m\033[24mark, "
                 "e\033[1m\033[4mX\033[22m\033[24mit > ";

    std::string s;
    std::getline(std::cin, s);
    if (s == "a" || s == "A")
    {
        return 1;
    }
    if (s == "r" || s == "R")
    {
        return 2;
    }
    if (s == "m" || s == "M")
    {
        return 3;
    }
    if (s == "x" || s == "X")
    {
        return 4;
    }
    int i;
    try
    {
        i = std::stoi(s);
    }
    catch (std::invalid_argument const &ex)
    {
        std::cout << "std::invalid_argument::what(): " << ex.what() << '\n';
    }
    catch (std::out_of_range const &ex)
    {
        std::cout << "std::out_of_range::what(): " << ex.what() << '\n';
    }
    return i;
}

void App::clear_screen() { std::cout << "\033[2J\033[H" << std::endl; }

void App::list()
{
    clear_screen();
    std::cout << divider << std::endl;
    size_t i{0};
    for (auto &todo : todos)
    {
        ++i;
        std::string s;
        if (todo.done)
            s = "X] ";
        else
            s = " ] ";
        std::cout << "[" << s << i << ". " << todo.todo << std::endl;
    }
    std::cout << divider << std::endl;
}

void App::remove(int id)
{
    SQLite::Statement st{dbm.db, "delete from todos where id = (?);"};
    st.bind(1, id);
    st.executeStep();
}
void App::add(std::string &content)
{
    SQLite::Statement st{dbm.db, "insert into todos (todo) VALUES (?);"};
    st.bind(1, content);
    st.executeStep();
    SQLite::Statement st2{dbm.db, "SELECT MAX(id) from todos;"};
    st2.executeStep();
    int maxId = st2.getColumn(0).getInt();
    todos.push_back(Todo{.id = maxId, .todo = content, .done = false});
}

void App::markDone(int id, bool done)
{
    std::cout << "got id = " << id << " and done = " << done << std::endl;
    SQLite::Statement st{dbm.db, "update todos set done = ? where id = ?;"};
    int dbDone = done ? 1 : 0;
    st.bind(1, dbDone);
    st.bind(2, todos[id].id);
    st.executeStep();
}

} // namespace gwr::todo
