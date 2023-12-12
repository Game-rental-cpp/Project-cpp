// user_normal.h

#pragma once

#include "user.h"

class UserNormal : public User {
public:
    UserNormal(const std::string& login, const std::string& password);
    virtual ~UserNormal() = default;

    // Override
    void someVirtualFunction() const override;

    // Getter
    bool getIsPremium() const;

private:
    const bool isPremium;
};
