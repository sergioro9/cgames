#include <stdio.h>
#include <ncurses.h>
#include <string.h>

void start_ncurses(bool useRaw, bool useNoecho);
void printMenu(WINDOW * menu, char **choices[], int size, int highlight);

int main(int argc, char **argv)
{
    start_ncurses(false, true);

    int y, x, yBeg, xBeg, yMax, xMax;

    getyx(stdscr, y, x);
    getbegyx(stdscr, yBeg, xBeg);
    getmaxyx(stdscr, yMax, xMax);
    printw("%d %d %d %d %d %d\n", y, x, yBeg, xBeg, yMax, xMax);
    getch();

    // put message at the center of the screen
    mvprintw(yMax/2, xMax/2, "Hello\n");
    getch();

    WINDOW *win = newwin(10, 20, 10, 10);

    getyx(stdscr, y, x);
    getbegyx(win, yBeg, xBeg);
    getmaxyx(stdscr, yMax, xMax);
    printw("%d %d %d %d %d %d\n", y, x, yBeg, xBeg, yMax, xMax);
    getch();

    mvprintw(yMax/2, xMax/2, "%d %d", yBeg, xBeg);
    getch();

//    mvprintw(yMax/2, xMax/2, %d %d", yBeg, xBeg);


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

/*
void printMenu(WINDOW * menu, char *choices[], int size, int highlight)
{
    WINDOW *win = newwin(height, width, start_y, start_x);
}
    */
