#define CORRECT COLOR_PAIR(1)
#define WRONG COLOR_PAIR(2)
#define WAIT COLOR_PAIR(3)

extern void init(void); 
extern void color_word(int y, int x, char *s, int color);
extern void read_word();
extern void backspace(int i);
extern void cleanup(void);
extern char* word[10];

