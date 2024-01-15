// user.h
#pragma once

#include <string>
#include <vector>
#include <wx/datetime.h>
#include "GameAbs.h"

class User {
public:
    // Inner class
    class UserGame : public GameAbs {
    public:
        /* @param std::string& name */
        UserGame(const std::string& name);
        std::string getId() const;
        const std::string& GetName() const override;
        const float& GetRate() const override { return rate; };
        const std::map<std::string, int>& GetUserRates() const override { return userRates; };
        void SetRate(int r, std::string login) override;

        std::string getDate() const;
        void SetId(std::string idToSet) { id = idToSet; }
        void SetDate(std::string dateToSet) { date = dateToSet; }
    private:
        std::string id; // game unique id
        std::string date; // date of rental
    };

    /* @param std::string& login */
    User(const std::string& login);
    virtual ~User() = default;

    // Getters
    std::string getLogin() const;
    std::string getPassword() const;
    bool getPremium() const { return isPremium; }; 
    const std::vector<UserGame>& getUserGames() const; 


    // @param std::string& name
    // returns true if added successfully
    virtual bool addUserGame(const std::string& name);

    // @param std::string& id
    void removeUserGame(const std::string& id);

    void setUserGames(std::vector<UserGame>& newUserGamesVector);

    virtual std::string stringifyUser() { return ""; };
    std::string stringifyGames();

protected:
    std::string login;
    std::string password;
    bool isPremium = false;
    std::vector<UserGame> userGames; // Vector of UserGame
    void setPremium(bool value);
};
