#pragma once

#include <string>

class Game {
public:
    Game(const std::string& name, int quantity, int nrOfLoans);

    // getters
    const std::string& GetName() const;
    int GetQuantity() const;
    int GetNrOfLoans() const;

    // setters
    //void SetName(const std::string& name);
    void SetQuantity(int quantity);
    void SetNrOfLoans(int nrOfLoans);

private:
    std::string name;
    int quantity;
    int nrOfLoans;
};
