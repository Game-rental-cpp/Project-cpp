// userpremium.cpp

#include "userpremium.h"
#include "UserCRUD.h"
#include "json.hpp"

using json = nlohmann::json;

UserPremium::UserPremium(const std::string& login)
    : User(login) {
    setPremium(true); //set isPremium 
}

std::string UserPremium::stringifyUser() {
    json userGames = json::parse(User::stringifyGames());
    json user = {
        {"login", login},
        {"password", password},
        {"isPremium", true}, // true
        {"userGames", userGames}
    };

    return user.dump(4);
}