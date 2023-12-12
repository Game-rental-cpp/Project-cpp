// user_normal.cpp

#include "usernormal.h"

UserNormal::UserNormal(const std::string& login, const std::string& password)
    : User(login, password), isPremium(false) {}

void UserNormal::someVirtualFunction() const {
    // Implementation for the pure virtual function
}

bool UserNormal::getIsPremium() const {
    return isPremium;
}
