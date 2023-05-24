#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct a
{
   char website[30];
   char userid[30];
   char password[15];
}a1;

void decrypt(char *p)
{
  for(int i=0;i<strlen(p);i++)
  {
    *(p+i)-=4;
  }
  printf("%s",p);
}

void search(struct a a1)
{
   FILE *file = fopen("password.txt", "r");
    printf("enter website to be searched: ");
char str[30];
scanf("%d",str);  
    char buffer[256];
    char next_line[256] = ""; 
    int line_num = 1;
    while(fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        if (strstr(buffer, str) != NULL)
         {
          
          
            printf("%s", buffer);
             
           
        }
        strcpy(next_line, buffer); 
        line_num++;
        if(line_num==4)
        break;
    }
    
    fclose(file);
} 

int main()
{
    int n;
    printf("enter 1 to add password");
    printf("\nenter 2 to retrive password\n");
    printf("enter 3 to exit\n");
    scanf("%d",&n);

    if(n==2)
    {
       search(a1);
    }

   if(n==3)
   {
    return 0;
   }
}