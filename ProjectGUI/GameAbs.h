#pragma once

#include <string>

class GameAbs {
public:
    virtual ~GameAbs() = default;

    virtual const std::string& GetName() const = 0;
    virtual int GetQuantity() const = 0;
    virtual int GetNrOfLoans() const = 0;

    virtual void SetQuantity(int quantity) = 0;
    virtual void SetNrOfLoans(int nrOfLoans) = 0;
};

