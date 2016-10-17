#include<stdio.h>
#define STACK_INIT_SIZE 50
#define STACKINCREMENT 10
#define OK 1
#define FALSE 0
#define OVERFLOW -1
#define TRUE 1
#define ERROR 0

typedef struct{
    int *top;
    int *base;
    int stacksize;
}SqStack;
int InitStack(SqStack *S){
    S->base=(int *)malloc(STACK_INIT_SIZE*sizeof(int));
    if(!S->base)exit(OVERFLOW);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}
int Push(SqStack *S,int e){
    if(S->top-S->base>=S->stacksize){
        S->base=(int *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(int));
        if(!S->base)exit(OVERFLOW);
        S->top=S->base+S->stacksize;
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++=e;
    return OK;
}
int Pop(SqStack *S,int *e){
    if(S->top==S->base)return FALSE;
    *e=*--S->top;
    return OK;
}
int GetTop(SqStack S){
    if(S.base==S.top)return FALSE;
    int e=*(S.top-1);
    return e;
}
int In(int *c,int *OP){
    int i;
    OP=(int *)malloc(7*sizeof(int));
    OP[0]='+';
    OP[1]='-';
    OP[2]='*';
    OP[3]='/';
    OP[4]='(';
    OP[5]=')';
    OP[6]='#';
    for(i=0;i<7;i++)
        if(*c==OP[i])
            return OK;
    *c-='0';
    return FALSE;
}
int Precede(int m,int n){
    if(m=='+'){
        if(n=='*'||n=='/'||n=='(')
           return '<';
        else return '>';
    }
    if(m=='-'){
        if(n=='*'||n=='/'||n=='(')
           return '<';
        else return '>';
    }
    if(m=='*'){
        if(n=='(')
            return '<';
        else return '>';
    }
    if(m=='/'){
        if(n=='(')
            return '<';
        else return '>';
    }
    if(m=='('){
        if(n==')')
            return '=';
        else return '<';
    }
    if(m==')'){
        return '>';
    }
    if(m=='#'){
        if(n=='#')return '=';
        else return '<';
    }
}
int Operate(int a,int theta,int b){
    switch(theta){
        case '+':return a+b;break;
        case '-':return a-b;break;
        case '*':return a*b;break;
        case '/':return a/b;break;
        default:return FALSE;
    }
}
int main(){
    int higher,a,b,c,x,thera,*OP;
    SqStack OPTR,OPND;
    InitStack(&OPTR);
    InitStack(&OPND);
    Push(&OPTR,'#');
    printf("请输入表达式并在结尾加‘#’结束\n");
    c=getchar();
    while(c!='#'||GetTop(OPTR)!='#'){
        if(!In(&c,OP)){
            higher=c;
            c=getchar();
            while(!In(&c,OP)){
                higher=higher*10+c;
                c=getchar();
            }

            Push(&OPND,higher);
        }
        else{
            switch(Precede(GetTop(OPTR),c)){
                case '<':Push(&OPTR,c);c=getchar();break;
                case '=':Pop(&OPTR,&x);c=getchar();break;
                case '>':Pop(&OPTR,&thera);Pop(&OPND,&b);Pop(&OPND,&a);Push(&OPND,Operate(a,thera,b));break;
            }
        }
    }
    printf("%d\n",GetTop(OPND));
    return 0;
}
