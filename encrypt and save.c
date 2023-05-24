#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct a
{
   char website[30];
   char userid[30];
   char password[15];
}a1;

char *encrypt(char *p)
{
  for(int i=0;i<strlen(p);i++)
  {
    *(p+i)+=4;
  }
  return p;
}

void encryption(char *password,char *website,char *userid)
{
  FILE *ptr=fopen("password.txt","a");
  char *s=encrypt(password);
  fprintf(ptr,"website: %s\n",website);
  fprintf(ptr,"user id: %s\n",userid);
  fprintf(ptr,"%s\n\n",password);
  fclose(ptr);
} 

int main()
{
    int n;
    printf("enter 1 to add password");
    printf("\nenter 2 to retrive password\n");
    printf("enter 3 to exit\n");
    scanf("%d",&n);

    if(n==1)
    {
     
          printf("enter website: ");
          scanf("%s",&a1.website);
          printf("enter userid: ");
          scanf("%s",&a1.userid);
          printf("enter password: ");
          scanf("%s",&a1.password);
          encryption(a1.password,a1.website,a1.userid);
          printf("\n\n");
          main();
    
    }

}