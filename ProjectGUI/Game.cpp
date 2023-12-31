// Game.cpp
#include "Game.h"
#include "GameCRUD.h"

// Implementacja konstruktora
Game::Game(const std::string& name, int quantity, int nrOfLoans) : quantity(quantity), nrOfLoans(nrOfLoans) { this->name = name; }

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
        GameCRUD::updateGame(name, quantity, nrOfLoans);
    }
}

void Game::SetNrOfLoans(int nrOfLoans) {
    this->nrOfLoans++;
    GameCRUD::updateGame(name, quantity, nrOfLoans);
}
