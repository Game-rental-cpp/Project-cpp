// usernormal.h

#pragma once

#include "user.h"

class UserNormal : public User {
public:
    /* @param std::string& login */
    UserNormal(const std::string& login);
    virtual ~UserNormal() = default;

    bool addUserGame(const std::string& name)  override;
    std::string stringifyUser() override;
    //bool getPremium() const override { return false; };

};
