#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <windows.h>
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
void signUp();
void changepass(char *filename,char* key);
void signIn();
void addPassword();
void retrievePassword();
void runnercode3(char *filename, char *key);
void changespecky(char *filename, char*key);
void delete(char *filename,char* key);

void tpass() {
    for(int i = 0; i<1999999999; i++) {
        printf("");
    }
}

void byn(char *str, int n) {
    int len = strlen(str);
    if (len > 0) {
        str[len - n] = '\0';
    }
}

char *getfile(int ln, char *filename, char *result) {
    char line[100];
    int count = 1;
    FILE *fp;
    fp = fopen(filename, "r");
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
    byn(result,1);
    return result;
}

void runnercode() {
    system("cls");
    int option;
    printf("\nSelect an option:\n");
 printf("\n1. Sign Up\n");
        printf("2. Sign In\n");
        printf("3. Exit\n");
        printf("Option: ");
        scanf("%d", &option);
        getchar(); // consume newline character
        switch (option) {
            case 1:
                signUp();
                break;
            case 2:
                signIn();
                break;
            case 3:
                printf("Exiting...\n");
                printf("\n***Thank You***\n");
                exit(0);
                break;
            default:
                printf("Invalid option. Please try again.\n");
                runnercode();
        }
} 

void encrypt(char password[]) {
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

  int n = strlen(password);
  for(int i = 0; i<n; i++) {
    int p = 0;
    for(int j = 0; j<yum; j++) {
      if (i%yum == *(lock + j)) {
        p = j;
      }
    *(password + i) = *(password + i) + *(key + p+1);
    }
  }
}

void decrypt(char encrypted[]) {
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
  int n = strlen(encrypted);
  for(int i = 0; i<n; i++) {
    int p = 0;
    for(int j = 0; j<yum; j++) {
      if (i%yum == *(lock + j)) {
        p = j;
      }
    *(encrypted + i) = *(encrypted + i) - *(key + p+1);
    }
  }
}

int strength(char p[])
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

int search(char *filename, char *website,char *key) {
    system("cls");
    int count = 1;
    int flag = 0;
    char line[20];
    char web[25] = "W:";
    strcat(web,website);
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 0;
    }
    while (fgets(line, sizeof(line), fp)) {
        byn(line,1);
        if (strcmp(line, web) == 0) { 
            flag += 1;
            printf("Found the website. (nvalue = %d)\n",count);
            char username[20];
            decrypt(getfile(count+1,filename,username));
            printf("Username:");
            puts(username);
            printf("\n");
        }
    count++;
    }
    fclose(fp);
    if (flag == 0) {
        printf("Not Found.\n");
        return 0;
        tpass();
        runnercode3(filename,key);
    }
    else{
        return 1;
    }
}

void delete(char *filename,char* key) {
    char replace[20][20];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    int read = 0;
    int lnn = 0;
    while (1)
    {
        read = fscanf(fp,"%s", replace[lnn]);
        if (read == EOF)
        {
            break;
        }
        lnn++;
    }
    fclose(fp);
    char del[20];
    printf("Enter website name:");
    fgets(del,20,stdin);
    del[strcspn(del,"\n")]  = '\0';
    int d = search(filename,del,key);
    if (d==0) {
        tpass();
        runnercode3(filename,key);
    }
    else {
    FILE*fpp = fopen(filename,"w");
    int l;
    printf("Enter nvalue:");
    scanf("%d",&l);
    getchar();
    int k=0;
    while(1){
        if(k+1==l){
            strcpy(replace[k],"numnumnumnum");
        }
        fprintf(fpp,"%s\n",replace[k]);
         if(k==lnn-1){
            break;
        }
        k++;
    }
    fclose(fpp);
    printf("Successfully deleted.");
    tpass();
    runnercode3(filename,key);
}
return;
}

void changepass(char *filename, char*key) {
    char replace[20][20];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    int read = 0;
    int lnn = 0;
    while (1)
    {
        read = fscanf(fp,"%s", replace[lnn]);
        if (read == EOF)
        {
            break;
        }
        lnn++;
    }
    fclose(fp);
    printf("Enter old password:");
    char op[20];
    fgets(op,20,stdin);
    char pss[20];
    strcpy(pss,replace[1]);
    decrypt(pss);
    op[strcspn(op,"\n")]  = '\0';
    if (strcmp(op, pss)==0) {
        char np[20];
    printf("Enter new password :");
    fgets(np,20,stdin);
    np[strcspn(np,"\n")]  = '\0';
    encrypt(np);
    FILE*fpp = fopen(filename,"w");
    int k=0;
    while(1){
        if(k+1==2){
            strcpy(replace[k],np);
        }
        fprintf(fpp,"%s\n",replace[k]);
         if(k==lnn-1){
            break;
        }
        k++;
    }
    fclose(fpp);
    printf("Password successfully updated. Log in again.");
    tpass();
    runnercode();
}
else {
    printf("Wrong Password. Please try again.");
    tpass();
    runnercode3(filename,key);
}
return;
}

void changespecky(char *filename, char* key) {
    char replace[20][20];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    int read = 0;
    int lnn = 0;
    while (1)
    {
        read = fscanf(fp,"%s", replace[lnn]);
        if (read == EOF)
        {
            break;
        }
        lnn++;
    }
    fclose(fp);
    printf("Enter old special key:");
    char okey[20];
    fgets(okey,20,stdin);
    okey[strcspn(okey,"\n")]  = '\0';
    if (strcmp(okey, key)==0) {
        char newkey[20];
    printf("Enter new special key for retreiving passwords:");
    fgets(newkey,20,stdin);
    newkey[strcspn(newkey,"\n")]  = '\0';
    encrypt(newkey);
    FILE*fpp = fopen(filename,"w");
    int k=0;
    while(1){
        if(k+1==3){
            strcpy(replace[k],newkey);
        }
        fprintf(fpp,"%s\n",replace[k]);
         if(k==lnn-1){
            break;
        }
        k++;
    }
    fclose(fpp);
    printf("special key successfully updated. Log in again.");
    tpass();
    runnercode();
}
else {
    printf("Wrong Key. Please try again.");
    tpass();
    runnercode3(filename,key);
}
return;
}

void runnercode2(char *filename, char *key){
    system("cls");
    printf("\n1. Retrieve password\n2. Add Password\n3. Main Menu\n4. Sign Out\n5. Exit\n");
        int option;
        printf("Option:");
        scanf("%d",&option);
        getchar();
        system("cls");
        switch (option) {
            case 1:
                retrievePassword(filename,key);
                break;
            case 2:
                addPassword(filename,key);
                break;
            case 3:
                runnercode3(filename,key);
                break;
            case 4:
                signIn();
                break;
            case 5:
                runnercode();
                break;
            default:
                printf("Invalid option. Please try again.\n");
                runnercode2(filename,key);
        }
}   
void runnercode3(char *filename, char* key) { 
    system("cls");
    int option;
    printf("\nSelect an option:\n");
    printf("1. Retrieve Password\n");
    printf("2. Add Password\n");
    printf("3. Change Password\n");
    printf("4. Change speckey\n");
    printf("5. Delete Entry\n");
    printf("6. Back\n");
    printf("Option: ");
    scanf("%d", &option);
    getchar(); // consume newline character
    system("cls");
    switch (option) {
        case 1:
            retrievePassword(filename,key);
            break;
        case 2:
            addPassword(filename,key);
            break;
        case 3:
            changepass(filename,key);
            break;
        case 4:
            changespecky(filename,key);
            break;
        case 5:
            delete(filename,key);
            break;
        case 6:
            printf("Going back...\n");
            runnercode();
            break;
        default:
            printf("Invalid option. Please try again.\n");
            runnercode3(filename,key);
    }
}

// Function for generating a random password
void getPass(char *password) {
    int size;
    printf("Enter size of the password:");
    scanf("%d",&size);
    getchar();
    srand(time(NULL));
    //characters to choose from for the password
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$^&*()+'-,.";
    for (int i = 0; i < size; i++) {
        int index = rand() % (sizeof(charset) - 1);
        *(password + i) = charset[index];
    }
}

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char spckey[20];
};
struct User masterUser;
void addPassword(char *filename, char*key) {
    char website[MAX_USERNAME_LENGTH];
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    system("cls");

    printf("=== Add Password ===\n");

    // Get website name
    printf("Enter website name (use only lowercase): ");
    fgets(website, sizeof(website), stdin);
    website[strcspn(website, "\n")] = '\0'; // remove trailing newline

    // Get username
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // remove trailing newline

    // Get password
    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // remove trailing newline
    int n;
    printf("Strength of your password is: %d/5\nDo you want to save it?\n1. Yes\n2. Generate for me\n3. Try again\n4. Back\n", strength(password));
    printf("Enter:");
    scanf("%d",&n);
    getchar(); 
    if (n==1) {
    // Encrypt the password
    encrypt(password);
    encrypt(username);

    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    // Write website name, username, and encrypted password to the file
    fprintf(file, "W:%s\n", website);
    fprintf(file, "%s\n", username);
    fprintf(file, "%s\n", password);
    fclose(file);
    printf("Password added successfully!\n");
    runnercode2(filename,key);
    }
    else if (n==2) {
        strcpy(password,"");
        getPass(password);
        printf("Your Password: ");
        puts(password);
        printf("\n1. Save\n2. Try Again\n");
        int m;
        printf("Enter:");
        scanf("%d",&m);
        getchar();
        if(m==1) {
            // Encrypt the password
            encrypt(password);
            encrypt(username);
            FILE* file = fopen(filename, "a");
            if (file == NULL) {
            printf("Error opening file!\n");
            return;
            }
            // Write website name, username, and encrypted password to the file
            fprintf(file, "W:%s\n", website);
            fprintf(file, "%s\n", username);
            fprintf(file, "%s\n", password);
            fclose(file);
            printf("Password added successfully!\n");
            runnercode2(filename,key);
        }
        else {
            addPassword(filename,key);
        }
    }
    else if (n==3) {
        addPassword(filename,key);
    }
    else {
        runnercode2(filename,key);
    }
}
void retrievePassword(char *filename,char*key) {
    char website[MAX_USERNAME_LENGTH];
    char specialKey[MAX_PASSWORD_LENGTH];
    system("cls");

    printf("\n=== Retrieve Password ===\n");

    // Get the special key from the user
    printf("Enter the special key: ");
    fgets(specialKey, sizeof(specialKey), stdin);
    specialKey[strcspn(specialKey, "\n")] = '\0'; // remove trailing newline

    // Check if the special key is correct
    if (strcmp(specialKey, key) != 0) {
        printf("Invalid special key. Access denied.\n");
        runnercode();
    }
    else {
    printf("Enter website name: ");
    fgets(website, sizeof(website), stdin);
    website[strcspn(website, "\n")] = '\0'; // remove trailing newline
    }
    int d = search(filename,website,key);
    if (d == 1){
        printf("Enter the indicated nvalue:");
        int m;
        scanf("%d",&m);
        char pass[20];
        getfile(m+2,filename,pass);
        decrypt(pass);
        printf("Password: ");
        puts(pass);
        int x;
        printf("\nPress 1 to leave this page\n");
        scanf("%d",&x);
        if (x==1) {
            runnercode2(filename,key);
        }
    }
}
void signUp() {
    struct User newUser;
    system("cls");
    printf("\n=== Sign Up ===\n");
    printf("Enter master username: ");
    fgets(newUser.username, sizeof(newUser.username), stdin);
    newUser.username[strcspn(newUser.username, "\n")] = '\0'; // remove trailing newline
    char lame[20];
    strcpy(lame,newUser.username);
    if(strcmp(lame,"")==0) {
        runnercode();
    }
    char *file = strcat(lame,".txt");
    if (access(file, F_OK) != -1) {
        printf("Username Exist. Choose another\n");
        signUp();
    }
    else{
        printf("Enter master password: ");
        fgets(newUser.password, sizeof(newUser.password), stdin);
        newUser.password[strcspn(newUser.password, "\n")] = '\0'; // remove trailing newline
        printf("Strength of your password is: %d/5\nDo you want to save it?\n1. Yes\n2. Try Again\n", strength(newUser.password));
        int n;
        printf("Enter:");
        scanf("%d",&n);
        getchar();
        if (n==1) {
            // adding special key
            printf("Enter your special key for retreiving passwords: ");
            fgets(newUser.spckey, sizeof(newUser.spckey), stdin);
            newUser.spckey[strcspn(newUser.spckey, "\n")] = '\0'; // remove trailing newline
            // Create a new file for the user
            char filename[MAX_USERNAME_LENGTH + 4]; // 4 is for ".txt" and null terminator
            snprintf(filename, sizeof(filename), "%s.txt", newUser.username);
            FILE* file = fopen(filename, "w");
            if (file == NULL) {
                printf("Error creating file!\n");
                return;
            }
            encrypt(newUser.username);
            encrypt(newUser.password);
            encrypt(newUser.spckey);
            fprintf(file, "%s\n", newUser.username);
            fprintf(file, "%s\n", newUser.password);
            fprintf(file, "%s\n", newUser.spckey);
            fclose(file);
            printf("Sign up successful!\n", filename);
            runnercode();
        }
        else{
         signUp();
        }
    }
}

void signIn() {
    struct User inputUser;
    int match = 0;
    system("cls");

    printf("\n=== Sign In ===\n");

    printf("Enter master username: ");
    fgets(inputUser.username, sizeof(inputUser.username), stdin);
    inputUser.username[strcspn(inputUser.username, "\n")] = '\0'; // remove trailing newline

    printf("Enter master password: ");
    fgets(inputUser.password, sizeof(inputUser.password), stdin);
    inputUser.password[strcspn(inputUser.password, "\n")] = '\0'; // remove trailing newline
    char filename[MAX_USERNAME_LENGTH + 4]; // 4 is for ".txt" and null terminator
    // Open the user's file for verification
    snprintf(filename, sizeof(filename), "%s.txt", inputUser.username);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("User does not exist.\n");
        tpass();
        runnercode();
        return;
    }
    fclose(file);
    struct User masterUser;
    
    getfile(1,filename,masterUser.username);
    getfile(2,filename,masterUser.password);
    getfile(3,filename,masterUser.spckey);

        decrypt(masterUser.username);
        decrypt(masterUser.password);
        decrypt(masterUser.spckey);

    if (strcmp(masterUser.username, inputUser.username) == 0 && strcmp(masterUser.password, inputUser.password) == 0) {
        match = 1;
    }

    if (match) {
        printf("Sign in successful!\n");
        tpass();
        runnercode3(filename,masterUser.spckey);
    }
    else {
        printf("Wrong master username or password. Please try again.\n");
        tpass();
        runnercode();
    }
}

int main() {
    printf("\n\n\n\n\n\t\t\t\t\t\t*** Welcome to Pass Hub ***\n");
    printf("\n\n\n\n");
    printf("\n\t\t\t\t\t\t     **");
    Sleep(400);
    printf(")(");
    Sleep(400);
    printf("()");
    Sleep(400);
    printf(")(");
    Sleep(400);
    printf("()");
    Sleep(400);
    printf(")(");
    Sleep(400);
    printf("()");
    Sleep(400);
    printf(")(");
    Sleep(400);
    printf("**");
    tpass();
    runnercode();
    return 0;
}
