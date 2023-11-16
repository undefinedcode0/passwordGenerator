#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sodium.h>
#include <windows.h>

#define ALPHANUMERIC_PERCENT 80
#define SPECIAL_PERCENT 20

char generateRandomCharacter() {
    const char alphanumeric[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const char specialCharacters[] = "!@#$%&*?=";

    double randomValue = (double)randombytes_uniform(1000) / 10.0;  // Generate a random value between 0 and 100.

    if (randomValue < ALPHANUMERIC_PERCENT) {
        return alphanumeric[randombytes_uniform(sizeof(alphanumeric) - 1)];
    }
    else {
        return specialCharacters[randombytes_uniform(sizeof(specialCharacters) - 1)];
    }
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

            int attempts = 0;
            while (used[tolower(randomChar)]) {
                // Limit the number of attempts to avoid infinite loop
                if (attempts++ > 1000) {
                    fprintf(stderr, "Error: Unable to generate a unique character.\n");

                    /* Debug code for testing purposes
                     * 
                     * char buf[30];
                     * sprintf(buf, "sobber: %d", GetLastError());
                     * printf(buf);
                    */

                    fclose(file);
                    return;
                }
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
        printf("Error initializing sodium library\n");
        return 1;
    }

    if (argc == 2) {
        if (strcmp(argv[1], "email") == 0) {
            generateAndSavePasswords(3, 40);
        }
        else if (strcmp(argv[1], "account") == 0) {
            generateAndSavePasswords(3, 50);
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