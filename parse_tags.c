#include <stdlib.h>
#include <stdio.h>

// parse tags file for hightlighting user defined type.

int main(int argc, char*argv[])
{
    char buffer[256];
    int i;
    int f;
    int name_end;
    char type;
    while (fgets(buffer, 256, stdin)) {
        i = 0;
        if (buffer[i++] == '!')
            continue;

        f = 0;
        while (buffer[i] != '\t') {
            if (buffer[i] == ':') {
                f = 1;
                break;
            }
            i++;
        }

        if (f == 1) {
            continue;
        }

        name_end = i;
        while (buffer[i] != ';' || (buffer[i+1] != '"')) 
            i++;
        type = buffer[i + 3];
        if (type != 't') {
            continue;
        }

        //buffer[name_end + 1] = type;
        buffer[name_end] = '\n';
        buffer[name_end + 1] = '\0';

        fputs("syn keyword cType ",stdout);   
        fputs(buffer, stdout);
    }

    return 0;
}
            
