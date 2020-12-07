#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

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
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);

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
    for(int i = 0; i < 8; i++){
        free(word[i]);
        word[i] = 0;
    }
}
