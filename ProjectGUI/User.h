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
        UserGame(const std::string& id, const std::string& name);
        std::string getId() const;
        std::string getName() const;
        wxDateTime getDate() const;

        // Dodaj inne funkcje lub zmienne dla UserGame wed³ug potrzeb

    private:
        std::string id;
        std::string name;
        wxDateTime date;
    };

    User(const std::string& login, const std::string& password);
    virtual ~User() = default;
    virtual void someVirtualFunction() const = 0;

    // Getters
    std::string getLogin() const;
    std::string getPassword() const;
    const std::vector<UserGame>& getUserGames() const; // Getter for the vector of UserGame

    // Add and remove functions
    void addUserGame(const std::string& name);
    void removeUserGame(const std::string& id);

private:
    std::string login;
    std::string password;
    std::vector<UserGame> userGames; // Vector of UserGame
};
