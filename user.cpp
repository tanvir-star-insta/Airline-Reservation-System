#include "user.h"
#include <iostream>

User::User(const std::string& name, const std::string& email, const std::string& password, const std::string& aadhar)
    : name(name), email(email), password(password), aadhar(aadhar) {}

std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }
std::string User::getAadhar() const { return aadhar; }

bool User::verifyPassword(const std::string& pass) const {
    return pass == password;
}

void User::fillProfile() {
    std::cout << "Enter Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Email: ";
    std::getline(std::cin, email);
    std::cout << "Enter Aadhaar Number (12 digits): ";
    std::getline(std::cin, aadhar);
    while (aadhar.length() != 12) {
        std::cout << "Invalid Aadhaar number. Enter again: ";
        std::getline(std::cin, aadhar);
    }
    // Password should be set during signup with masking (handled externally)
}

void User::showProfile() const {
    std::cout << "Name: " << name << "\nEmail: " << email << "\nAadhaar: " << aadhar << '\n';
}
