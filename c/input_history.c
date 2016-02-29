/*
 * input_history.c
 *
 * 模拟 bash readline 库实现历史命令存储
 *
 * Compile:
 *      gcc -g `pkg-config --cflags ncurses` -o input_history.c \
 *      `pkg-config --libs ncurses`
 */
#include <stdio.h>
#include <string.h>
#include <ncurses/ncurses.h>

#define WIDTH 40
#define HEIGHT 10 

int startx = 0;
int starty = 0;

char str[256];
char history_str[20][256];

int main()
{   WINDOW *input_win;
    int c;
    char *ptr = str;
    char *tmp;
    str[0] = '\0';
    int i, j, k, n;
    i = 0; j = 0; k = 0;
    n = 0;

    initscr();
    clear();
    noecho();
    cbreak();   /* Line buffering disabled. pass on everything */
    startx = 0;
    starty = 0;
        
    input_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(input_win, TRUE);
    refresh();
    while(1)
    {   c = wgetch(input_win);
        switch(c)
        {   case KEY_UP:
                k = k - 1 < 0 ? 0 : k - 1;
                ptr = str;
                while (*ptr != '\0') {
                    *ptr = ' ';
                    ptr++;
                }
                mvprintw(0, 0, str);
                strcpy(str, history_str[k]);
                mvprintw(0, 0, str);
                refresh();
                ptr = str + strlen(str);
                j = strlen(str);
                break;

            case KEY_DOWN:
                ptr = str;
                while (*ptr != '\0') {
                    *ptr = ' ';
                    ptr++;
                }
                mvprintw(0, 0, str);
                k = k + 1 > i ? i: k+1;
                strcpy(str, history_str[k]);
                mvprintw(0, 0, str);
                refresh();
                ptr = str + strlen(str);
                j = strlen(str);
                break;

            case KEY_LEFT:
                if (j > 0) {
                    j--;
                    move(0, j);
                        refresh();
                }
                break;
            case KEY_RIGHT:
                n = strlen(str);
                if (j < n) {
                    j++;
                    move(0, j);
                        refresh();
                }
                break;

            //case KEY_BREAK:
            //    break;
            case KEY_DC:
            case KEY_BACKSPACE:
                if (j != 0) {
                    tmp = str + j - 1;
                    while (*tmp != 0) {
                        *tmp = *(tmp + 1);
                        tmp++;
                    }
                    j--;
                    n = strlen(str);
                    mvprintw(0, 0, str);
                    mvprintw(0, n, " ");
                    move(0, j);
                    refresh();
                }
                break;
            case '\t':
                break;
            case 10: // \n
                if (str[0] == '\0') break;
                strcpy(history_str[i], str);
                ptr = str;
                while (*ptr != '\0') {
                    *ptr = ' ';
                    ptr++;
                }
                i++;
                k = i;
                mvprintw(0, 0, str);
                j = 0;
                move(0, j);
                refresh();
                str[0] = '\0';
                ptr = str;
                break;
            default:
                n = strlen(str);
                tmp = str + n + 1;
                n = n - j + 1;
                *tmp = '\0';
                while (n != 0) {
                    *tmp  = * (tmp - 1);
                    tmp--;
                    n--;
                }
                k = i;
                j++;
                *tmp = c;
                mvprintw(0, 0, str);
                move(0, j);
                refresh();
                strcpy(history_str[i], str);
                break;
            case 27: // ESC
                goto ret;
        }
    }   
ret:
    clrtoeol();
    refresh();
    endwin();
    return 0;
}
