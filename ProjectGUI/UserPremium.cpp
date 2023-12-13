// userpremium.cpp

#include "userpremium.h"
#include "json.hpp"

using json = nlohmann::json;

UserPremium::UserPremium(const std::string& login)
    : User(login) {}


bool UserPremium::isPremium() const {
    return true; //user is premium
}

std::string UserPremium::stringifyUser() {
    json userGames = json::parse(User::stringifyGames()); //tworzy tablicê
    json user = {
        {"login", login},
        {"password", password},
        {"isPremium", true},
        {"userGames", userGames}
    };

    return user.dump(4);
}