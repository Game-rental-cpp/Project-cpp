// Game.cpp
#include "Game.h"
#include "GameCRUD.h"


Game::Game(const std::string& name, int quantity, int nrOfRentals, float rate, std::map<std::string, int> userRates) : quantity(quantity), nrOfRentals(nrOfRentals) { this->name = name; this->rate = rate; this->userRates = userRates; }

const std::string& Game::GetName() const {
    return name;
}

int Game::GetQuantity() const {
    return quantity;
}

int Game::GetNrOfRentals() const {
    return nrOfRentals;
}

void Game::SetQuantity(int quantity) {
    // Quantity cannot be negative
    if (quantity >= 0) {
        this->quantity = quantity;
        GameCRUD::updateGame(name, quantity, nrOfRentals, rate, userRates);
    }
}

void Game::SetNrOfRentals(int nrOfRentals) {
    this->nrOfRentals++;
    GameCRUD::updateGame(name, quantity, nrOfRentals, rate, userRates);
}

/*
@param int r - user's rate;
@param string login - user's login
*/
void Game::SetRate(int r, std::string login) {
    
    if (r == 0) { // If r equals 0, this means the user canceled their previous rate    
        // delete user's rate in the map
        auto it = userRates.find(login);
        if (it != userRates.end()) {
            userRates.erase(it);
        }
    }
    else {
        auto it = userRates.find(login);
        if (it != userRates.end()) { // The user already did rated this game
            it->second = r; //update an existing rate
        }
        else {
            // Add new user's rate to the map
            userRates[login] = r;
        }
    }

    // Update an average rate
    int totalRates = 0;
    for (const auto& pair : userRates) {
        totalRates += pair.second;
    }

    if (!userRates.empty()) {
        this->rate = static_cast<float>(totalRates) / userRates.size();
    }
    else {
        // If userRates is empty, set rate on 0 
        this->rate = 0.0f;
    }

}
