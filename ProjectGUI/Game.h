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
    Game(const std::string& name, int quantity, int nrOfLoans);

    const std::string& GetName() const override;
    int GetQuantity() const;
    int GetNrOfLoans() const;
    void SetQuantity(int quantity);
    void SetNrOfLoans(int nrOfLoans);
};
