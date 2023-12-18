// Game.h
#pragma once

#include "GameAbs.h"
#include "GameCRUD.h"

class Game : public GameAbs {
private:
    //std::string name;
    int quantity;
    int nrOfLoans;
public:
    Game(const std::string& name, int quantity, int nrOfLoans, float rate, std::map<std::string, int> userRates);
    const float& GetRate() const override { return rate; };
    const std::map<std::string, int>& GetUserRates() const override {return userRates;};
    void SetRate(int r, std::string login) override;

    const std::string& GetName() const override;
    int GetQuantity() const;
    int GetNrOfLoans() const;
    void SetQuantity(int quantity);
    void SetNrOfLoans(int nrOfLoans);
};
