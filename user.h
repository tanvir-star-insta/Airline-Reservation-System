#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string name;
    std::string email;
    std::string password;
    std::string aadhar;
public:
    User() = default;
    User(const std::string& name, const std::string& email, const std::string& password, const std::string& aadhar);
    virtual ~User() = default;

    std::string getName() const;
    std::string getEmail() const;
    std::string getAadhar() const;
    bool verifyPassword(const std::string& pass) const;

    virtual void fillProfile();
    virtual void showProfile() const;
};

#endif
