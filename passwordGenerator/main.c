#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char generateRandomCharacter() {
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()?=";
    int randomIndex = rand() % (sizeof(characters) - 1);
    return characters[randomIndex];
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <password_length>\n", argv[0]);
        return 1;
    }

    int passwordLength = atoi(argv[1]);
    if (passwordLength <= 0) {
        printf("Please provide a valid password length.\n");
        return 1;
    }

    srand((unsigned)(time(NULL) + clock()));

    printf("Generated password: ");
    for (int i = 0; i < passwordLength; i++) {
        char randomChar = generateRandomCharacter();

        if (rand() % 2 == 0) {
            randomChar = (randomChar >= 'a' && randomChar <= 'z') ? (randomChar - 'a' + 'A') : randomChar;
        }

        printf("%c", randomChar);
    }
    printf("\n");

    return 0;
}