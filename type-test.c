#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "tstfunc.h"

int main(int argc, char const *argv[])
{
    init();

    int i = 0, idx, now;
    char temp[100];


    mvprintw(2, 0, "> ");
    keypad(stdscr, TRUE);

    while(1){

        read_word();

        now = 0;
        idx = 0;

        move(0, 0);

        for(int i = 0; i < 8; i++)
            printw("%s ", word[i]);

        while(idx < 8){
            
            color_word(0, now, word[idx], WAIT);

            move(2, 2);

            while(' '  != (temp[i] = getch())){

                if(temp[i] ==  7 && i > 0)
                    backspace(--i);
                else if(temp[i] > 0x20 && temp[i] < 0x7f)
                    addch(temp[i++]);

            };

            temp[i] = '\0';
            i = 0;

            move(2, 2);
            clrtoeol();

            if(!strcmp(temp, word[idx]))
                color_word(0, now, word[idx], CORRECT);
            else
                color_word(0, now, word[idx], WRONG);

            now += strlen(word[idx]) + 1;

            free(word[idx]);
            word[idx] = 0;

            idx++;

            move(2, 0);
            
        }

        // cleanup();
        move(0, 0);
        clrtoeol();

    }

	refresh();
	endwin();

	return 0;
}
