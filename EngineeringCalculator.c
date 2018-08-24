#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
//-----------------------------------------------------------------------------

//global variables
int p=0;//counter for output
char output[100][100];
float numberstack[100];
int nsp=0;//number stack pointer
float eps=0.0001;

//----------------------------------------------------------------------------

long int factorial(int m)
{
    if (m==0 || m==1)
        return (1);
    else
        return (m*factorial(m-1));
}

//----------------------------------------------------------------------------

float sincos(float x,int i)//i=1 for sin and i=0 for cos
{
    int n;
    float val=0;
    for (n=i;n<10;n=n+2)
    {
        float q = pow(-1,n);
        float px = pow(x,n);
        long fac = factorial(n);
        val += q * px / fac;
    }
    //printf("%f",val);
    return val;
}

//----------------------------------------------------------------------------

int op(char x,char y)//operator or operand
{
    int i;
    int j=0;
    int t=(int)x;
    int r=(int)y;
    if(t>=48 && t<=57)
        i=1;//x is a number
    else
    if(t==80 || t==69 || t==101 || t==112)
        i=1;//x=pi or x=e
    else
    if(t==45 && r>=48 && r<=57)
        i=1;//number<0
    else
        i=0;//x is not a number
        return i;
}

//-----------------------------------------------------------------------------

int point(char x)
{
    int i;
    switch(x)
    {
        case '+':
            i=3;
            break;
        case '-':
            i=3;
            break;
        case '*':
            i=4;
            break;
        case '/':
            i=4;
            break;
        case '^':
            i=5;
            break;
        case '(':
            i=8;
            break;
        case ')':
            i=6;
            break;
        default:
            i=7;
    }
    return i;
}

//----------------------------------------------------------------------------

int pointb(char x)//in stack
{
    int i;
    switch(x)
    {
        case '+':
            i=3;
            break;
        case '-':
            i=3;
            break;
        case '*':
            i=4;
            break;
        case '/':
            i=4;
            break;
        case '^':
            i=5;
            break;
        case '(':
            i=0;
            break;
        case ')':
            i=6;
            break;
        default:
            i=7;
    }
    return i;
}

//---------------------------------------------------------------------------

float cast(int n)
{
 int i,j;
 int temp;//for .
 float x=0;
 char y;
 int t;
 //printf("%c",output[n][0]);
 if(n==p-2)
    {t=strlen(output[n])-1;}
 else
    {t=strlen(output[n]);}
    //printf("%d\n",t);
    for(i=0;i<t;i++)
    {
        if(output[n][i]=='.')
        {
            {
                temp=i;
                break;
            }
        }
        else
        {
            temp=t;
        }
    }
    for(i=0;i<temp;i++)
    {
        y=output[n][i];
        //printf("%c\n",y);
        x=x*10+((int)y-'0');
    }
    for(i=t-1;i>temp;i--)
    {
        y=output[n][i];
        x=x+(((int)y-'0')*pow(10,-1*i+temp));
    }
    //printf("%f\n",x);
    return x;
}

//---------------------------------------------------------------------------

float solve()
{
    int i,j;
    float op1,op2;
    float x,y;
    float convert;
    char temp;
    char m;
    float u;
    for(i=0;i<p;i++)
    {
        if(op(output[i][0],output[i][1])==1)
        {
            if(strcmp(output[i],"p")==0 || strcmp(output[i],"P")==0)
                {numberstack[nsp]=3.141592;
                 //printf("%f",numberstack[nsp]);
                 //p = check!
                 nsp++;}
            else
            if(strcmp(output[i],"e")==0 || strcmp(output[i],"E")==0)
                {numberstack[nsp]=2.718281;
                nsp++;}
            else
            {
                convert=cast(i);
                numberstack[nsp]=convert;
                //printf("%f\n",cast(i));
                //printf("\n%f\n",numberstack[nsp]);
                nsp++;
                //convert to float number = check!
            }
        }
        else
        if(op(output[i][0],output[i][1])==0 && point(output[i][0])!=7)//not a number and not a function(an operator)
        {
            temp=output[i][0];
            op2=numberstack[nsp-1];
            op1=numberstack[nsp-2];
            //printf("%f\n",op2);
            nsp=nsp-2;
            switch(temp)
            {
            case '+'://check!
                numberstack[nsp]=op1+op2;
                nsp++;
                break;
            case '-':
                numberstack[nsp]=op1-op2;
                nsp++;
                break;
            case '*':
                numberstack[nsp]=op1*op2;
                nsp++;
                break;
            case '/':
                if(op2==0)
                {
                    printf("error!");
                    exit(1);
                }
                else
                {
                    numberstack[nsp]=op1/op2;
                    nsp++;
                }
                break;
            case '^':
                numberstack[nsp]=pow(op1,op2);
                nsp++;
                break;
            }
        }
        else
        if(op(output[i][0],output[i][0])==0 && point(output[i][0])==7)//function
        {
            op1=numberstack[nsp-1];
            /*if(o)==0)
            {
                printf("\nsyntax error!");
                exit(1);
            }*/
            //printf("\n%f",op1);
            nsp--;
            if(strcmp(output[i],"sin")==0)
            {
                //numberstack[nsp]=sincos(op1,1);
                numberstack[nsp]=sin(op1);
                //printf("%f",sin(op1));
                nsp++;
            }
            else
            if(strcmp(output[i],"cos")==0)
            {
                //numberstack[nsp]=sincos(op1,0);
                numberstack[nsp]=cos(op1);
                nsp++;
            }
            else
            if(strcmp(output[i],"tan")==0)
            {
                //x=sincos(op1,1);
                //y=sincos(op1,0);
                x=sin(op1);
                y=cos(op1);
                if(y<eps)
                {
                    printf("error!");
                    exit(1);
                }
                else
                {
                    numberstack[nsp]=x/y;
                    nsp++;
                }
            }
            else
            if(strcmp(output[i],"cot")==0)
            {
                //x=sincos(op1,1);
                //y=sincos(op1,0);
                x=cos(op1);
                y=sin(op1);
                if(x<eps)
                {
                    printf("error!");
                    exit(1);
                }
                else
                {
                    numberstack[nsp]=y/x;
                    nsp++;
                }
            }
            else
            if(strcmp(output[i],"sec")==0)
            {
                //x=sincos(op1,0);
                x=cos(op1);
                if(x<eps)
                {
                    printf("error!");
                    exit(1);
                }
                else
                {
                    numberstack[nsp]=1/x;
                    nsp++;
                }
            }
             if(strcmp(output[i],"csc")==0)
            {
                //x=sincos(op1,1);
                x=sin(op1);
                //y=cos(op1);
                if(x<eps)
                {
                    printf("error!");
                    exit(1);
                }
                else
                {
                    numberstack[nsp]=1/x;
                    nsp++;
                }
            }
            else
            if(strcmp(output[i],"rexp")==0)
            {
                u=2.71;
                numberstack[nsp]=pow(u,op1);
                //printf("%f",op1);
                nsp++;
            }
            else
            if(strcmp(output[i],"ln")==0)
            {
                if(op1<=0)
                {
                    printf("\nerror!");
                    exit(1);
                }
                else
                {
                    numberstack[nsp]=log(op1);
                    nsp++;
                }
            }
            else
            if(strcmp(output[i],"log")==0)
            {
                x=log(op1);
                y=log(10);
                if(x<=0)
                {
                    printf("\nerror!");
                    exit(1);
                }
                else
                {
                  numberstack[nsp]=x/y;
                  nsp++;
                }

            }
            else
            if(strcmp(output[i],"sinh")==0)
            {
                numberstack[nsp]=sinh(op1);
                nsp++;
            }
            else
            if(strcmp(output[i],"cosh")==0)
            {
                numberstack[nsp]=cosh(op1);
                nsp++;
            }
            else
            if(strcmp(output[i],"tanh")==0)
            {
                x=sinh(op1);
                y=cosh(op1);
                if(y==0)
                {
                    printf("error!");
                    exit(1);
                }
                else
                {
                    numberstack[nsp]=x/y;
                    nsp++;
                }
            }
            else
            if(strcmp(output[i],"coth")==0)
            {
                x=sinh(op1);
                y=cosh(op1);
                if(x==0)
                {
                    printf("error!");
                    exit(1);
                }
                else
                {
                    numberstack[nsp]=y/x;
                    nsp++;
                }
            }
        }
    }
    printf("\n%f\n",numberstack[0]);
}

//-----------------------------------------------------------------------------------

int main()
{
    char c;
    char infix[100][100];
    char stack[100][100];
    int s=0;//counter for stack
    int i=0,j=0,t=1;//t=operand+operator==space+1
    int pnt;//operator's point
    int pntb;//last operand's point in stack
    int x;//counter
    int r=-1;//find (
    int answer;
    while(c!='\n')
    {
        c=getchar();
        if(c!=' ')
        {
            infix[i][j]=c;
            j++;
        }
        else
        if(c==' ')
        {
            i++;
            j=0;
            t++;
        }
    }
    //infix=check! :)
    for(i=0;i<t;i++)
    {
        j=0;
        if(op(infix[i][j],output[i][j+1])==1)
        {
            strcpy(output[p],infix[i]);
            p++;
        }
        else
        if(op(infix[i][j],output[i][j+1])==0)
        {
            pnt=point(infix[i][j]);
            if(s!=0)
            {pntb=pointb(stack[s-1][j]);}
            else
            pntb=-1;
            if(pnt>pntb && pnt!=6)
            {
                strcpy(stack[s],infix[i]);
                s++;
            }
            else
            if(pnt==6)
            {
                for(x=s-1;x>=0;x--)
                {
                    if(strcmp(stack[x],"(")==0)
                        {r=x;
                        break;}
                        //find ( =check!
                }
                if(r==-1)
                {
                    printf("\nmissing ( !");
                    exit(1);
                }
                for(x=s-1;x>=r+1;x--)
                {
                    strcpy(output[p],stack[x]);
                    p++;
                }
                s=r;//move stack pointer to the string "("
            }
            else
            if(pnt<=pntb)
            {
                for(x=s-1;x>=0;x--)
                {
                    if(point(infix[i][j])<=pointb(stack[x][0]))
                    {
                        strcpy(output[p],stack[x]);
                        p++;
                        s--;
                    }
                }
                strcpy(stack[s],infix[i]);
                s++;
            }
        }
    }
    for(i=s-1;i>=0;i--)
    {
        strcpy(output[p],stack[i]);
        p++;
    }
    /*for(i=0;i<p;i++)
    {
        printf("%s",output[i]);
    }*/
    //postfix = check!
    solve();
    return 0;
}

