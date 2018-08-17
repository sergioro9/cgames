/* Compile with:
 *     gcc -Wall -Wextra -g $(pkg-config --cflags ncurses) pong.c $(pkg-config --libs ncurses) -o pong
 *     https://gist.github.com/Zoi4i/090e6cccae50d59962c0#file-pong-c
 * Sources used:
 *     https://github.com/vicentebolea/Pong-curses
*/

#include <ncurses.h>
#include <string.h>
#include <time.h>

 static int ROW,COL;
 int main(int argc, char *argv[]) {

 initscr();
 keypad(stdscr, TRUE);
 noecho();
 cbreak();
 curs_set(0);

    	srand((unsigned)time(0));
    	getmaxyx(stdscr,ROW,COL);

 int ball(int y,int x,int flag); 		// ball
 int paddle(int y,int x,int flag);		// paddle
 void field();                           		// field
    int l_y = ROW / 2 - 2;
    int l_x = 2;
    int r_y = ROW / 2 - 2;
    int r_x = COL - 4;   
    int ball_y = ROW / 2;
    int ball_x;

 start_color();

     	field();
	paddle(l_y,l_x,1);
	paddle(r_y,r_x,1);

 char mesg1[]="A, Z, UP, DOWN - paddle UP-DOWN";
 char mesg2[]="Q, ESC - QUIT GAME, P - PAUSE";
 char mesg3[]="<-Press Any Key->";
 char mesg4[]="Left player won!";
 char mesg5[]="Right player won!";

 init_pair(1, COLOR_RED, COLOR_BLACK);
 attron(COLOR_PAIR(1));
 attron(A_BOLD);

    	mvprintw(ROW/2-8,(COL-strlen(mesg1))/2,"%s",mesg1);
    	mvprintw(ROW/2-7,(COL-strlen(mesg2))/2,"%s",mesg2);

 attron(A_BLINK);

    	mvprintw(ROW/2-3,(COL-strlen(mesg3))/2,"%s",mesg3);

 attroff(A_BLINK);
 attroff(A_BOLD);
 attroff(COLOR_PAIR(1));


 typedef struct
	{
	 short int x, y, c; 
	 bool mov_H, mov_V;
	} object;
	object scr; int i,cont=0; bool fin=FALSE;
	object

 ball1={COL-2,ROW/2,0,FALSE,FALSE},
 ball2={1,ROW/2,0,FALSE,FALSE},
 b={COL/2,ROW/2,0,FALSE,FALSE};

	getch();

	for (nodelay(stdscr,1); !fin; usleep(4000)) {
		if (++cont%16==0){
			if ((b.y==ROW-1)||(b.y==1)) 
				b.mov_V=!b.mov_V;
			if ((b.x>=COL-2)||(b.x<=2)){
				b.mov_H=!b.mov_H;
				if ((b.y==ball1.y-1)||(b.y==ball2.y-1)) {
					b.mov_V=FALSE;
        } else if ((b.y==ball1.y+1)||(b.y==ball2.y+1)) {
					b.mov_V=true;
				} else if ((b.y != ball1.y) && (b.y != ball2.y)) {
          (b.x>=COL-2) ? ball1.c++: ball2.c++; 
					b.x=COL/2; 
					b.y=ROW/2;
				}
			}
			b.x=b.mov_H ? b.x+1 : b.x-1;
			b.y=b.mov_V ? b.y+1 : b.y-1;

			if (ball1.y<=1) 
				ball1.y=ROW-2;
			if (ball1.y>=ROW-1) 
				ball1.y=2;
			if (ball2.y<=1) 
				ball2.y=ROW-2; 
			if (ball2.y>=ROW-1) 
				ball2.y=2;
		}

		switch(getch()) {
		case 'q': case 'Q':  case 0x1B: 
			endwin();
			fin++;
			break;

		case 'a': case 'A':
			ball2.y--; 
			break;

		case 'z': case 'Z':
 			ball2.y++;
			break;

		case  KEY_UP:
			ball1.y--;
			break;

		case  KEY_DOWN:
			ball1.y++;
			break;

		case  'p':
			getchar();
			break;
			}

		erase();

	if (ball1.c <10)
		mvprintw(2,COL/2-3,"%i | %i",ball1.c,ball2.c);
	else 
		mvprintw(2,COL/2-4,"%i | %i",ball1.c,ball2.c);

		mvvline(0,COL/2-1,ACS_VLINE,ROW);
    		mvaddch(b.y,b.x-1,ACS_CKBOARD);
    		mvaddch(b.y,b.x,ACS_CKBOARD);
    			for(i=-2;i<3;i++){
     		mvaddch(ball1.y+i,ball1.x-1,ACS_CKBOARD);
     		mvaddch(ball1.y+i,ball1.x,ACS_CKBOARD);
      		mvaddch(ball2.y+i,ball2.x+1,ACS_CKBOARD);
      		mvaddch(ball2.y+i,ball2.x,ACS_CKBOARD);}

	}

 return 0;
}

//==============================================

 int ball(int y,int x,int flag){		// ball

 	if (flag == 0)
 		mvaddch(y,x,' '), mvaddch(y,x+1,' ');
	else if (flag == 1)
 		mvaddch(y,x,ACS_CKBOARD), 
		mvaddch(y,x+1,ACS_CKBOARD);

 return 0;
}
//==============================================

 int paddle(int y,int x,int flag){		// paddle
 
	int i;
	if (flag == 0)
		for(i = 0; i < 5; i++)
		ball(y + i,x,0);
	else if (flag == 1)
		for(i = 0; i < 5; i++)
		ball(y + i,x,1);
 return 0;
}
//==============================================

 void field(){					// field

	int i;
		for (i=0; i<=ROW; i++) 
		{
	 	 if (i%2==0) 
			ball(i,(COL/2-2),1);	// field separator
		}
}
//=============================================
