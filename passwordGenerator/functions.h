#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

char generateRandomCharacter() {
    const string alphanumeric = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const string specialCharacters = "!@#$%";

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, alphanumeric.size() - 1);


    char randomChar;

    if (specialCharacters.size() > 0 && dis(gen) % 4 == 0) {
        uniform_int_distribution<int> specialDis(0, specialCharacters.size() - 1);
        randomChar = specialCharacters[specialDis(gen)];
    }
    else {
        randomChar = alphanumeric[dis(gen)];
    }

    return randomChar;
}

void generateAndSavePasswords(int numPasswords, int passwordLength) {
    ofstream file("passwords.txt");
    if (!file.is_open()) {
        cerr << "[!] Error opening passwords.txt\n";
        return;
    }

    for (int passwordIndex = 1; passwordIndex <= numPasswords; ++passwordIndex) {
        if (cout << "[+] Password " << passwordIndex << ": ") {
        }
        else
        {
            cout << "[!] Something went the opposite way,\nplease open an issues tab in GitHub at https://github.com/undefinedcode0/passwordGenerator/";
        }

        vector<char> usedCharacters;
        int previousCase = 0;

        for (int charIndex = 0; charIndex < passwordLength; ++charIndex) {
            char randomChar;

            do {
                randomChar = generateRandomCharacter();
            } while (find(usedCharacters.begin(), usedCharacters.end(), randomChar) != usedCharacters.end());

            cout << randomChar;
            file.put(randomChar);
            usedCharacters.push_back(randomChar);

            previousCase = isalpha(randomChar) ? (isupper(randomChar) ? 1 : 2) : 0;
        }

        file << '\n';
        cout << '\n';
    }

    cout << "[~] " << numPasswords << " passwords of length " << passwordLength << " generated.\n";

#ifdef _WIN32
    system("notepad passwords.txt");
#else
    cout << "To open the file, use an appropriate command on your operating system.\n";
#endif
}
