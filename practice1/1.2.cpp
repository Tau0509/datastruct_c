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
bool check(char *str)
{
    //在这里补全代码
    /****begin*****/
    int flag=1,i=0;
    char temchar;
    sqstack tem;
    initstack(tem);
    while(flag&&str[i]){
        if(str[i]=='('||str[i]=='{'||str[i]=='['){
            push(tem,str[i]);
        }else if(str[i]==')'||str[i]=='}'||str[i]==']'){
            pop(tem,temchar);
            switch (str[i]) {
                case ')': {
                    if(temchar!='(') flag=0;
                    break;
                }
                case '}': {
                    if(temchar!='{') flag=0;
                    break;
                }
                case ']': {
                    if(temchar!='[') flag=0;
                    break;
                }
            }
        }
    }
    if(!isempty(tem)) flag=0;
    if(flag) return true;
    else return false;
    /****end******/
}
void initstack(sqstack &S){
    S.top=-1;
}

bool push(sqstack &S,char x){
    if(S.top==MAXSIZE-1)
        return false;
    S.data[++S.top]=x;
    return true;
}

bool pop(sqstack &S,char &x){
    if(S.top==-1)
        return false;
    x=S.data[S.top--];
    return true;
}

bool isempty(sqstack S) {
    if(S.top==-1)
        return true;
    else
        return false;
}


int main(){
    char str[50];
    scanf("%s",str);
    if(check(str))
        printf("匹配成功\n");
    else
        printf("匹配失败\n");
}
