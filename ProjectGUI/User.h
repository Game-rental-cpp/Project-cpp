// user.h

#pragma once

#include <string>
#include <vector>

class User {
public:
    // Klasa wewn¹trzna UserGame
    class UserGame {
    public:
        UserGame(int id, const std::string& name, const std::string& date)
            : id(id), name(name), date(date) {}

        int getId() const {
            return id;
        }

        std::string getName() const {
            return name;
        }

        std::string getDate() const {
            return date;
        }

        // Dodaj inne funkcje lub zmienne dla UserGame wed³ug potrzeb

    private:
        int id;
        std::string name;
        std::string date;
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
    void removeUserGame(int id);

private:
    std::string login;
    std::string password;
    std::vector<UserGame> userGames; // Vector of UserGame
};
