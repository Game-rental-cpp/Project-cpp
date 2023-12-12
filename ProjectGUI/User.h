// user.h

#pragma once

#include <string>

class User {
public:
    User(const std::string& login, const std::string& password);
    virtual ~User() = default;

    virtual void someVirtualFunction() const = 0;

    // Getters
    std::string getLogin() const;
    std::string getPassword() const;

private:
    std::string login;
    std::string password;
};
