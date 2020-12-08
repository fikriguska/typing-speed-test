extern void init(void); 
extern void color_word(int y, int x, char *s, int color);
extern void read_word();
extern void backspace(int i);
extern void cleanup(void);
// extern void result(int correct, int wrong);
extern char* word[10];

struct t{
    unsigned int correct;
    unsigned int wrong;
};
