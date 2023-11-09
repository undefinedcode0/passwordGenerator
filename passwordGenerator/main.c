#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>
#include <ctype.h>

char generateRandomCharacter() {
    // Added more symbols to the character set
    const char characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%&*()?=~^+_-[]{}<>/|`.,;:'";
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
        int used[256] = { 0 };
        int prevCase = 0; // 0 for none, 1 for upper, 2 for lower
        for (int i = 0; i < passwordLength; i++) {
            char randomChar = generateRandomCharacter();

            while (used[tolower(randomChar)]) {
                randomChar = generateRandomCharacter();
            }

            while ((isupper(randomChar) && prevCase == 1) || (islower(randomChar) && prevCase == 2)) {
                randomChar = generateRandomCharacter();
            }

            fputc(randomChar, file);
            used[tolower(randomChar)] = 1;

            if (isupper(randomChar)) {
                prevCase = 1;
            }
            else if (islower(randomChar)) {
                prevCase = 2;
            }
            else {
                prevCase = 0;
            }
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
    if (sodium_init() < 0) {
        // panic! the library couldn't be initialized, it is not safe to use
        printf("Error initializing sodium library\n");
        return 1;
    }

    if (argc == 2) {
        if (sodium_memcmp(argv[1], "email", 5) == 0) {
            generateAndSavePasswords(15, 40);
        }
        else if (sodium_memcmp(argv[1], "account", 7) == 0) {
            generateAndSavePasswords(15, 60);
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

        generateAndSavePasswords(numPasswords, passwordLength);
    }
    else {
        printf("Usage: %s <numPasswords> <passwordLength> OR %s email OR %s account\n", argv[0], argv[0], argv[0]);
        return 1;
    }

    return 0;
}
