#include "MainFrame_Logic.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

//ta funkcja sprawdza czy ktoœ jest zalogowany (czy _logged.txt jest pusty czy zape³niony)
bool isLogged() {
    // Open the file for reading
    std::ifstream inputFile("./Users/_logged.txt");

    if (inputFile.is_open()) {
        // Read the content of the file
        std::stringstream buffer;
        buffer << inputFile.rdbuf();
        std::string fileContent = buffer.str();

        // Check if the file is empty (contains no characters other than whitespace)
        for (char c : fileContent) {
            if (!std::isspace(c)) {
                return true; // The file is not empty
            }
        }

        // The file is empty
        return false;
    }
    else {
        // Handle the case where the file couldn't be opened
        std::cerr << "Unable to open the file for reading." << std::endl;
        return false; // You might want to return an error code here or throw an exception.
    }
}