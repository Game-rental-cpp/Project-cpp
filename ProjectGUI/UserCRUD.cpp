#define _CRT_SECURE_NO_WARNINGS

#include "UserCRUD.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

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

//creat
void UserCRUD::CreateUser(std::string login, std::string password) {
    // Open the file for writing
    std::ofstream outputFile("./Users/" + login + ".json");

    if (outputFile.is_open()) {
        // Write username and password to a file
        json userJson = {
            {"login:", login},
            {"password:", password},
            {"isPremium:", false}
        };
        outputFile << userJson.dump(4) << std::endl;

        outputFile.close();
    }
    else {
        // Handle the case where the file couldn't be opened
        std::cerr << "Unable to open the file for reading." << std::endl;
        return; // You might want to return an error code here or throw an exception
    }
}

//read
std::string UserCRUD::ReadLogged() {
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

std::string UserCRUD::ReadUser(std::string login) {
    // Open the file for reading
    std::ifstream inputFile("./Users/" + login + ".json");
    std::string loginContent;

    if (inputFile.is_open()) {
        // Read the content of the file
        std::stringstream buffer;
        buffer << inputFile.rdbuf();
        loginContent = buffer.str();

        inputFile.close();
        return loginContent;
    }
    else {
        // Handle the case where the file couldn't be opened
        std::cerr << "Unable to open the file for reading." << std::endl;
        return ""; // You might want to return an error code here or throw an exception
    }
}

//update
void UserCRUD::Update_logged(std::string newContent) {
    //Open the file for writing
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

void UserCRUD::UpdateUser(std::string login, std::string body) {
    //Open the file for writing
    std::ofstream inputFile("./Users/" + login + ".json", std::ios::trunc);
    if (inputFile.is_open()) {
        // Write the new content to the file
        inputFile << body;

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
bool UserCRUD::DoesExist(std::string login) {
    std::string filePath = "./Users/" + login + ".json";
    std::ifstream file(filePath.c_str()); 
    // Returns true if the file exists and is readable
    return file.good();
}



