#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#define MAX 50

typedef struct stack
{
    int data[MAX];
    int top;
}stack;

int precedence(char);
void init(stack *);
int empty(stack *);
int full(stack *);
int pop(stack *);
void push(stack *,int);
int top(stack *);
void infix_to_postfix(char infix[],char postfix[]);

int main()
{
    char a;
do{
        printf("��JQ���}�Υ��N��}�l\n");
        scanf(" %c",&a);
        if(a=='q'||a=='Q')
        return 0;

    char infix[30],postfix[30];
    printf("���m�����m��+�p��\n");
    printf("�`�N!�ȭ���J�Ӧ��!!\n\n\n");

    printf("�п�J���m�B�⦡: ");
    scanf("%s",&infix);
    infix_to_postfix(infix,postfix);
    printf("\n���m�����m����X��: %s\n",postfix);

    printf("�B�⦡�ҭp��X�Ӫ��Ȭ�: %d\n" , evaluate(postfix));

   memset(infix,'\0',30);
   memset(postfix,'\0',30);



}while(a!='q'||a!='Q');
}

int stack_int[25];                                    /*�p��B�⦡���ȡA���]�@�Ӱ}�C�M��Ϋ��Ы����m������m�A���۶}�l�P�_�M��B��C*/
int top_int = -1;

void push_int(int item) {
   stack_int[++top_int] = item;
}

char pop_int() {
   return stack_int[top_int--];
}


int evaluate(char *postfix){

   char ch;
   int i = 0,operand1,operand2;

   while( (ch = postfix[i++]) != '\0') {

      if(isdigit(ch)) {
	     push_int(ch-'0');
      }else {
         operand2 = pop_int();
         operand1 = pop_int();

         switch(ch) {
            case '+':
               push_int(operand1+operand2);
               break;
            case '-':
               push_int(operand1-operand2);
               break;
            case '*':
               push_int(operand1*operand2);
               break;
            case '/':
               push_int(operand1/operand2);
               break;
               case '%':
               push_int(operand1%operand2);
               break;
         }
      }
   }

   return stack_int[top_int];
}



void infix_to_postfix(char infix[],char postfix[])           /*�ഫ���m���ܫ�m��*/
{
    stack s;
    char x,token;
    int i,j;
    init(&s);
    j=0;

    for(i=0;infix[i]!='\0';i++)
    {
        token=infix[i];
        if(isalnum(token))
            postfix[j++]=token;
        else
            if(token=='(')
               push(&s,'(');
        else
            if(token==')')
                while((x=pop(&s))!='(')
                      postfix[j++]=x;
                else
                {
                    while(precedence(token)<=precedence(top(&s))&&!empty(&s))
                    {
                        x=pop(&s);
                        postfix[j++]=x;
                    }
                    push(&s,token);
                }
    }

    while(!empty(&s))
    {
        x=pop(&s);
        postfix[j++]=x;
    }

    postfix[j]='\0';
}

int precedence(char x)          /*�P�_�B��Ȫ��u������*/
{
    if(x=='(')
        return(0);
    if(x=='+'||x=='-')
        return(1);
    if(x=='*'||x=='/'||x=='%')
        return(2);

    return(3);
}

void init(stack *s)                        /*�P�_�O�_���Ū�*/
{
    s->top=-1;
}

int empty(stack *s)
{
    if(s->top==-1)
        return(1);

    return(0);
}

int full(stack *s)
{
    if(s->top==MAX-1)
        return(1);

    return(0);
}

void push(stack *s,int x)
{
    s->top=s->top+1;
    s->data[s->top]=x;
}

int pop(stack *s)
{
    int x;
    x=s->data[s->top];
    s->top=s->top-1;
    return(x);
}

int top(stack *p)
{
    return (p->data[p->top]);
}
