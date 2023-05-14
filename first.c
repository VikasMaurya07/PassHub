#include <stdio.h>
#include <string.h>

char *encryption(char *password) {
    // encryption function definition here
    return password;
}

int main() {
    FILE *ptr = fopen("passwords.txt", "a"); // open the file in append mode instead of write mode
    if (ptr == NULL) {
        printf("Could not open file passwords.txt");
        return 1;
    }

    char website[30];
    char userid[30];
    char password[15];

    printf("Enter website: ");
    scanf("%s", website);

    printf("Enter user id: ");
    scanf("%s", userid);

    printf("Enter password: ");
    scanf("%s", password);

    char *encrypted_password = encryption(password);

    fprintf(ptr, "Website: %s\n", website);
    fprintf(ptr, "User ID: %s\n", userid);
    fprintf(ptr, "Encrypted Password: %s\n", encrypted_password);

    fclose(ptr);

    char search_str[30];
    printf("Enter website to search: ");
    scanf("%s", search_str);

    FILE *fp = fopen("passwords.txt", "r");
    if (fp == NULL) {
        printf("Could not open file passwords.txt");
        return 1;
    }

    char buffer[100];
    int line_num = 1;
    int found = 0;

    while (fgets(buffer, 100, fp) != NULL) {
        if (strstr(buffer, search_str) != NULL) {
            printf("A match found on line: %d\n", line_num);
            printf("%s\n", buffer);
            found = 1;
        }
        line_num++;
    }

    if (!found) {
        printf("Sorry, could not find a match.\n");
    }

    fclose(fp);

    return 0;
}