#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int password;
    int sign;
    struct Node *next;
}People;

int main()
{
    People *p,*p1,*q1;
    int n,m,k=0,i=0,counts=1;
    int Output[30];
    printf("请输入人数、初始报数上限：\n");
    scanf("%d,%d",&n,&m);
    p=p1=(People *)malloc(sizeof(struct Node));
    printf("请输入第%d人的密码：\n",i+1);
    scanf("%d",&p1->password);
    p1->sign=1;
    for(i=1;i<n;i++){
        q1=p1;
        p1=(People *)malloc(sizeof(struct Node));
        q1->next=p1;
        printf("请输入第%d人的密码：\n",i+1);
        scanf("%d",&p1->password);
        p1->sign=i+1;
    }
    p1->next=p;

    while(p!=p->next){
        if(counts==m){
            k++;
            q1=p->next;
            p1->next=q1;
            m=p->password;
            Output[k]=p->sign;
            free(p);
            p=q1;
            counts=1;
        }
        else{
            p1=p;
            p=p->next;
            counts++;
        }
    }
    Output[n]=p->sign;
    for(i=1;i<=n;i++){
        printf("%d,",Output[i]);
    }
    return 0;
}
