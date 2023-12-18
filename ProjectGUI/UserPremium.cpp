// userpremium.cpp

#include "userpremium.h"
#include "json.hpp"
#include "UserCRUD.h"

using json = nlohmann::json;

UserPremium::UserPremium(const std::string& login)
    : User(login) {
    setPremium(true); //set premium in User
}

std::string UserPremium::stringifyUser() {
    json userGames = json::parse(User::stringifyGames()); //tworzy tablic�
    json user = {
        {"login", login},
        {"password", password},
        {"isPremium", true},
        {"userGames", userGames}
    };

    return user.dump(4);
}