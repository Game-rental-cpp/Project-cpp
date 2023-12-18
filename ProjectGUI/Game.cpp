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


void Game::SetRate(int r, std::string login) {
    // SprawdŸ, czy u¿ytkownik ju¿ oceni³ tê grê
    //this->rate = 5.0;
    auto it = userRates.find(login);
    if (it != userRates.end()) {
        // U¿ytkownik ju¿ wczeœniej oceni³ tê grê, wiêc edytuj ocenê
        it->second = r;
    }
    else {
        // Dodaj now¹ ocenê u¿ytkownika do mapy
        userRates[login] = r;
    }

    // Zaktualizuj œredni¹ ocenê
    int totalRates = 0;
    for (const auto& pair : userRates) {
        totalRates += pair.second;
    }

    if (!userRates.empty()) {
        this->rate = static_cast<float>(totalRates) / userRates.size();
    }
    else {
        // Jeœli userRates jest puste, ustaw rate na 0 lub inny domyœlny wartoœæ
        this->rate = 0.0f;
    }
    //wxLogMessage("%d", rate);
    //rate = 5;

    // Przyk³adowa logika obs³ugi aktualizacji pliku JSON lub innej formy przechowywania danych
    // w zale¿noœci od Twoich potrzeb
    //GameCRUD::updateGame(name, quantity, nrOfLoans, rate, userRates);
}