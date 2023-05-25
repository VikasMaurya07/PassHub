#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function for generating a random password
void getPass(int size) {
    srand(time(NULL));

    //characters to choose from for the password
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$^&*()+'-,.";

    printf("Generated Password: ");

    for (int i = 0; i < size; i++) {
        int index = rand() % (sizeof(charset) - 1);
        printf("%c", charset[index]);
    }

    printf("\n");
}

int main() {
    int passwordSize;

    printf("Enter the size of the password: ");
    scanf("%d", &passwordSize);

    // Generate and print the password
    getPass(passwordSize);

    return 0;
}
