#include <stdio.h>
#include <ncurses.h>

int main(int argc, char **argv)
{
    // initializes curses function, sets up memory and clears the screen
    initscr();
    // cbreak() makes ctrl-C exit your program. This is the default 
    // behavior. Useful to exit your program while testing
    //cbreak();
    // raw() puts any character, including ctrl-C.
    //raw();
    // noecho() whatever input the user types doesn't shows up in the screen.
    // noecho() is more useful than raw() or cmode()
    noecho();

    int height, width, start_y, start_x;
    height = 10;
    width = 20;
    start_y = start_x = 10;

    // newwin() creates new window
    WINDOW *win = newwin(height, width, start_y, start_x);
    refresh(); // screen knows that we created a new window

    //box() boxes a window
    box(win, 103, 104);
    wrefresh(win);
    getch();

    char c = '/';
    box(win, c, c);
    wprintw(win, "---------");
    mvwprintw(win, 5, 12, "this is my box");
    wrefresh(win);
    getch();

    int left, right, top, bottom, tlc, trc, blc, brc;
    left= right= top= bottom= tlc= trc= blc= brc='/';
    wborder(win, left, right, top, bottom, tlc, trc, blc, brc);
    wrefresh(win);

    getch();

    endwin();

    return 0;
}

