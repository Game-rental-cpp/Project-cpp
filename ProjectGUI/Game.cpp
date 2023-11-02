#include <string>

class Game {
public:
    Game(const std::string& name, int quantity);

    // Metody dostêpowe do pól name i quantity
    const std::string& GetName() const;
    int GetQuantity() const;

    // Metody ustawiaj¹ce wartoœci pól name i quantity
    void SetName(const std::string& name);
    void SetQuantity(int quantity);

private:
    std::string name;
    int quantity;
};

// Implementacja konstruktora
Game::Game(const std::string& name, int quantity) : name(name), quantity(quantity) {}

// Implementacja getterów
const std::string& Game::GetName() const {
    return name;
}

int Game::GetQuantity() const {
    return quantity;
}

// Implementacja setterów
void Game::SetName(const std::string& name) {
    this->name = name;
}

void Game::SetQuantity(int quantity) {
    this->quantity = quantity;
}
