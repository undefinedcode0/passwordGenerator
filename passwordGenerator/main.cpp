#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

std::string GeneratePassword(int length)
{
    const std::string characters =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "!@#$%_-?.";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string password;
    for (int i = 0; i < length; ++i)
    {
        password += characters[distribution(generator)];
    }
    return password;
}

std::vector<std::string> GeneratePasswords(int num_passwords, int length)
{
    std::vector<std::string> passwords;
    for (int i = 0; i < num_passwords; ++i)
    {
        passwords.push_back(GeneratePassword(length));
    }
    return passwords;
}

void PrintPasswords(const std::vector<std::string>& passwords)
{
    for (int i = 0; i < passwords.size(); ++i)
    {
        std::cout << (i + 1) << ": " << passwords[i] << std::endl;
    }
}

void SavePasswordsToFile(const std::vector<std::string>& passwords, const std::string& filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        for (int i = 0; i < passwords.size(); ++i)
        {
            file << (i + 1) << ": " << passwords[i] << std::endl;
        }
        file.close();
        std::cout << "[+] Passwords saved to " << filename << std::endl;
    }
    else
    {
        std::cerr << "[!] Unable to open file: " << filename << std::endl;
    }
}

void GetUserInput(int& num_passwords, int& length)
{
    std::cout << "[+] Enter the number of passwords to generate: ";
    while (!(std::cin >> num_passwords) || num_passwords < 0)
    {
        std::cerr << "[+] Please enter a non-negative number." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter the number of passwords to generate: ";
    }

    std::cout << "[+] Enter the length of the passwords: ";
    while (!(std::cin >> length) || length <= 0)
    {
        std::cerr << "[+] Please enter a positive number." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[+] Enter the length of the passwords: ";
    }
}

int main()
{
    int num_passwords, length;
    GetUserInput(num_passwords, length);

    auto passwords = GeneratePasswords(num_passwords, length);
    PrintPasswords(passwords);

    std::cout << "[+] Do you want to save the passwords to a file? (y/n): ";
    std::string save_choice;
    std::cin >> save_choice;
    if (save_choice == "y" || save_choice == "Y")
    {
        std::cout << "[+] Enter the filename: ";
        std::string filename;
        std::cin >> filename;
        SavePasswordsToFile(passwords, filename);
    }

    return 0;
}