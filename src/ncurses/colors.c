#include <stdio.h>
#include <ncurses.h>

int main(int argc, char **argv)
{
    /* NCURsES START */
    //start_ncurses(true, true);
    initscr();
    noecho();

    /*
     * Possible attributes for attron():
     * A_NORMAL
     * A_STANDOUT
     * A_REVERSE
     * A_BLINK
     * A_DIM
     * A_BOLD
     * A_PROTECT
     * A_INVIS
     * A_ALTCHARSET
     * A_CHARTEXT
     */

    attron(A_REVERSE); // reverses bg color with fg color
    printw("This is some text\n");
    getch();
    attron(A_STANDOUT); // reverses bg color with fg color
    printw("This is some text\n");
    getch();
    attron(A_INVIS);
    printw("This is some text\n"); // make text invisible
    getch();
    attroff(A_INVIS);     // turns off
    attroff(A_STANDOUT);  // turns off
    attroff(A_REVERSE);   // turns off
    printw("This is some text\n");
    getch();

    if(!has_colors()) {
        printw("Terminal does not support color");
        getch();
        return -1;
    }
    start_color();

    /*
     * Color attributes for init_pair(), attron() etc
     * COLOR_PAIR(n)
     * COLOR_BLACK   0
     * COLOR_RED     1
     * COLOR_GREEN   2
     * COLOR_YELLOW  3
     * COLOR_BLUE    4
     * COLOR_MAGENTA 5
     * COLOR_CYAN    6
     * COLOR_WHITE   7
     */

    init_pair(1, COLOR_CYAN, COLOR_WHITE);
    init_pair(2, COLOR_YELLOW, COLOR_MAGENTA);

    attron(COLOR_PAIR(1));
    printw("This is some text\n");
    getch();
    attron(COLOR_PAIR(2));
    printw("This is some text\n");
    getch();

    attroff(COLOR_PAIR(1));
    attroff(COLOR_PAIR(1));

    if(can_change_color()) {
        printw("Can change color\n");
        init_color(COLOR_CYAN, 0-999, 0-999, 0-999);
        printw("This is some text\n");
    }

    getch();

    endwin();

    return 0;
}

