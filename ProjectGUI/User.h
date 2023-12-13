// user.h

#pragma once

#include <string>
#include <vector>
#include <wx/datetime.h>

class User {
public:
    // Klasa wewn¹trzna UserGame
    class UserGame {
    public:
        UserGame(const std::string& name);
        std::string getId() const;
        std::string getName() const;
        wxDateTime getDate() const;

        // Dodaj inne funkcje lub zmienne dla UserGame wed³ug potrzeb

    private:
        std::string id; // game unique id
        std::string name; // name
        wxDateTime date; // date of loan
    };

    User(const std::string& login);
    virtual ~User() = default;

    // Getters
    std::string getLogin() const;
    std::string getPassword() const;
    const std::vector<UserGame>& getUserGames() const; // Getter for the vector of UserGame

    // Add and remove functions
    virtual void addUserGame(const std::string& name);
    void removeUserGame(const std::string& id);

protected:
    std::string login;
    std::string password;
    std::vector<UserGame> userGames; // Vector of UserGame
};
