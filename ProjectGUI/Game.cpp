#include <string>
#include <fstream>
#include <filesystem>

class Game {
public:
    Game(const std::string& name, int quantity);

    // Metody dost�powe do p�l name i quantity
    const std::string& GetName() const;
    int GetQuantity() const;

    // Metody ustawiaj�ce warto�ci p�l name i quantity
    void SetName(const std::string& name);
    void SetQuantity(int quantity);

    //metoda aktualizuj�ca pliki txt
    void UpdateTextFile(int quantity);

private:
    std::string name;
    int quantity;
};

// Implementacja konstruktora
Game::Game(const std::string& name, int quantity) : name(name), quantity(quantity) {}

// Implementacja getter�w
const std::string& Game::GetName() const {
    return name;
}

int Game::GetQuantity() const {
    return quantity;
}

// Implementacja setter�w
void Game::SetName(const std::string& name) {
    this->name = name;
}

void Game::SetQuantity(int quantity) {
    this->quantity = quantity;

    std::string folderPath = "./Games/"; // �cie�ka do folderu "Games"
    std::string fileName = folderPath + name + ".txt"; // Tworzymy pe�n� �cie�k� do pliku
    std::ofstream file(fileName);
    if (file.is_open()) {
        file << "name: " << name << "\n";
        file << "quantity: " << quantity << "\n";
        file.close();
    }
}


void UpdateTextFile(int quantity) {

}