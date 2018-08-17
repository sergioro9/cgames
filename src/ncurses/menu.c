#include <stdio.h>
#include <ncurses.h>

void start_ncurses(bool useRaw, bool useNoecho);

int main(int argc, char **argv)
{
    start_ncurses(false, true);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW *menuwin = newwin(6, xMax-12, yMax-8, 5);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);

    // makes it so we can use arrow keys
    keypad(menuwin, true);

    char *choices[3] = {"Walk", "Log", "Run"};
    int nchoices = sizeof choices / sizeof choices[0];
    int choice;
    int highlight = 0;
    while (1) {
        for (int i = 0; i < 3; i++)
        {
            if (i == highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, 1, "%s",choices[i]);
            wattroff(menuwin, A_REVERSE);
        }
        choice = wgetch(menuwin);
        switch(choice)
        {
            case KEY_UP:
                highlight--;
                if (highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == nchoices)
                    highlight = nchoices-1;
                break;
            default:
                break;
        }
        if (choice == 10)
            break;
    }

    printw("Your choice was: %s", choices[highlight]);
    getch();

    endwin();
    return 0;
}

void start_ncurses(bool useRaw, bool useNoecho)
{
    initscr();
    if (useRaw)
        raw();
    else
        cbreak();
    if (useNoecho)
        noecho();
}
