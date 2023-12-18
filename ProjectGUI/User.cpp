// user.cpp
#include "user.h"
#include "UserCRUD.h"
#include "uuid_v4.h"
#include "json.hpp"

using json = nlohmann::json;

User::User(const std::string& login)
    : login(login) {
    std::string userStr = UserCRUD::ReadUser(login);

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

std::string User::getLogin() const {
    return login;
}

std::string User::getPassword() const {
    return password;
}

const std::vector<User::UserGame>& User::getUserGames() const {
    return userGames;
}

User::UserGame::UserGame(const std::string& name) {
    this->name = name;
    // generate unique id
    UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
    UUIDv4::UUID uuid = uuidGenerator.getUUID();
    id = uuid.str(); // convert id to string

    wxDateTime now = wxDateTime::Now(); // Today's date and time 
    date = now.Format(wxT("%d-%m-%y__%H-%M-%S"), wxDateTime::CET).ToStdString(); // convert wxDateTime to string
}

std::string User::UserGame::getId() const {
    return id;
}


const std::string& User::UserGame::GetName() const {
    return name;
}

std::string User::UserGame::getDate() const {
    return date;
}

bool User::addUserGame(const std::string& name) {
    // Create new userGame and puch it to userGames vector
    userGames.push_back(UserGame(name));

    //TODO: update user json file
    UserCRUD::UpdateUser(login, stringifyUser());
    return true;
}

void User::removeUserGame(const std::string& id) {
    
    for (auto it = userGames.begin(); it != userGames.end(); ++it) {
        // Check if game ID matches the id given in param
        if (it->getId() == id) {
            // remove an element
            userGames.erase(it);
            //TODO: update user json file
            //UserCRUD::UpdateUser(std::string login, std::string stringifiedUser);
            break; 
        }
    }

    UserCRUD::UpdateUser(login, stringifyUser());
}


void User::setUserGames(std::vector<User::UserGame>& newUserGamesVector) {
    userGames = newUserGamesVector;
}

std::string User::stringifyUser() {
    json userGames = json::parse(User::stringifyGames()); //tworzy tablicê
    json user = {
        {"login", login},
        {"password", password},
        {"isPremium", isPremium},
        {"userGames", userGames}
    };

    return user.dump(4);
}

//this function creates a string representation of userGames vector in json format
//used to update user games in json file 
// @returns std::string
std::string User::stringifyGames() {

    std::string strGames = "[";

    for (int i = 0; i < userGames.size(); i++) {
        if (i > 0) {
            strGames += ", ";
        }

        strGames += "{\"id\": \"" + userGames[i].getId() + "\", \"name\": \"" + userGames[i].GetName() +
            "\", \"date\": \"" + userGames[i].getDate() + "\"}";
    }

    strGames += "]";

    return strGames;
}



 