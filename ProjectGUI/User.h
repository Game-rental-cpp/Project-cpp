// user.h
#pragma once

#include <string>
#include <vector>
#include <wx/datetime.h>

class User {
public:
    // Inner class
    class UserGame {
    public:
        /* @param std::string& name */
        UserGame(const std::string& name);
        std::string getId() const;
        std::string getName() const;
        std::string getDate() const;

    private:
        std::string id; // game unique id
        std::string name; // name
        std::string date; // date of loan
    };

    /* @param std::string& login */
    User(const std::string& login);
    virtual ~User() = default;

    // Getters
    std::string getLogin() const;
    std::string getPassword() const;
    const std::vector<UserGame>& getUserGames() const; // Getter for the vector of UserGame


    // @param std::string& name
    // returns true if added successfully
    virtual bool addUserGame(const std::string& name);

    // @param std::string& id
    void removeUserGame(const std::string& id);

    void setUserGames(std::vector<UserGame>& newUserGamesVector);

    std::string stringifyGames();

protected:
    std::string login;
    std::string password;
    std::vector<UserGame> userGames; // Vector of UserGame
};
