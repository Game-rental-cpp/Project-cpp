#define _CRT_SECURE_NO_WARNINGS

#include "UserCRUD.h"
#include <iostream>
#include <fstream>
#include <sstream>


//This function checks if someone is logged in (if _logged.txt is empty or full)
bool UserCRUD::isLogged() {
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