// userpremium.cpp

#include "userpremium.h"
#include "json.hpp"
#include "UserCRUD.h"

using json = nlohmann::json;

UserPremium::UserPremium(const std::string& login)
    : User(login) {
    setPremium(true); //set premium in User
}

