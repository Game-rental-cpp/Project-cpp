#pragma once

#include "GameAbs.h"
#include "GameCRUD.h"

class Game : public GameAbs {
public:
    Game(const std::string& name, int quantity, int nrOfLoans);

    // Implementacje funkcji z GameAbs
    const std::string& GetName() const override;
    int GetQuantity() const override;
    int GetNrOfLoans() const override;
    void SetQuantity(int quantity) override;
    void SetNrOfLoans(int nrOfLoans) override;

private:
    std::string name;
    int quantity;
    int nrOfLoans;
};

