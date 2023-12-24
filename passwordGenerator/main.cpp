#include "functions.h"

int main() {
    cout << "[*] Welcome to PasswordGenerator!\n";
    cout << "[*] A secure password generator.\n\n";

    int numPasswords, passwordLength;

    cout << "[~] Number of passwords?: ";
    cin >> numPasswords;

    cout << "[~] Length of passwords?: ";
    cin >> passwordLength;

    if (numPasswords <= 0 || passwordLength <= 0) {
        cerr << "[?] Please provide a valid number of passwords and password length.\n";
        return 1;
    }

    generateAndSavePasswords(numPasswords, passwordLength);

    return 0;
}
