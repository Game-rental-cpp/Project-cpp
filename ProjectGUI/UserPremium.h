// userpremium.h

#pragma once

#include "user.h"

class UserPremium : public User {
public:
    /* @param std::string& login */
    UserPremium(const std::string& login);
    virtual ~UserPremium() = default;
    bool getPremium() const override { return true; };

    //std::string stringifyUser() override;
    //std::string stringifyUser();

    // Getter
    //bool isPremium() const;

};
