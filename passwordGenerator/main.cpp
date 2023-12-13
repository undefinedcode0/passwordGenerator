#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

char generateRandomCharacter() {
    const string alphanumeric = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%";

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, alphanumeric.size() - 1);

    return alphanumeric[dis(gen)];
}

void generateAndSavePasswords(int numPasswords, int passwordLength) {
    ofstream file("passwords.txt");
    if (!file.is_open()) {
        cerr << "Error opening passwords.txt\n";
        return;
    }

    for (int passwordIndex = 1; passwordIndex <= numPasswords; ++passwordIndex) {
        file << passwordIndex << ": ";

        vector<char> usedCharacters;
        int previousCase = 0;

        for (int charIndex = 0; charIndex < passwordLength; ++charIndex) {
            char randomChar;

            do {
                randomChar = generateRandomCharacter();
            } while (find(usedCharacters.begin(), usedCharacters.end(), randomChar) != usedCharacters.end());

            file.put(randomChar);
            usedCharacters.push_back(randomChar);

            previousCase = isalpha(randomChar) ? (isupper(randomChar) ? 1 : 2) : 0;
        }

        file << '\n';
    }

    cout << "[~] " << numPasswords << " passwords of length " << passwordLength << " generated and saved to passwords.txt\n";

#ifdef _WIN32
    system("notepad passwords.txt");
#else
    cout << "To open the file, use an appropriate command on your operating system.\n";
#endif
}

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
