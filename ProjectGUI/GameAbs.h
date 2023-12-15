#pragma once

#include <string>

class GameAbs {
protected:
    std::string name;

public:
    virtual ~GameAbs() = default;

    virtual const std::string& GetName() const = 0;
};
