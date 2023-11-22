#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sodium.h>
#include <windows.h>
#include <time.h>

#define ALPHANUMERIC_PERCENT 90
#define SPECIAL_PERCENT 10

char generateRandomCharacter() {
    const char alphanumeric[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const char specialCharacters[] = "!@#$&*";

    unsigned char randomChar;
    randombytes_buf(&randomChar, sizeof(randomChar));

    double randomValue = (double)randomChar / (double)UCHAR_MAX * 100.0;

    if (randomValue < ALPHANUMERIC_PERCENT) {
        return alphanumeric[randombytes_uniform(sizeof(alphanumeric) - 1)];
    }
    else {
        return specialCharacters[randombytes_uniform(sizeof(specialCharacters) - 1)];
    }
}

static void generateAndSavePasswords(
    int numPasswords, 
    int passwordLength
) {
    FILE* file = fopen("passwords.txt", "w");
    if (file == NULL) {
        perror("Error opening passwords.txt");
        return;
    }

    for (int j = 1; j <= numPasswords; j++) {
        fprintf(file, "%d: ", j);

        int used[256] = { 0 };
        int prevCase = 0;

        for (int i = 0; i < passwordLength; i++) {
            char randomChar;

            do {
                randomChar = generateRandomCharacter();

            } while (used[tolower((unsigned char)randomChar)] ||
                (i > 0 && randomChar == used[i - 1]) ||
                (i > 1 && randomChar == used[i - 2]));

            while ((isupper(randomChar) && prevCase == 1) || (islower(randomChar) && prevCase == 2)) {
                randomChar = generateRandomCharacter();
            }

            fputc(randomChar, file);

            used[tolower((unsigned char)randomChar)] = randomChar;
            prevCase = isalpha(randomChar) ? isupper(randomChar) ? 1 : 2 : 0;
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

int main(
    int numPasswords, 
    int passwordLength
) {

    if (sodium_init() < 0) {
        fprintf(stderr, "Error initializing sodium library\n");
        return 1;
    }

    randombytes_stir();

    printf("number of passwords?: ");
    scanf("%d", &numPasswords);

    printf("length of passwords?: ");
    scanf("%d", &passwordLength);

    if (numPasswords <= 0 || passwordLength <= 0) {
        fprintf(stderr, "Please provide a valid number of passwords and password length.\n");
        return 1;
    }

    generateAndSavePasswords(numPasswords, passwordLength);

    return 0;
}
