#include <stdio.h>
#include <stdlib.h> // rand(), getenv()
#include <string.h> // strlen()
#include <sys/ioctl.h> // struct winsize
#include <time.h> // time()
#include <unistd.h> // usleep()

void fillScreen(int height, int width, char *word);

int main(int argc, char **argv)
{
    useconds_t milisecs;
    milisecs = 500000;
    int i;
    char buffer[1024];
    char *string;

    /* writing a variable to a buffer
    string="hello";
    snprintf(buffer, sizeof(buffer), "%s, goodbye", string);
    printf(buffer);
    */

    /* print numbers in-place
    for (i=0;i<10;i++) {
        printf("%d\r",i);
        fflush(stdout);
        usleep(milisecs);
    }
    */

    /* print numbers in-place using write()
    for (i=0;i<10;i++) {
        snprintf(buffer, sizeof(buffer), "%d\r", i);
        write(1,buffer,strlen(buffer));
        //write(1, "    :-)\b\b\b\b\b\r",13);
        usleep(milisecs);
    }
    */

    /* same but more efficient
    for (i=0;i<10;i++) {
        int len = snprintf(buffer, sizeof(buffer), "%d\r", i);
        write(1,buffer,len);
        //write(1, "    :-)\b\b\b\b\b\r",13);
        usleep(milisecs);
    }
    */

    /* same but more efficient
    for (i=0;i<10;i++) {
        write(1,buffer,snprintf(buffer, sizeof(buffer), "%d\r", i));
        usleep(milisecs);
    }
    */

    /* print numbers changing-mood face
    for (i=0;i<10;i++) {
        if (i%3==0)
            string=":-)";
        else if (i%3==1)
            string=":-/";
        else
            string=":-(";
        snprintf(buffer, sizeof(buffer), "%s\r", string);
        write(1,buffer,strlen(buffer));
        //write(1, "    :-)\b\b\b\b\b\r",13);
        usleep(milisecs);
    }
    */

    /* print depending on terminal size (better to run in bash shell so
     * that you dont see the prompt) */
    struct winsize win;
    ioctl(0, TIOCGWINSZ, &win);
    int width = win.ws_row;
    int height = win.ws_col;
    char *list[3] = {"uno", "dos", "tres"};
    int randCol;
    int randRow;
    int randWord;
    int numWords;

    numWords = sizeof list / sizeof list[0];

    srand(time(NULL));

    for (;;) {
        randCol=(int)(height*(float)rand()/RAND_MAX);
        randRow=(int)(width*(float)rand()/RAND_MAX);
        randWord=(int)(numWords*(float)rand()/RAND_MAX);
        fillScreen(height, width, list[randWord]);
    }

    //printf("%d\n",randCol);
    //printf("%d\n",randRow);
    //printf("%s\n",list[randWord]);

    /*
    setenv("PS1","hello>",1);
    */

    return 0;
}

void fillScreen(int height, int width, char *word)
{
    char screen[height*width-40*width];
    char buffer[1024];
    memset(screen, '_', sizeof(screen));
    memcpy(screen+8,word,strlen(word));
    printf("%s\n", screen);
    getchar();

    /*
    while
    system("clear");
    printf("aaaaaaaaaaaaaaaaa\n"
           "bbbbbbbbbbbbbbbbb\n"
           "ccccccccccccccccc\n"
           "ddddddddddddddddd\n\r");
    sleep(1);
    system("clear");
    printf("bbbbbbbbbbbbbbbbb\n"
           "aaaaaaaaaaaaaaaaa\n"
           "ddddddddddddddddd\n"
           "ccccccccccccccccc\n\r");
   */
}
