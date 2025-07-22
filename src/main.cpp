#include "App.h"

int main(int argc, char *argv[])
{
    gwr::todo::App app;
    app.setup();
    std::string s;

    if (argc == 1)
        app.mode = gwr::todo::Mode::List;
    else if (argc == 2)
    { // got command?
        std::string cmd{argv[1]};
        if (cmd == "list")
            app.mode = gwr::todo::Mode::List;
    }
    else
    {
        for (int i = 1; i < argc; ++i)
        {
            s += argv[i] + std::string{" "};
        }
        app.add(s);
        app.mode = gwr::todo::Mode::List;
    }

    app.run();

    return 0;
}
