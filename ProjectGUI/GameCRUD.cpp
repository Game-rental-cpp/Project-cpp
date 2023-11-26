#define _CRT_SECURE_NO_WARNINGS

#include "GameCRUD.h"
#include <wx/dir.h>
#include <string>
#include <iostream>
#include <fstream>
#include "json.hpp"


//in included json.hpp so now we can write the line below
using json = nlohmann::json;

/*
This function counts files in the Games directory
@returns int fileCount
*/
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

/*
This funnction return the content of the given file
@param string fileName (without extension) - name of the file we want to read
@returns string contents
*/
std::string GameCRUD::readGame(std::string fileName) {

    std::ifstream reader("./Games/" + fileName + ".json");

    if (reader.is_open()) {

        // Use nlohmann::json to read contents of the file
        json jsonData;
        reader >> jsonData;

        // Zamknij plik
        reader.close();

        // Return the contents in form of string
        return jsonData.dump();
       
    }
    else {
        // Handle the case where the file couldn't be opened
        std::cerr << "Unable to open the file for reading." << std::endl;
        return "false"; // You might want to return an error code here or throw an exception.
    }

}