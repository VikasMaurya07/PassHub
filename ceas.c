#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define CAESAR_SHIFT 3

char* encryptPassword(const char* password) {
    char* encrypted = malloc(MAX_PASSWORD_LENGTH);
    int i;

    for (i = 0; password[i] != '\0'; i++) {
        if (password[i] >= 'a' && password[i] <= 'z') {
            encrypted[i] = 'a' + (password[i] - 'a' + CAESAR_SHIFT) % 26;
        } else if (password[i] >= 'A' && password[i] <= 'Z') {
            encrypted[i] = 'A' + (password[i] - 'A' + CAESAR_SHIFT) % 26;
        } else {
            encrypted[i] = password[i];
        }
    }

    encrypted[i] = '\0';

    return encrypted;
}

char* decryptPassword(const char* encryptedPassword) {
    char* decrypted = malloc(MAX_PASSWORD_LENGTH);
    int i;

    for (i = 0; encryptedPassword[i] != '\0'; i++) {
        if (encryptedPassword[i] >= 'a' && encryptedPassword[i] <= 'z') {
            decrypted[i] = 'a' + (encryptedPassword[i] - 'a' - CAESAR_SHIFT + 26) % 26;
        } else if (encryptedPassword[i] >= 'A' && encryptedPassword[i] <= 'Z') {
            decrypted[i] = 'A' + (encryptedPassword[i] - 'A' - CAESAR_SHIFT + 26) % 26;
        } else {
            decrypted[i] = encryptedPassword[i];
        }
    }

    decrypted[i] = '\0';

    return decrypted;
}

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char spckey[5];
};
struct User masterUser;

// Function declarations
void signUp();
void signIn();
void retrievePassword();
void addPassword();

void setSpecialKey() {
    char specialKey[MAX_PASSWORD_LENGTH];

    printf("=== Set Special Key ===\n");

    // Get special key
    printf("Enter special key: ");
    fgets(specialKey, sizeof(specialKey), stdin);
    specialKey[strcspn(specialKey, "\n")] = '\0'; // remove trailing newline

    // Encrypt the special key
    char* encryptedKey = encryptPassword(specialKey);

    // Create the special key file
    FILE* file = fopen("specialkey.txt", "w");
    if (file == NULL) {
        printf("Error creating special key file!\n");
        return;
    }

    // Write the encrypted special key to the file
    fprintf(file, "Encrypted Special Key: %s\n", encryptedKey);

    fclose(file);

    printf("Special key set successfully!\n");
}

void retrievePassword() {
    char website[MAX_USERNAME_LENGTH];
    char specialKey[MAX_PASSWORD_LENGTH];

    printf("=== Retrieve Password ===\n");

    // Get the special key from the user
    printf("Enter the special key: ");
    fgets(specialKey, sizeof(specialKey), stdin);
    specialKey[strcspn(specialKey, "\n")] = '\0'; // remove trailing newline

    // Read the encrypted special key from the file
    FILE* specialKeyFile = fopen("specialkey.txt", "r");
    if (specialKeyFile == NULL) {
        printf("Error opening special key file!\n");
        return;
    }

    char encryptedKey[MAX_PASSWORD_LENGTH];

    // Read the contents of the special key file
    while (fgets(encryptedKey, sizeof(encryptedKey), specialKeyFile) != NULL) {
        if (strstr(encryptedKey, "Encrypted Special Key:")) {
            sscanf(encryptedKey, "Encrypted Special Key: %s", encryptedKey);
            break;
        }
    }

    fclose(specialKeyFile);

    // Decrypt the special key
    char* decryptedKey = decryptPassword(encryptedKey);

    // Check if the special key is correct
    if (strcmp(specialKey, decryptedKey) != 0) {
        printf("Invalid special key. Access denied.\n");
        free(decryptedKey);
        return;
    }

    free(decryptedKey);

    // Get website name
    printf("Enter website name: ");
    fgets(website, sizeof(website), stdin);
    website[strcspn(website, "\n")] = '\0'; // remove trailing newline

    // Rest of the code remains the same
    // ...
}


void addPassword() {
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

    // Encrypt the password
    char* encryptedPassword = encryptPassword(password);

    // Create file name using master username and website
    char filename[MAX_USERNAME_LENGTH + MAX_USERNAME_LENGTH + 5]; // masterusername + "_" + website + ".txt" + null character
    snprintf(filename, sizeof(filename), "%s_%s.txt", masterUser.username, website);

    // Open the file in write mode
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write website name, username, and encrypted password to the file
    fprintf(file, "Website: %s\n", website);
    fprintf(file, "Username: %s\n", username);
    fprintf(file, "Encrypted Password: %s\n", encryptedPassword);

    fclose(file);

    printf("Password added successfully!\n");
}

void signUp() {
    struct User newUser;

    printf("=== Sign Up ===\n");

    printf("Enter master username: ");
    fgets(newUser.username, sizeof(newUser.username), stdin);
    newUser.username[strcspn(newUser.username, "\n")] = '\0'; // remove trailing newline

    printf("Enter master password: ");
    fgets(newUser.password, sizeof(newUser.password), stdin);
    newUser.password[strcspn(newUser.password, "\n")] = '\0'; // remove trailing newline
    // creating special key

    // Create a new file for the user
    char filename[MAX_USERNAME_LENGTH + 4]; // 4 is for ".txt" and null terminator
    snprintf(filename, sizeof(filename), "%s.txt", newUser.username);
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating file!\n");
        return;
    }

    fprintf(file, "Master Username: %s\n", newUser.username);
    fprintf(file, "Master Password: %s\n\n", newUser.password);

    fclose(file);

    printf("Sign up successful! User information saved to %s.\n", filename);
}

void signIn() {
    struct User inputUser;
    int match = 0;

    printf("=== Sign In ===\n");

    printf("Enter master username: ");
    fgets(inputUser.username, sizeof(inputUser.username), stdin);
    inputUser.username[strcspn(inputUser.username, "\n")] = '\0'; // remove trailing newline

    printf("Enter master password: ");
    fgets(inputUser.password, sizeof(inputUser.password), stdin);
    inputUser.password[strcspn(inputUser.password, "\n")] = '\0'; // remove trailing newline
    
    // Open the user's file for verification
    char filename[MAX_USERNAME_LENGTH + 4]; // 4 is for ".txt" and null terminator
    snprintf(filename, sizeof(filename), "%s.txt", inputUser.username);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("User does not exist.\n");
        return;
    }

    char line[100];
    struct User masterUser;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Master Username:")) {
            sscanf(line, "Master Username: %s", masterUser.username);
        } else if (strstr(line, "Master Password:")) {
            sscanf(line, "Master Password: %s", masterUser.password);
        }
    }

    fclose(file);

    if (strcmp(masterUser.username, inputUser.username) == 0 && strcmp(masterUser.password, inputUser.password) == 0) {
        match = 1;
    }

    if (match) {
        printf("Sign in successful!\n");
        int option;

        do {
            printf("\nSelect an option:\n");
            printf("1. Retrieve Password\n");
            printf("2. Add Password\n");
            printf("3. Back\n");
            printf("Option: ");
            scanf("%d", &option);
            getchar(); // consume newline character

            switch (option) {
                case 1:
                    retrievePassword();
                    break;
                case 2:
                    addPassword();
                    break;
                case 3:
                    printf("Going back...\n");
                    break;
                default:
                    printf("Invalid option. Please try again.\n");
            }
        } while (option != 3);
    } else {
        printf("Wrong master username or password. Please try again.\n");
    }
}

int main() {
    int option;

    printf("Welcome to Pass Hub\n");

    do {
        printf("\nSelect an option:\n");
        printf("1. Sign Up\n");
        printf("2. Sign In\n");
        printf("3. Set Special Key\n");
        printf("4. Exit\n");
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
                setSpecialKey();
                break;

            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 3);

    return 0;
}
