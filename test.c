#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

// Generate a random password of a given length
void generate_password(int length, char *password) {
    const char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
    int characters_length = strlen(characters);

    for (int i = 0; i < length; i++) {
        int random_index = rand() % characters_length;
        password[i] = characters[random_index];
    }

    password[length] = '\0';
}

// Encrypt password using a simple Caesar cipher
void encrypt_password(char *password) {
    int i = 0;
    while (password[i] != '\0') {
        if (isalpha(password[i])) {
            if (isupper(password[i])) {
                password[i] = (password[i] - 'A' + 1) % 26 + 'A';
            } else {
                password[i] = (password[i] - 'a' + 1) % 26 + 'a';
            }
        }
        i++;
    }
}

// Save username, website, and encrypted password to a file
void save_password(const char *username, const char *website, const char *encrypted_password) {
    FILE *file = fopen("passwords.txt", "a");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%s %s %s\n", username, website, encrypted_password);
    fclose(file);
}

// Retrieve password based on username and website
void retrieve_password(const char *username, const char *website) {
    char current_username[MAX_LENGTH];
    char current_website[MAX_LENGTH];
    char current_password[MAX_LENGTH];

    FILE *file = fopen("passwords.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    while (fscanf(file, "%s %s %s", current_username, current_website, current_password) != EOF) {
        if (strcmp(current_username, username) == 0 && strcmp(current_website, website) == 0) {
            printf("Retrieved Password: %s\n", current_password);
            fclose(file);
            return;
        }
    }

    printf("Password not found.\n");
    fclose(file);
}

int main() {
    char username[MAX_LENGTH];
    char website[MAX_LENGTH];
    char password[MAX_LENGTH];
    char encrypted_password[MAX_LENGTH];
    int password_length;
    int option;

    // Prompt for option
    printf("Choose an option:\n");
    printf("1. Save a password\n");
    printf("2. Retrieve a password\n");
    printf("Enter option number: ");
    scanf("%d", &option);

    if (option == 1) {
        // Prompt for username and website
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter website: ");
        scanf("%s", website);

        // Prompt for password length
        printf("Enter the desired length of the password: ");
        scanf("%d", &password_length);

        // Generate and encrypt a new password
        generate_password(password_length, password);
        encrypt_password(password);
        printf("Generated Password: %s\n", password);

        // Save the username, website, and encrypted password to a file
        save_password(username, website, password);

        printf("Password saved successfully.\n");
    } 
        else if (option == 2) {
        // Prompt for username and website
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter website: ");
        scanf("%s", website);

        // Retrieve the password based on username and website
        retrieve_password(username, website);
    } else {
        printf("Invalid option. Exiting...\n");
        return 0;
    }

    return 0;
}