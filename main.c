#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
void signUp();
void changepass(char *filename);
void signIn();
void addPassword();
void retrievePassword();
void changespecky(char *filename, char*newkey);
void delete(char *filename);

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
    int option;
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
void changespecky(char *filename, char*newkey) {

}

void delete(char *filename) {

}

void changepass(char *filename) {

}

int search(char *filename, char *website) {
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
            int i = count;
            printf("Found the website. (nvalue = %d)\n",count);
            char username[20];
            decrypt(getfile(i+1,filename,username));
            printf("Username:");
            puts(username);
            printf("\n");
        }
    count++;
    }
    fclose(fp);
    if (flag == 0) {
        printf("Not Found.");
        return 0;
    }
    else{
        return 1;
    }
}

void runnercode2(char *filename, char *key){
    printf("\n1. Retrieve password\n2. Add Password\n3. Sign Out\n4. Exit\n");
        int option;
        printf("Option:");
        scanf("%d",&option);
        switch (option) {
            case 1:
                retrievePassword(filename,key);
                break;
            case 2:
                addPassword(filename,key);
                break;
            case 3:
                signIn();
                break;
            case 4:
                runnercode();
                break;
            default:
                printf("Invalid option. Please try again.\n");
                runnercode2(filename,key);
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

    printf("=== Add Password ===\n");

    // Get website name
    printf("Enter website name: ");
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
    printf("Strength of your password is: %d/5\nDo you want to save it?\n1. Yes\n2. No\n", strength(password));
    printf("Enter:");
    scanf("%d",&n);
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
    else {
        runnercode2(filename,key);
    }
}
void retrievePassword(char *filename,char*key) {
    char website[MAX_USERNAME_LENGTH];
    char specialKey[MAX_PASSWORD_LENGTH];

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
    int d = search(filename,website);
    if(d==0) {
        runnercode2(filename,key);
    }
    else if (d == 1){
        printf("Enter the indicated nvalue:");
        int m;
        scanf("%d",&m);
        char pass[20];
        getfile(m+2,filename,pass);
        decrypt(pass);
        printf("Password: ");
        puts(pass);
        runnercode2(filename,key);
    }
}
void signUp() {
    struct User newUser;
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
}

void signIn() {
    struct User inputUser;
    int match = 0;

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
            switch (option) {
                case 1:
                    retrievePassword(filename,masterUser.spckey);
                    break;
                case 2:
                    addPassword(filename,masterUser.spckey);
                    break;
                case 3:
                    changepass(filename);
                    break;
                case 4:
                    changespecky(filename,masterUser.spckey);
                    break;
                case 5:
                    delete(filename);
                    break;
                case 6:
                    printf("Going back...\n");
                    runnercode();
                    break;
                default:
                    printf("Invalid option. Please try again.\n");
                    signIn();
            }
    }
    else {
        printf("Wrong master username or password. Please try again.\n");
    }
}

int main() {
    printf("\n***Welcome to Pass Hub***\n");
     printf("\nSelect an option:\n");
    runnercode();
    return 0;
}
