// userpremium.cpp

#include "userpremium.h"
#include "json.hpp"
#include "UserCRUD.h"

using json = nlohmann::json;

UserPremium::UserPremium(const std::string& login)
    : User(login) {
    std::string userStr = UserCRUD::ReadUser(login);
    //wxLogMessage(wxString::Format("%s", userStr));
    setPremium(true);

    json jsonData = json::parse(userStr); //parsing JSON string
    std::string passwordStr = jsonData.at("password"); //get value of key "password"
    //isPremium password = jsonData.at("password"); //get value of key "password"
    password = passwordStr;
    json gamesArray = jsonData.at("userGames");
    //if(gamesArray.size()>0)
    // Iterowanie po elementach tablicy
    for (const auto& game : gamesArray) {
        // Wyci¹ganie wartoœci z obiektu w tablicy
        User::UserGame userGame(game.at("name"));
        userGame.SetId(game.at("id"));
        userGame.SetDate(game.at("date"));
        userGames.push_back(userGame);
    }


}


//std::string UserPremium::stringifyUser() {
//    json userGames = json::parse(User::stringifyGames()); //tworzy tablicê
//    json user = {
//        {"login", login},
//        {"password", password},
//        {"isPremium", true},
//        {"userGames", userGames}
//    };
//
//    return user.dump(4);
//}

bool UserPremium::isPremium() const {
    return true; //user is premium
}
