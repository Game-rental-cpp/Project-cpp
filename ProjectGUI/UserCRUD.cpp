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
        return false; // You might want to return an error code here or throw an exception
    }
}

//creat
static void CreateUser(std::string login, std::string password) {
    // Open the file for writing
    std::ofstream outputFile(".Users/" +login + ".json");
    
    if (outputFile.is_open()) {
        // Write username and password to a file
        outputFile << "login: " << login << std::endl;
        outputFile << "password: " << password << std::endl;
        outputFile << "isPremium: " << false << std::endl;

        outputFile.close();
    }
    else {
        // Handle the case where the file couldn't be opened
        std::cerr << "Unable to open the file for reading." << std::endl;
        return; // You might want to return an error code here or throw an exception
    }
}

//read
static std::string ReadLogged() {
    // Open the file for reading
    std::ifstream inputFile("./Users/_logged.txt");
    std::string loggedContent;

    if (inputFile.is_open()) {
        // Read the content of the file
        std::stringstream buffer;
        buffer << inputFile.rdbuf();
        loggedContent = buffer.str();

        inputFile.close();
        return loggedContent;
    }
    else {
        // Handle the case where the file couldn't be opened
        std::cerr << "Unable to open the file for reading." << std::endl;
        return ""; // You might want to return an error code here or throw an exception
    }
}

//update
static void Update_logged(std::string newContent){
    //Open the file for 
    std::ofstream inputFile("./Users/_logged.txt", std::ios::trunc);

    if (inputFile.is_open()) {
        // Write the new content to the file
        inputFile << newContent;

        inputFile.close();
    }
    else {
        // Handle the case where the file couldn't be opened
        std::cerr << "Unable to open the file for reading." << std::endl;
        return; // You might want to return an error code here or throw an exception
    }
}

//delete

//other
static bool DoesExist(std::string) 
{

}
