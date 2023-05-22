#include<stdio.h>
#include<string.h>
int strength(const char *p)
{
   int a=0,b=0,c=0,d=0;
   for(int i=0;i<strlen(p);i++)
   {
    if(*(p+i)>='A' && *(p+i)<='Z')
    a=1;
    else if(*(p+i)>='a' && *(p+i)<='z')
    b=1;
    else if(*(p+i)>='0' && *(p+i)<='9')
    c=1;
    else
    d=1;
   }
      
   return a+b+c+d+1;
}
int main()
{
    char p[20];
    printf("enter characters in password: ");
    scanf("%s",p);
   printf("strength of password is %d/5",strength(p));
   return 0;  
}