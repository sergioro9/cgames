/* 
 * so/1022957
 */

#include <stdio.h>
#include <unistd.h> // sleep(), usleep()
#include <time.h> // nanosleep()
#include <sys/ioctl.h> // winsize, TIOCGWINSZ
#include <string.h>
#include <wchar.h> // wint_t
#include <locale.h>

int main (int argc, char **argv)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    /*
    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
    */

    char buf[w.ws_col];
    memset(buf,'_',sizeof(buf));
    buf[0]='a';

    /*
    memmove(buf,"_",1);
    printf ("%s\n%ld\n%ld\n",buf,sizeof(buf), strlen(buf));
    */

    /*
    for (int i=0;i<sizeof(buf);i++) {
        printf("%c",buf[i]);
        fflush(stdout);
        sleep(1);
    }
    */

    /* print with no scroll so/408965 using time interval so/7684359*/
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 100000000L;
    for (int i=0;i<sizeof(buf);i++) {
        printf("%s\r",buf);
        fflush(stdout);
        nanosleep(&tim, &tim2);
//        nanosleep((struct timespec[]){{0,100000000L}}, NULL); // also works
        buf[i]='_';
        buf[i+1]='a';
    }
    

    char buf1[w.ws_col];
    char buf2[w.ws_col];
    memset(buf1,'_',sizeof(buf1));
    memset(buf2,'_',sizeof(buf2));
    buf1[0]='a';
    buf2[0]='b';

    char buff[w.ws_col*w.ws_row];
    memset(buff,'_',sizeof(buff));

    /* not working
    wchar_t buff[w.ws_col*w.ws_row];
    memset(buff,'█',sizeof(buff));
    */

    /*
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 100000000L;
    for (int i=0;i<w.ws_col;i++) {
        printf("%s\n%s\r",buf1,buf2);
        fflush(stdout);
        nanosleep(&tim, &tim2);
        buff[i]='_';
        buff[i+1]='a';
    }
    */

    /* print ascii table
    for (int i = 32; i < 256;i++)
        printf("%3d / %02x = %c%s", i, i, i, ((i >> 2) << 2 == i) ? "\n\r" : "\t");
    */

    /*
    setlocale(LC_ALL, ""); // needed to print unicode
    printf("%lc\n",(wint_t)9608);
    printf("%s",buff);
    */


    return 0;
}
