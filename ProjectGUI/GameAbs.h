#pragma once

#include <string>
#include <map>

class GameAbs {
protected:
    std::string name;
    float rate;
    std::map<std::string, int> userRates;  /

public:
    virtual ~GameAbs() = default;

    virtual const std::string& GetName() const = 0;
    virtual const float& GetRate() const = 0;
    virtual const std::map<std::string, int>& GetUserRates() const = 0;
    virtual void SetRate(int r, std::string login) = 0;
};
