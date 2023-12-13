// user_normal.cpp

#include "usernormal.h"

UserNormal::UserNormal(const std::string& login, const std::string& password)
    : User(login, password) {}

void UserNormal::someVirtualFunction() const {
    // Implementation for the pure virtual function
}

bool UserNormal::isPremium() const {
    return false;
}
