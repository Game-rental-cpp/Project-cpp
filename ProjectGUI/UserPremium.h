// userpremium.h

#pragma once

#include "user.h"

class UserPremium : public User {
public:
    /* @param std::string& login */
    UserPremium(const std::string& login);
    virtual ~UserPremium() = default;
    std::string stringifyUser() override;
    //bool addUserGame(const std::string& name) override;

};
