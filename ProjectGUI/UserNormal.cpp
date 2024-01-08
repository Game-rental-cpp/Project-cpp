// usernormal.cpp

#include "usernormal.h"
#include "UserCRUD.h"
#include "json.hpp"

using json = nlohmann::json;

UserNormal::UserNormal(const std::string& login)
    : User(login) {
    setPremium(false);
   

}

std::string UserNormal::stringifyUser() {
    json userGames = json::parse(User::stringifyGames());
    json user = {
        {"login", login},
        {"password", password},
        {"isPremium", false}, //
        {"userGames", userGames}
    };

    return user.dump(4);
}

