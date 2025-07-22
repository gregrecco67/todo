#include "DbManager.h"

namespace gwr::todo
{

DbManager::DbManager(std::string dbFilename) : db(dbFilename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    try
    {
        db.exec("CREATE TABLE IF NOT EXISTS todos (id INTEGER PRIMARY KEY AUTOINCREMENT, todo TEXT, done INT DEFAULT 0);");

        SQLite::Statement st{db, "SELECT COUNT(*) FROM todos WHERE (todo = 'make a todo list');"};
        st.executeStep();
        if (st.getColumn(0).getInt() == 0)
            db.exec("INSERT INTO todos (todo, done) VALUES ('make a todo list', 1);");

        SQLite::Statement st2{db, "SELECT COUNT(*) FROM todos WHERE (todo = 'add some todos');"};
        st2.executeStep();
        if (st2.getColumn(0).getInt() == 0)
            db.exec("INSERT INTO todos (todo) VALUES ('add some todos');");
    }
    catch (std::exception &e)
    {
        std::cout << "Got exception: " << e.what() << std::endl;
    }
}

} // namespace gwr::todo
