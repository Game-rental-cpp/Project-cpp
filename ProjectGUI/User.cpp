// user.cpp

#include "user.h"
#include "UserCRUD.h"
#include "uuid_v4.h"

//#include <uuid/uuid.h> // Include the header for UUID generation

User::User(const std::string& login)
    : login(login) {
    // creates user from json file
    // UserCRUD::ReadUser(login);
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

User::UserGame::UserGame(const std::string& name) : name(name) {
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

std::string User::UserGame::getName() const {
    return name;
}

std::string User::UserGame::getDate() const {
    return date;
}

bool User::addUserGame(const std::string& name) {
    // Tworzymy now¹ grê i dodajemy j¹ do wektora
    userGames.push_back(UserGame(name));
    //update user json file
    return true;
}

void User::removeUserGame(const std::string& id) {
    // Iteruj przez wektor
    for (auto it = userGames.begin(); it != userGames.end(); ++it) {
        // SprawdŸ, czy identyfikator gry pasuje
        if (it->getId() == id) {
            // Usuñ element
            userGames.erase(it);
            //update user json file
            //UserCRUD::UpdateUser(std::string login, std::string stringifiedUser);
            break; // Przerwij pêtlê, poniewa¿ element zosta³ znaleziony i usuniêty
        }
    }
}

std::string User::stringifyGames() {
    std::string strGames = "[";

    for (int i = 0; i < userGames.size(); i++) {
        if (i > 0) {
            strGames += ", ";
        }

        // Formatuj obiekt JSON dla ka¿dej gry z w³asnym formatem daty
        strGames += "{\"id\": \"" + userGames[i].getId() + "\", \"name\": \"" + userGames[i].getName() +
            "\", \"date\": \"" + userGames[i].getDate() + "\"}";
    }

    strGames += "]";

    return strGames;
}


 