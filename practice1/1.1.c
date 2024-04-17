#include<stdio.h>
#define MAXSIZE 30

typedef struct{
    char data[30];
    int top;
}sqstack;

void initstack(sqstack &S);
bool push(sqstack &S,char x);
bool pop(sqstack &S,char &x);
bool isempty(sqstack S);
bool check(char *str);