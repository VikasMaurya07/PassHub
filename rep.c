#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void replace(){
    char replace[20][20];
    FILE *ou = fopen("ram07.txt", "r");
    int kk = 0;
    int zeo = 0;
    while (1)
    {
        kk = fscanf(ou,"%s", replace[zeo]);
        zeo++;
        if (kk == EOF)
        {
            break;
        }
    }
    fclose(ou);
    char id[40];
    fflush(stdin);
    FILE*mou=fopen("ram07.txt","w");
    int ln;
    printf("Enter ln:");
    scanf("%d",&ln);
    int k=0;
    while(1){
        if(k+1==ln){
            strcpy(replace[k],"numnumnumnum");
        }
        fprintf(mou,"%s\n",replace[k]);
         if(k==zeo){
            break;
        }
        k++;
       

    }
    fclose(mou);
}

int main() {
    replace();
    return 0;
}