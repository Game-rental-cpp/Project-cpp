// user.cpp

#include "user.h"
#include <algorithm>

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

void User::addUserGame(const std::string& name) {
    // Identyfikator mo�na stworzy� na podstawie wielko�ci wektora (prosta implementacja)
    int newId = static_cast<int>(userGames.size()) + 1;

    // Tworzymy now� gr� i dodajemy j� do wektora
    userGames.push_back(UserGame(newId, name, "current_date")); // Mo�esz dostosowa� date wed�ug potrzeb
}

void User::removeUserGame(int id) {
    // Usuwamy gr� na podstawie identyfikatora
    auto it = std::remove_if(userGames.begin(), userGames.end(),
        [id](const UserGame& game) { return game.getId() == id; });

    // Usuwamy elementy, kt�re zosta�y oznaczone do usuni�cia
    userGames.erase(it, userGames.end());
}
