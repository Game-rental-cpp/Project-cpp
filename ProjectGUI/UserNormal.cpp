// user_normal.cpp

#include "usernormal.h"

UserNormal::UserNormal(const std::string& login)
    : User(login) {}


bool UserNormal::isPremium() const {
    return false;
}

void UserNormal::addUserGame(const std::string& name) {
    // Normal user can hire maximally 10 games
    if (userGames.size() == 10)
        return;

    userGames.push_back(UserGame(name));
}