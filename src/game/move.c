#include <stdio.h>
#include <ncurses.h>
#include <string.h> // strcpy()

#define NKEYS (sizeof story / sizeof story[0])

void start_ncurses(bool useRaw, bool useNoecho);

int main(int argc, char **argv)
{

    struct textAnimation {
        char text[128];
        int size;
    } story[]={
"It is a period of civil war. Rebel spaceships, striking from a hidden\n\n",70,
" base, have won their first victory against the evil Galactic Empire.\n\n",70,
" During the battle, Rebel spies managed to steal secret plans to the\n\n",69,
" Empire's ultimate weapon, the DEATH STAR, an armored space station\n\n",68,
" with enough power to destroy an entire planet.  Pursued by the\n\n",64,
" Empire's sinister agents, Princess Leia races home aboard her\n\n",63,
" starship, custodian of the stolen plans that can save her people and\n\n",70,
" restore freedom to the galaxy....                                   \n\n",70
    };

    struct textAnimation *p;
    p=story;

    /* this print works nicely
    for (p = story; p < story + NKEYS; p++)
        if (p->size > 0)
            printf("%4d %s\n", p->size, p->text);
    return 0;
    */

    start_ncurses(false, true);

    int height, width;
    getmaxyx(stdscr, height, width);

    WINDOW *menuwin1 = newwin(8, width-6, height-9, 3);
    box(menuwin1, 0, 0);
    refresh();
    printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tSTAR WARS MOVIE\n");
    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    printf("press any key to read story (q exits)\n");
    wrefresh(menuwin1);

    WINDOW *menuwinInvisible = newwin(6, width-10, height-8, 5);
    int left, right, top, bottom, tlc, trc, blc, brc;
    left= right= top= bottom= tlc= trc= blc= brc=' ';
    wborder(menuwinInvisible, left, right, top, bottom, tlc, trc, blc, brc);

    for (; p < story + NKEYS - 1;) {
        if (p->size > 0) {
            wmove(menuwinInvisible,2,0);
            wprintw(menuwinInvisible,p++->text);
            wprintw(menuwinInvisible,p->text);
            wrefresh(menuwinInvisible);
            if (getch()=='q') break;
        }
    }


    /*
    strcpy(p->text,p->text+p->size);
    mvwprintw(menuwinInvisible,1,1,p->text);
    wrefresh(menuwin1);
    wrefresh(menuwinInvisible);
    getch();
    */

    // to center a window use this formula as argument of newwin():
    // (xoffset*2, yoffset*2, height/2-xoffsed, width/2-yoffset)
    WINDOW *menuwin = newwin(16, 32, height/2-8, width/2-16);
    box(menuwin, 0, 0);
    wrefresh(menuwin);
    // makes it so we can use arrow keys
    keypad(menuwin, true);

    /*
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
    */


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
