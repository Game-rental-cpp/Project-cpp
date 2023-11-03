#include "MainFrame_Logic.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

//ta funkcja sprawdza czy kto� jest zalogowany (czy _logged.txt jest pusty czy zape�niony)
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