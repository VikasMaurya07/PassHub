#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

char* encryptPassword(const char* password) {
    // Load public key
    RSA* rsa = RSA_new();
    FILE* keyFile = fopen("public_key.pem", "r");
    PEM_read_RSA_PUBKEY(keyFile, &rsa, NULL, NULL);
    fclose(keyFile);

    // Encrypt the password
    char* encrypted = malloc(RSA_size(rsa));
    RSA_public_encrypt(strlen(password) + 1, (unsigned char*)password, (unsigned char*)encrypted, rsa, RSA_PKCS1_PADDING);

    RSA_free(rsa);

    return encrypted;
}

char* decryptPassword(const char* encryptedPassword) {
    // Load private key
    RSA* rsa = RSA_new();
    FILE* keyFile = fopen("private_key.pem", "r");
    PEM_read_RSAPrivateKey(keyFile, &rsa, NULL, NULL);
    fclose(keyFile);

    // Decrypt the password
    char* decrypted = malloc(RSA_size(rsa));
    RSA_private_decrypt(RSA_size(rsa), (unsigned char*)encryptedPassword, (unsigned char*)decrypted, rsa, RSA_PKCS1_PADDING);

    RSA_free(rsa);

    return decrypted;
}

   
struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};
struct User masterUser;

// Function declarations
void signUp();
void signIn();
void retrievePassword();
void addPassword();

    

void retrievePassword() {
    char website[MAX_USERNAME_LENGTH];

    printf("=== Retrieve Password ===\n");

    // Get the special key from the user
    char specialKey[50];
    printf("Enter the special key: ");
    fgets(specialKey, sizeof(specialKey), stdin);
    specialKey[strcspn(specialKey, "\n")] = '\0'; // remove trailing newline

    // Check if the special key is correct
    if (strcmp(specialKey, "gohil@ranendu") != 0) {
        printf("Invalid special key. Access denied.\n");
        return;
    }

    // Get website name
    printf("Enter website name: ");
    fgets(website, sizeof(website), stdin);
    website[strcspn(website, "\n")] = '\0'; // remove trailing newline

    // Create file name using master username and website
    char filename[MAX_USERNAME_LENGTH + MAX_USERNAME_LENGTH + 5]; // masterusername + "_" + website + ".txt" + null character
    snprintf(filename, sizeof(filename), "%s_%s.txt", masterUser.username, website);

    // Open the file in read mode
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char line[100];
    char encryptedPassword[MAX_PASSWORD_LENGTH];

    // Read the contents of the file
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Encrypted Password:")) {
            sscanf(line, "Encrypted Password: %s", encryptedPassword);
        }
    }

    fclose(file);

    // Decrypt the password
    char* decryptedPassword = decryptPassword(encryptedPassword);

    printf("Decrypted Password: %s\n", decryptedPassword);
    free(decryptedPassword);
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
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 3);

    return 0;
}
