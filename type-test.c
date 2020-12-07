#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "tstfunc.h"
#include "color.h"

int main(int argc, char const *argv[])
{
    init();

    int i = 0, idx, now, counter = 0;;
    char temp[100];
    struct t typing;

    mvprintw(2, 0, "> ");
    keypad(stdscr, TRUE);

    while(counter < 2){

        read_word();

        now = 0;
        idx = 0;

        move(0, 0);

        for(int i = 0; i < 8; i++)
            printw("%s ", word[i]);

        while(idx < 8){
            
            color_word(0, now, word[idx], BG_WHITE);

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

            if(!strcmp(temp, word[idx])){
                color_word(0, now, word[idx], BG_GREEN);
                typing.correct++;
            }
            else{
                color_word(0, now, word[idx], BG_RED);
                typing.wrong++;
            }

            now += strlen(word[idx]) + 1;

            free(word[idx]);
            word[idx] = 0;

            idx++;

            move(2, 0);
            
        }
        
        counter++;
        // cleanup();
        move(0, 0);
        clrtoeol();

    }
    
    clear();

    // show a result;

    result(typing.correct, typing.wrong);

    getch();

	refresh();
	endwin();

	return 0;
}
