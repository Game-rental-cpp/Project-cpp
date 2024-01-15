// usernormal.cpp

#include "usernormal.h"
#include "UserCRUD.h"
#include "json.hpp"

using json = nlohmann::json;

UserNormal::UserNormal(const std::string& login)
    : User(login) {
}

std::string UserNormal::stringifyUser() {
    json userGames = json::parse(User::stringifyGames());
    json user = {
        {"login", login},
        {"password", password},
        {"isPremium", false}, // false
        {"userGames", userGames}
    };

    return user.dump(4);
}

bool UserNormal::addUserGame(const std::string& name) {
    if (userGames.size() == 5) // add this condition
        return false;

    // Create new userGame and push it to userGames vector
    userGames.push_back(UserGame(name));

    UserCRUD::UpdateUser(login, stringifyUser());
    return true;
}