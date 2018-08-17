#include <ncurses.h>
#include <string>
#include <cstdlib>
#include "player.h"
using namespace std;

void start_ncurses(bool useRaw, bool useNoecho);

int main(int argc, char **argv)
{

    start_ncurses(false, true);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // create a window for our input
    WINDOW * playwin = newwin(20, 50, (yMax/2)-10, 10);
    box(playwin, 0, 0);
    refresh();
    wrefresh(playwin);

    Player *p = new Player(playwin, 1, 1, '@');
    do {
        p->display();
        wrefresh(playwin);
    } while(p->getmv()!='x');

    endwin();
    /* NCURSES END */

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
