#define _CRT_SECURE_NO_WARNINGS

#include "GameCRUD.h"
#include <wx/dir.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

//This function count files in the Games directory
int GameCRUD::countGames() {
    //Take the path to GameCRUD.cpp
    wxString parentDir = wxGetCwd();

    // Concatenate it with the path of the Games directory
    wxString gamesDir = parentDir + "/Games";

    // Count files inside the Games directory
    int fileCount = 0;
    wxDir dir(gamesDir);
    if (dir.IsOpened()) {
        wxString filename;
        bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
        while (cont) {
            fileCount++;
            cont = dir.GetNext(&filename);
        }
    }
    return fileCount;


}

std::string GameCRUD::readGame(std::string fileName) {
    // Open the file for reading
    std::ifstream inputFile("./Games/"+fileName+".json");


    if (inputFile.is_open()) {
        // Read the content of the file
        std::stringstream buffer;
        buffer << inputFile.rdbuf();
        std::string fileContent = buffer.str();

        return fileContent;

       
    }
    else {
        // Handle the case where the file couldn't be opened
        std::cerr << "Unable to open the file for reading." << std::endl;
        return "false"; // You might want to return an error code here or throw an exception.
    }
    return fileName;
}