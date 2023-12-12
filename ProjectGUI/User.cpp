// user.cpp

#include "user.h"

User::User(const std::string& login, const std::string& password)
    : login(login), password(password) {}

std::string User::getLogin() const {
    return login;
}

std::string User::getPassword() const {
    return password;
}
