#include "Logic.h"
#include <iostream>
#include <fstream>

void mvcShowcase() {
    // Utwórz i otwórz plik do zapisu
    std::ofstream outputFile("mvc.txt");
    if (outputFile.is_open()) {
        // Wypisz coœ do konsoli
        std::cout << "Funkcja mvcShowcase() zosta³a wywo³ana." << std::endl;

        // Zapisz tekst do pliku
        outputFile << "Funkcja mvcShowcase() zosta³a wywo³ana." << std::endl;

        // Zamknij plik
        outputFile.close();
    }
    else {
        // Obs³u¿ b³¹d, jeœli nie uda³o siê otworzyæ pliku
        std::cerr << "Nie uda³o siê otworzyæ pliku do zapisu." << std::endl;
    }
}
