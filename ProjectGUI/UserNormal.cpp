// usernormal.cpp

#include "usernormal.h"

UserNormal::UserNormal(const std::string& login)
    : User(login) {}


bool UserNormal::isPremium() const {
    return false; //user is not premium
}

bool UserNormal::addUserGame(const std::string& name) {
    // Normal user can hire maximally 10 games
    if (userGames.size() == 10)
        return false; //could'nt add new game

    userGames.push_back(UserGame(name));
    return true; //game has been added
}