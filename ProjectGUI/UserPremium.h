// userpremium.h

#pragma once

#include "user.h"

class UserPremium : public User {
public:
    /* @param std::string& login */
    UserPremium(const std::string& login);
    virtual ~UserPremium() = default;

    // Getter
    bool isPremium() const;

};
