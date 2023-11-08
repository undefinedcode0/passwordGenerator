#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char generateRandomCharacter() {
    const char characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%&*()?=";
    int randomIndex = rand() % (sizeof(characters) - 1);
    return characters[randomIndex];
}

void generateAndSavePasswords(int numPasswords, int passwordLength) {
    FILE* file = fopen("passwords.txt", "w");
    if (file == NULL) {
        perror("Error opening passwords.txt");
        return;
    }

    for (int j = 1; j <= numPasswords; j++) {
        fprintf(file, "%d: ", j);
        for (int i = 0; i < passwordLength; i++) {
            char randomChar = generateRandomCharacter();
            if (rand() % 2 == 0) {
                randomChar = (randomChar >= 'a' && randomChar <= 'z') ? (randomChar - 'a' + 'A') : randomChar;
            }
            fputc(randomChar, file);
        }
        fputc('\n', file);
    }

    fclose(file);
    printf("%d passwords of length %d generated and saved to passwords.txt\n", numPasswords, passwordLength);

#ifdef _WIN32
    system("notepad passwords.txt");
#else
    printf("To open the file, use an appropriate command on your operating system.\n");
#endif
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        if (strcmp(argv[1], "email") == 0) {
            generateAndSavePasswords(15, 30);
        }
        else if (strcmp(argv[1], "account") == 0) {
            generateAndSavePasswords(15, 50);
        }
        else {
            printf("Invalid input. Usage: %s <numPasswords> <passwordLength> OR %s email OR %s account\n", argv[0], argv[0], argv[0]);
            return 1;
        }
    }
    else if (argc == 3) {
        int numPasswords = atoi(argv[1]);
        int passwordLength = atoi(argv[2]);

        if (numPasswords <= 0 || passwordLength <= 0) {
            printf("Please provide a valid number of passwords and password length.\n");
            return 1;
        }

        srand((unsigned)time(NULL));

        generateAndSavePasswords(numPasswords, passwordLength);
    }
    else {
        printf("Usage: %s <numPasswords> <passwordLength> OR %s email OR %s account\n", argv[0], argv[0], argv[0]);
        return 1;
    }

    return 0;
}
