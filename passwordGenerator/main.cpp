#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>

char GenerateRandomCharacter() {
    const std::string alphanumeric = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const std::string specialCharacters = "!@#$%";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, alphanumeric.size() - 1);

    char randomChar;

    if (!specialCharacters.empty() && dis(gen) % 4 == 0) {
        std::uniform_int_distribution<int> specialDis(0, specialCharacters.size() - 1);
        randomChar = specialCharacters[specialDis(gen)];
    }
    else {
        randomChar = alphanumeric[dis(gen)];
    }

    return randomChar;
}

void GenerateAndSavePasswords(int numPasswords, int passwordLength) {
    std::ofstream file("passwords.txt");
    if (!file.is_open()) {
        std::cerr << "[!] Error opening passwords.txt\n";
        return;
    }

    for (int passwordIndex = 1; passwordIndex <= numPasswords; ++passwordIndex) {
        if (std::cout << "[+] Password " << passwordIndex << ": ") {
        }
        else {
            std::cout << "[!] Something went the opposite way,\nplease open an issues tab in GitHub at https://github.com/undefinedcode0/passwordGenerator/";
        }

        std::vector<char> usedCharacters;
        int previousCase = 0;

        for (int charIndex = 0; charIndex < passwordLength; ++charIndex) {
            char randomChar;

            do {
                randomChar = GenerateRandomCharacter();
            } while (std::find(usedCharacters.begin(), usedCharacters.end(), randomChar) != usedCharacters.end());

            std::cout << randomChar;
            file.put(randomChar);
            usedCharacters.push_back(randomChar);

            previousCase = std::isalpha(randomChar) ? (std::isupper(randomChar) ? 1 : 2) : 0;
        }

        file << '\n';
        std::cout << '\n';
    }

    std::cout << "[~] " << numPasswords << " passwords of length " << passwordLength << " generated.\n";

#ifdef _WIN32
    system("notepad passwords.txt");
#else
    std::cout << "To open the file, use an appropriate command on your operating system.\n";
#endif
}

int main() {
    std::cout << "[*] Welcome to PasswordGenerator!\n";
    std::cout << "[*] A secure password generator.\n\n";

    std::string password;
    for (int i = 0; i < length; ++i) 
    {
        password += characters[distribution(generator)];
    }
    return password;
}

    std::cout << "[~] Number of passwords?: ";
    std::cin >> numPasswords;

    std::cout << "[~] Length of passwords?: ";
    std::cin >> passwordLength;

    if (numPasswords <= 0 || passwordLength <= 0) {
        std::cerr << "[?] Please provide a valid number of passwords and password length.\n";
        return 1;
    }

    GenerateAndSavePasswords(numPasswords, passwordLength);

    return 0;
}