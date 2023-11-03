#pragma once


#include <string>

class Game {
public:
    Game(const std::string& name, int quantity);

    // Metody dost�powe do p�l name i quantity
    const std::string& GetName() const;
    int GetQuantity() const;

    // Metody ustawiaj�ce warto�ci p�l name i quantity
    void SetName(const std::string& name);
    void SetQuantity(int quantity);
    void UpdateTextFile(int quantity);

private:
    std::string name;
    int quantity;
};


