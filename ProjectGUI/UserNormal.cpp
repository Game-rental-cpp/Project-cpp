// usernormal.cpp

#include "usernormal.h"
#include "UserCRUD.h"
#include "json.hpp"
//#include <wx/wx.h>

using json = nlohmann::json;

UserNormal::UserNormal(const std::string& login)
    : User(login) {
    std::string userStr = UserCRUD::ReadUser(login);
    //wxLogMessage(wxString::Format("%s", userStr));
    setPremium(false);

    json jsonData = json::parse(userStr); //parsing JSON string
    std::string passwordStr = jsonData.at("password"); //get value of key "password"
    //isPremium password = jsonData.at("password"); //get value of key "password"
    password = passwordStr;
    json gamesArray = jsonData.at("userGames");
    //if(gamesArray.size()>0)
    // Iterowanie po elementach tablicy
    for (const auto& game : gamesArray) {
        // Wyci�ganie warto�ci z obiektu w tablicy
        User::UserGame userGame(game.at("name"));
        userGame.SetId(game.at("id"));
        userGame.SetDate(game.at("date"));
        userGames.push_back(userGame);
    }


}

//std::string UserNormal::stringifyUser() {
//    json userGames = json::parse(User::stringifyGames()); //tworzy tablic�
//    json user = {
//        {"login", login},
//        {"password", password},
//        {"isPremium", false},
//        {"userGames", userGames}
//    };
//
//    return user.dump(4);
//}

bool UserNormal::isPremium() const {
    return false; //user is not premium
}

//bool UserNormal::addUserGame(const std::string& name) {
//    // Normal user can hire maximally 10 games
//    if (userGames.size() == 10)
//        return false; //could'nt add new game
//    UserCRUD::UpdateUser(login, User::stringifyUser());
//
//    userGames.push_back(UserGame(name));
//    return true; //game has been added
//}


