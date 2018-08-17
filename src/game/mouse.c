#include <stdio.h>
#include <unistd.h> // sleep(), usleep()
#include <time.h> // nanosleep()
#include <sys/ioctl.h> // winsize, TIOCGWINSZ
#include <string.h>
#include <wchar.h> // wint_t
#define BUFSIZE 100

int main (int argc, char **argv)
{

    char c;

    /*
    while ((c=getchar())!=EOF) {
        if (c==97)
            write(1,"you typed 'a'",13);
        else if (c=='b')
            write(1,"you typed 'b'",13);
        else
            write(1,&c,1);
    }
    */

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int pos=0;
    int width=w.ws_col-2;
    char buff[width+1];
    memset(buff,'_',sizeof(buff));
    buff[pos]='a';

    /*
    strncpy(buff,getpass("Password: "),5);
    printf("%s\n",buff);
    */

    /*
    while (1) {
        strncpy(&c,getpass("\r"),1);
        if (c=='.')
            return 0;
        printf("%c\r",c);
    }
    */

    /* move the 'a' around by typing 'h+Enter' or 'l+Enter'*/
    printf("%s\r",buff);
    while ((c=getchar())!=EOF) {
        if (c=='h') { // move 'a' to the left
            if (pos==0) {
                pos=width;
                buff[pos]='a';
                buff[0]='_';
            } else {
                pos--;
                buff[pos]='a';
                buff[pos+1]='_';
            }
        } else if (c=='l') { // move 'a' to the right
            if (pos==width) {
                pos=0;
                buff[pos]='a';
                buff[width]='_';
            } else {
                pos++;
                buff[pos]='a';
                buff[pos-1]='_';
            }
        }
        printf("%s\r",buff);
        fflush(stdout);
    }

    /* move the 'a' suppressing user input with getpass() so/6856635
     * todo: getchar() read arrow keys instead of h,l so/10463201
    printf("%s\r",buff);
    while (1) {
        strncpy(&c,getpass("\r"),1);
        if (c=='.')
            break;
        if (c=='h') { // move 'a' to the left
            if (pos==0) {
                pos=width;
                buff[pos]='a';
                buff[0]='_';
            } else {
                pos--;
                buff[pos]='a';
                buff[pos+1]='_';
            }
        } else if (c=='l') { // move 'a' to the right
            if (pos==width) {
                pos=0;
                buff[pos]='a';
                buff[width]='_';
            } else {
                pos++;
                buff[pos]='a';
                buff[pos-1]='_';
            }
        }
        printf("%s\r",buff);
        fflush(stdout);
    }
    */


    /* avoid pressing enter with getchar() so/1798511
    // use system call to make terminal send all keystrokes to stdin
    system ("/bin/stty raw");
    while((c=getchar())!= '.')
        putchar(c); // type a period to break out of the loop, 
                    // since CTRL-D won't work raw
    // use system call to set a more normal terminal behaviour
    system ("/bin/stty cooked");
    */

}
