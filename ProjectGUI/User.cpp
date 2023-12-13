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
    // Identyfikator mo¿na stworzyæ na podstawie wielkoœci wektora (prosta implementacja)
    int newId = static_cast<int>(userGames.size()) + 1;

    // Tworzymy now¹ grê i dodajemy j¹ do wektora
    userGames.push_back(UserGame(newId, name, "current_date")); // Mo¿esz dostosowaæ date wed³ug potrzeb
}

void User::removeUserGame(int id) {
    // Usuwamy grê na podstawie identyfikatora
    auto it = std::remove_if(userGames.begin(), userGames.end(),
        [id](const UserGame& game) { return game.getId() == id; });

    // Usuwamy elementy, które zosta³y oznaczone do usuniêcia
    userGames.erase(it, userGames.end());
}
