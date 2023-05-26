#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt(char password[],int lock[],int key[], int y) {
    int n = strlen(password);
    for(int i = 0; i<n; i++) {
        int p = 0;
        for(int j = 0; j<y; j++) {
            if (i%y == *(lock + j)) {
                p = j;
            }
            *(password + i) = *(password + i) + *(key + p+1);
        }
    }
}

void decrypt(char encrypted[],int lock[],int key[],int y) {
    int n = strlen(encrypted);
    for(int i = 0; i<n; i++) {
        int p = 0;
        for(int j = 0; j<y; j++) {
            if (i%y == *(lock + j)) {
                p = j;
            }
            *(encrypted + i) = *(encrypted + i) - *(key + p+1);
        }
    }
}
char *getfile(int ln, char *filename, char *result) {
    char line[100];
    int count = 1;
    char lame[20];
    strcpy(lame,filename);
    char*file = strcat(lame,".txt");
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    while (fgets(line, sizeof(line), fp)) {
        if (count == ln) {
            strcpy(result, line);
            break;
        }
        count++;
    }
    fclose(fp);
    return result;
}

void main() {
    int yum;
    FILE *loki = fopen("loki.txt", "r");
    if (loki == NULL) {
        printf("File not found.\n");
        exit(1);
    }
    else {
        int num;
        while (fscanf(loki, "%d", &num)==1) {
            yum = num;
        }
    } 
    int key[yum + 1],lock[yum];
    FILE *pri = fopen("lockey.txt", "r");
    if (pri == NULL) {
        printf("File not found.\n");
        exit(1);
    }
    else {
        int num, i=0;
        while (fscanf(pri, "%d", &num)==1) {
            key[i++]= num;
        }
    }
    
    int i = 0,j = key[0];
    while(i<yum) {
        lock[i++] = j%10;
        j/=10;
    }
    
    char password[100];
    
    printf("Give:");
    
    fgets(password,100,stdin);
    encrypt(password,lock,key,yum);
    puts(password);
    
    printf("\n");
    
    FILE *fp;
    
    fp=fopen("password.txt","w");
    
    fprintf(fp,"%s",password);
    
    fclose(fp);

    char encryp1[100];
    FILE *kll = fopen("password.txt", "r");
    if (loki == NULL) {
        printf("File not found.\n");
        exit(1);
    }
    else {
        fgets(encryp1,100,fp);
        }
    fclose(fp);    
    puts(encryp1);
    decrypt(encryp1,lock,key,yum);
    puts(encryp1);
    char result[100];
    char filename[] = "ram07";
    getfile(1,filename,result);
    decrypt(result,lock,key,yum);
    puts(result);
}