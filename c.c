#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

void signUp() {
    struct User newUser;

    printf("=== Sign Up ===\n");

    printf("Enter master username: ");
    fgets(newUser.username, sizeof(newUser.username), stdin);
    newUser.username[strcspn(newUser.username, "\n")] = '\0'; // remove trailing newline

    printf("Enter master password: ");
    fgets(newUser.password, sizeof(newUser.password), stdin);
    newUser.password[strcspn(newUser.password, "\n")] = '\0'; // remove trailing newline

    FILE *file = fopen("user_info.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "Master Username: %s\n", newUser.username);
    fprintf(file, "Master Password: %s\n\n", newUser.password);

    fclose(file);

    printf("Sign up successful! User information saved to user_info.txt.\n");
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
                // TODO: Implement Sign In functionality
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