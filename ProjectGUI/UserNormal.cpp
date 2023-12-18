// usernormal.cpp

#include "usernormal.h"
#include "UserCRUD.h"
#include "json.hpp"
//#include <wx/wx.h>

using json = nlohmann::json;

UserNormal::UserNormal(const std::string& login)
    : User(login) {
    setPremium(false);
   

}


bool UserNormal::addUserGame(const std::string& name) {
    // Normal user can hire maximally 10 games
    if (userGames.size() == 5)
        return false; //could'nt add new game
    UserCRUD::UpdateUser(login, User::stringifyUser());

    userGames.push_back(UserGame(name));
    return true; //game has been added
}


