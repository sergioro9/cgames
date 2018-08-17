#include <stdio.h>
#include <ncurses.h>

int main(int argc, char **argv)
{
    // initializes curses function, sets up memory and clears the screen
    initscr();
    int x, y;
    x = y = 10;
    // moves the cursor to the specified location
    move(y, x);
    // prints a string(const char *) to a window
    printw("Hello World!");
    // whats for user input, returns int value of that key
    int c = getch();
    // refreshes the screen to match whats in memory (not really needed here)
    refresh();
    move(0, 0); printw("%d", c); // equivalent to mvprintw(0,0,"%d", c);
    // clears the screen
    clear();
    mvprintw(0,0,"%d", c);
    getch();
    // deallocatesw memory and ends ncurses
    endwin();
    return 0;
}

