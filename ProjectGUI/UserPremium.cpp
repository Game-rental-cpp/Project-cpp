// userpremium.cpp

#include "userpremium.h"

UserPremium::UserPremium(const std::string& login)
    : User(login) {}


bool UserPremium::isPremium() const {
    return true; //user is premium
}

