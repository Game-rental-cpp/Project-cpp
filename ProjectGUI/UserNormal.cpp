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

//std::string UserNormal::stringifyUser() {
//    json userGames = json::parse(User::stringifyGames()); //tworzy tablicê
//    json user = {
//        {"login", login},
//        {"password", password},
//        {"isPremium", false},
//        {"userGames", userGames}
//    };
//
//    return user.dump(4);
//}

//bool UserNormal::isPremium() const {
//    return false; //user is not premium
//}

//bool UserNormal::addUserGame(const std::string& name) {
//    // Normal user can hire maximally 10 games
//    if (userGames.size() == 10)
//        return false; //could'nt add new game
//    UserCRUD::UpdateUser(login, User::stringifyUser());
//
//    userGames.push_back(UserGame(name));
//    return true; //game has been added
//}


