// user_normal.h

#pragma once

#include "user.h"

class UserNormal : public User {
public:
    UserNormal(const std::string& login);
    virtual ~UserNormal() = default;

    // Override
    bool addUserGame(const std::string& name)  override;

    // Getter
    bool isPremium() const; 

private:
    // Brak pola isPremium
};
