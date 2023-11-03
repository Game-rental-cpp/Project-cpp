#pragma once


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
    void UpdateTextFile(int quantity);

private:
    std::string name;
    int quantity;
};


