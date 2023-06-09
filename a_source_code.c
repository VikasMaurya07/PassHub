#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void signUp();
void signIn();
void addPassword();
void retrievePassword();
void runnercode();
void tpass();
void encrypt(char password[]);
void decrypt(char encrypted[]);
int strength(char p[]);
void changepass(char *filename,char* key);
void runnercode2(char *filename, char *key);
void runnercode3(char *filename, char *key);
void changespecky(char *filename, char*key);
void delete(char *filename,char* key);
void hpass(char* password);
void byn(char *str, int n);
char *getfile(int ln, char *filename, char *result);
int search(char *filename, char *website,char *key);
void delete(char *filename,char* key);
void changepass(char *filename, char*key);
void getPass(char *password);

void hpass(char* password) {  //  function reads characters from the user without displaying them, allowing the user to input a password securely
    char c; 
    int i = 0;
    while ((c = getch ()) != '\n' && c != '\r') // if enter key is pressed
    {
        if (c == '\b') //if backspace
        {
            if (i > 0) 
            {
                password[i-1] = '\0';// makes previous character null so it can be erased
                printf ("\b \b"); 
                i--;
            }
        }
        else // if not backspace
        {
            password[i] = c;
            printf ("*");
            i++;
        }
    }
    password[i] = '\0';
}

// to pass time, as sleep didn't function correctly
void tpass() { 
    for(int i = 0; i<1999999999; i++) {
        printf("");
    }
}

// to short a string by n characters
void byn(char *str, int n) { 
    int len = strlen(str);
    if (len > 0) {
        str[len - n] = '\0';
    }
}

// to get a line from the text file
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
            strcpy(result, line); // saving the string in the character array line[]
            break;
        }
        count++;
    }
    fclose(fp);
    byn(result,1); // shorting the obtained stringlength by 1
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

// to encrypt the text 
void encrypt(char password[]) {
    // to get encryptionn data from text files
     int yum; 
FILE *loki = fopen("loki.txt", "r");  // key is stored in loki.txt
    if (loki == NULL) {
        printf("File not found.\n");
        exit(1);
    }
    else {
      int num;
        while (fscanf(loki, "%d", &num)==1) {
            yum = num; // key value assigned to yum
        }
    } 
    int key[yum + 1],lock[yum];
FILE *pri = fopen("lockey.txt", "r"); // encryption keys are stored in lockey.txt
    if (pri == NULL) {
        printf("File not found.\n");
        exit(1);
    }
    else {
        int num, i=0;
        while (fscanf(pri, "%d", &num)==1) {
            key[i++]= num;  // key copied from lockey.txt and stored in key[]
        }
    }
    int i = 0,j = key[0];
    while(i<yum) {
      lock[i++] = j%10;
      j/=10;
    }
// to encrypt a text input
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

// to decrypt the text
void decrypt(char encrypted[]) {
    // to get encryptionn data from text files
     int yum;
FILE *loki = fopen("loki.txt", "r");   // key is stored in loki.txt
    if (loki == NULL) {
        printf("File not found.\n");
        exit(1);
    }
    else {
      int num;
        while (fscanf(loki, "%d", &num)==1) {
            yum = num;  // key value assigned to yum
        }
    } 
    int key[yum + 1],lock[yum];
FILE *pri = fopen("lockey.txt", "r");  // encryption keys are stored in lockey.txt
    if (pri == NULL) {
        printf("File not found.\n");
        exit(1);
    }
    else {
        int num, i=0;
        while (fscanf(pri, "%d", &num)==1) {
            key[i++]= num;  // key copied from lockey.txt and stored in key[]
        }
    }
    int i = 0,j = key[0];
    while(i<yum) {
      lock[i++] = j%10;
      j/=10;
    }
  // to decrypt encrypted text input 
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

// function to find strength of the entered password
int strength(char p[])
{
   int a=0,b=0,c=0,d=0;
   for(int i=0;i<strlen(p);i++)
   {
    if(*(p+i)>='A' && *(p+i)<='Z') // one point awarded if uppercase letters are present
    a=1;
    else if(*(p+i)>='a' && *(p+i)<='z') // one point awarded if lowercase letters are present
    b=1;
    else if(*(p+i)>='0' && *(p+i)<='9') // one point awarded numbers are present
    c=1;
    else
    d=1;
   }
      
   return a+b+c+d+1; 
}

// to search for a website in user's text file
int search(char *filename, char *website,char *key) {
    system("cls"); // command to clear the whole screen
    int count = 1; 
    int flag = 0;
    char line[50];
    char web[25] = "W:"; 
    strcat(web,website); // to search for a website string W: website
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n"); // if user file not found
        return 0;
    }
    while (fgets(line, sizeof(line), fp)) { 
        byn(line,1); // removing the null character for proper comparison
        if (strcmp(line, web) == 0) {  // if website is found
            flag += 1;
            printf("Found the website. (nvalue = %d)\n",count);
            char username[50]; 
            // getting and decrypting the username
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
        return count;
    }
}

// to delete a website entry in user text file
void delete(char *filename,char* key) {
    char replace[50][50];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    int read = 0;
    int lnn = 0;
    while (1)
    { 
        // copying the user file to a two dimensional character arrray
        read = fscanf(fp,"%s", replace[lnn]); 
        if (read == EOF)
        {
            break;
        }
        lnn++;
    }
    fclose(fp); // closing the text file
    char del[50];
    printf("Enter website name:"); // to get the website name to be deleted 
    fgets(del,50,stdin);
    del[strcspn(del,"\n")]  = '\0';
    for (int i = 0; del[i] != '\0'; i++) {
        del[i] = tolower(del[i]); // converting the input to lowecase
    }
    int d = search(filename,del,key); // calling the search function to search for the input in the text file
    if (d==0) { // if input not found
        tpass();
        runnercode3(filename,key);
    }
    else {  // if found
    FILE*fpp = fopen(filename,"w");
    int l;
    printf("Enter nvalue (else enter some large value >200 to terminate):");
    scanf("%d",&l);  // to get the indicated nvalue for deleting the specific portion
    getchar(); 
    int k=0;
    while(1){
        if(k+1==l){
            strcpy(replace[k],"numnumnumnum"); // replacing the website name in the text file with a meaningless string
        }
        fprintf(fpp,"%s\n",replace[k]);
         if(k==lnn-1){  // reprinting the whole text file after editing
            break;
        }
        k++;
    }
    fclose(fpp);
    if(l<200) {
    printf("Successfully deleted.");
    tpass();
    runnercode3(filename,key);
    }
    else {
        runnercode3(filename,key);
    }
}
return;
}

// a function to change the user password
void changepass(char *filename, char*key) {
    char replace[50][50];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    int read = 0;
    int lnn = 0;
    while (1)
    {   // copying the user file to a two dimensional character arrray
        read = fscanf(fp,"%s", replace[lnn]);
        if (read == EOF)
        {
            break;
        }
        lnn++;
    }
    fclose(fp);
    printf("Enter old password:"); // to get the old password
    char op[50];
    hpass(op);
    char pss[50];
    strcpy(pss,replace[1]);
    decrypt(pss);
    op[strcspn(op,"\n")]  = '\0';
    if (strcmp(op, pss)==0) { // if entered input matches old password
        char np[50];
    printf("\nEnter new password:");
    hpass(np); // function for secure input of password // getting  a new password
    np[strcspn(np,"\n")]  = '\0';
    if(strcmp(np,"")==0) { // if no new password is entered
        runnercode3(filename,key);
    }
    // strength check of password
    printf("\n\nStrength of your password is: %d/5\nDo you want to save it?\n1. Yes\n2. Try Again\n", strength(np));
        int n;
        printf("Enter:");
        scanf("%d",&n);
        getchar();
    // if user wants to go with his entered password    
    if(n==1) {
    encrypt(np); // encrypting new password
    FILE*fpp = fopen(filename,"w");
    int k=0;
    while(1){
        if(k+1==2){
            strcpy(replace[k],np); // saving the new password in the second line of the user text file 
        }
        fprintf(fpp,"%s\n",replace[k]); // reprinting the whole text file
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
        changepass(filename,key);
    }
}
else {
    printf("Wrong Password. Please try again.");
    tpass();
    runnercode3(filename,key);
}
return;
}

// function to change the special key
void changespecky(char *filename, char* key) {
    char replace[50][50];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    int read = 0;
    int lnn = 0;
    while (1)
    {
        read = fscanf(fp,"%s", replace[lnn]); // getting the text file in an array
        if (read == EOF)
        {
            break;
        }
        lnn++;
    }
    fclose(fp); 
    printf("Enter old special key:");
    char okey[50];
    fgets(okey,50,stdin); // to get old soecial key
    okey[strcspn(okey,"\n")]  = '\0';
    if (strcmp(okey, key)==0) {  // if old special key matches the input
        char newkey[50];
    printf("Enter new special key for retreiving passwords:");
    fgets(newkey,50,stdin);
    newkey[strcspn(newkey,"\n")]  = '\0';
    if(strcmp(newkey,"")==0) { // if no input is found
        runnercode3(filename,key);
    }
    encrypt(newkey); // to encrypt newkey 
    FILE*fpp = fopen(filename,"w");
    int k=0;
    while(1){
        if(k+1==3){
            strcpy(replace[k],newkey); // saving the newkey in the third line of the text file
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
    char spckey[50];
};
struct User masterUser;

void addPassword(char *filename, char*key) {
    char website[MAX_USERNAME_LENGTH];
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    system("cls");

    printf("=== Add Password ===\n");

    // Get website name
    printf("Enter website name: ");
    fgets(website, sizeof(website), stdin);
    for (int i = 0; website[i] != '\0'; i++) {
        website[i] = tolower(website[i]);
    }
    website[strcspn(website, "\n")] = '\0'; // remove trailing newline

    // Get username
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // remove trailing newline

    // Get password
    printf("Enter password: ");
    hpass(password);
    password[strcspn(password, "\n")] = '\0'; // remove trailing newline
    int n;
    printf("\nStrength of your password is: %d/5\nDo you want to save it?\n1. Yes\n2. Generate for me\n3. Try again\n4. Back\n", strength(password));
    printf("\nEnter:");
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
    for (int i = 0; website[i] != '\0'; i++) {
        website[i] = tolower(website[i]);
    }
    website[strcspn(website, "\n")] = '\0'; // remove trailing newline
    }
    if(strcmp(website,"")==0) {
        runnercode2(filename,key);
    }
    int d = search(filename,website,key);
    if (d != 0){
        printf("Enter the indicated nvalue (else enter a value >= 200):");
        int m;
        scanf("%d",&m);
        getchar();
        if (m<=d) {
            char pass[50];
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
        else {
            runnercode2(filename,key);
        }
    }
    else {
        printf("Try Again.");
        tpass();
        runnercode2(filename,key);
    }
}
void signUp() {
    struct User newUser;
    system("cls"); // clears the terminal
    printf("\n=== Sign Up ===\n");
    printf("Enter master username: ");
    fgets(newUser.username, sizeof(newUser.username), stdin);
    newUser.username[strcspn(newUser.username, "\n")] = '\0'; // remove trailing newline By replacing the first newline character encountered with a null character
    char lame[50];
    strcpy(lame,newUser.username);  //if the string  newUser.username is empty then it will again call runnercode()
    if(strcmp(lame,"")==0) {
        runnercode();
    }
    char *file = strcat(lame,".txt"); // the file pointer will point to the modified lame string.
    if (access(file, F_OK) != -1) {
        printf("Username Exist. Choose another\n");
        tpass();
        tpass();
        signUp();
    }
    else{
        printf("Enter master password: ");
        hpass(newUser.password);
        newUser.password[strcspn(newUser.password, "\n")] = '\0'; // remove trailing newline
        printf("\n\nStrength of your password is: %d/5\nDo you want to save it?\n1. Yes\n2. Try Again\n", strength(newUser.password));
        int n;
        printf("Enter:");
        scanf("%d",&n);
        getchar();
        if (n==1) {
            // adding special key
            system("cls"); 
            printf("Enter your special key for retreiving passwords: ");
            fgets(newUser.spckey, sizeof(newUser.spckey), stdin);
            newUser.spckey[strcspn(newUser.spckey, "\n")] = '\0'; // remove trailing newline
            // Create a new file for the user
            char filename[MAX_USERNAME_LENGTH + 4]; // 4 is for ".txt" and null terminator
            snprintf(filename, sizeof(filename), "%s.txt", newUser.username); //This generates a filename with the username and the .txt extension.
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
            printf("Sign up successful!\n");
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
    hpass(inputUser.password);
    inputUser.password[strcspn(inputUser.password, "\n")] = '\0'; // remove trailing newline
    char filename[MAX_USERNAME_LENGTH + 4]; // 4 is for ".txt" and null terminator
    // Open the user's file for verification
    snprintf(filename, sizeof(filename), "%s.txt", inputUser.username);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("\nUser does not exist.\n");
        tpass();
        runnercode();
        return;
    }
    fclose(file);
    struct User masterUser;
   // Retrieve the username, password, and special key from the file and store them in masterUser struct
    getfile(1,filename,masterUser.username);
    getfile(2,filename,masterUser.password);
    getfile(3,filename,masterUser.spckey);
     //it  decrypts  the stored username, password, and special key.
        decrypt(masterUser.username);
        decrypt(masterUser.password);
        decrypt(masterUser.spckey);

    if (strcmp(masterUser.username, inputUser.username) == 0 && strcmp(masterUser.password, inputUser.password) == 0) {
        match = 1;
    }

    if (match) {
        printf("\nSign in successful!\n");
        tpass();
        runnercode3(filename,masterUser.spckey);
    }
    else {
        printf("\nWrong master username or password. Please try again.\n");
        tpass();
        runnercode();
    }
}

int main() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t*** Welcome to Pass Hub ***\n"); // ornamental
    printf("\n\n\n\n");
    printf("\n\t\t\t\t\t\t     **"); // ornamental
    Sleep(400); // command to stop execution
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
