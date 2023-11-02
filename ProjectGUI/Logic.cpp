#include "Logic.h"
#include <iostream>
#include <fstream>

void mvcShowcase() {
    // Utw�rz i otw�rz plik do zapisu
    std::ofstream outputFile("mvc.txt");
    if (outputFile.is_open()) {
        // Wypisz co� do konsoli
        std::cout << "Funkcja mvcShowcase() zosta�a wywo�ana." << std::endl;

        // Zapisz tekst do pliku
        outputFile << "Funkcja mvcShowcase() zosta�a wywo�ana." << std::endl;

        // Zamknij plik
        outputFile.close();
    }
    else {
        // Obs�u� b��d, je�li nie uda�o si� otworzy� pliku
        std::cerr << "Nie uda�o si� otworzy� pliku do zapisu." << std::endl;
    }
}
