#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"

char *word[10];

void read_word(){
    FILE* fp, *random;
    random = fopen("/dev/urandom", "r");
    unsigned short int number;
    char numstr[5], file_open[20];

    for(int i = 0; i < 8; i++){

        number = getc(random) % 3;
        number = (number << 8) + getc(random);

        sprintf(numstr, "%d", number);
        sprintf(file_open, "%c", '\x00');

        strcat(file_open, "dict/");
        strcat(file_open, numstr);
        strcat(file_open, ".txt");

        fp = fopen(file_open, "r");

        word[i] = malloc(0x10);
        fscanf(fp, "%s", word[i]);

        fclose(fp);

    }

    fclose(random);
}

void init(){
    initscr();
    raw();
    noecho();
    cbreak();

    start_color();
    // init_pair(kode, warna_huruf, warna_bg)
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);

    read_word();
}

void color_word(int y, int x, char* s, int color){
    attron(color);
    mvprintw(y, x, "%s", s);        
    attroff(color);
}

void backspace(int i){
    move(2, 2 + i);
    delch();
}

void cleanup(){
    for(int i = 0;i < 8; i++){
        free(word[i]);
        word[i] = 0;
    }
}

void result(int correct, int wrong){
    char statement[20];

    mvprintw(0, 0, "+------------------------+");

    sprintf(statement, " correct words: %d", correct);
    color_word(1, 0, statement, GREEN);
    sprintf(statement, " wrong words: %d", wrong);
    color_word(2, 0, statement, RED);
    sprintf(statement, " accuracy: %.2f%%", correct*1.0/(correct+wrong) * 100);
    color_word(3, 0, statement, WHITE);

    mvprintw(4, 0, "+------------------------+");
}
