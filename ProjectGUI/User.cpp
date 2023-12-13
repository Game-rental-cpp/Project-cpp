// user.cpp

#include "user.h"
//#include <uuid/uuid.h> // Include the header for UUID generation

User::User(const std::string& login, const std::string& password)
    : login(login), password(password) {}

std::string User::getLogin() const {
    return login;
}

std::string User::getPassword() const {
    return password;
}

const std::vector<User::UserGame>& User::getUserGames() const {
    return userGames;
}

User::UserGame::UserGame(const std::string& id, const std::string& name)
    : id(id), name(name) {
    // Ustaw dat� na obecn�
    date = wxDateTime::Now();
}

std::string User::UserGame::getId() const {
    return id;
}

std::string User::UserGame::getName() const {
    return name;
}

wxDateTime User::UserGame::getDate() const {
    return date;
}

void User::addUserGame(const std::string& name) {
    // TODO: change the way of creating ID (use std::uuid)
    //uuid_t uuid;
    //uuid_generate(uuid);
    //char uuidStr[37];
    //uuid_unparse(uuid, uuidStr);
    std::string uuidStr = "deded";
    std::string newId(uuidStr);

    // Tworzymy now� gr� i dodajemy j� do wektora
    userGames.push_back(UserGame(newId, name));
}

void User::removeUserGame(const std::string& id) {
    // Iteruj przez wektor
    for (auto it = userGames.begin(); it != userGames.end(); ++it) {
        // Sprawd�, czy identyfikator gry pasuje
        if (it->getId() == id) {
            // Usu� element
            userGames.erase(it);
            break; // Przerwij p�tl�, poniewa� element zosta� znaleziony i usuni�ty
        }
    }
}
