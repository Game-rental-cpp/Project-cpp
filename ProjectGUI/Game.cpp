// Game.cpp
#include "Game.h"
#include "GameCRUD.h"

// Implementacja konstruktora
Game::Game(const std::string& name, int quantity, int nrOfLoans, float rate, std::map<std::string, int> userRates) : quantity(quantity), nrOfLoans(nrOfLoans) { this->name = name; this->rate = rate; this->userRates = userRates; }

// Implementacje funkcji z GameAbs
const std::string& Game::GetName() const {
    return name;
}

int Game::GetQuantity() const {
    return quantity;
}

int Game::GetNrOfLoans() const {
    return nrOfLoans;
}

void Game::SetQuantity(int quantity) {
    // Quantity cannot be negative
    if (quantity >= 0) {
        this->quantity = quantity;
        GameCRUD::updateGame(name, quantity, nrOfLoans, rate, userRates);
    }
}

void Game::SetNrOfLoans(int nrOfLoans) {
    this->nrOfLoans++;
    GameCRUD::updateGame(name, quantity, nrOfLoans, rate, userRates);
}


