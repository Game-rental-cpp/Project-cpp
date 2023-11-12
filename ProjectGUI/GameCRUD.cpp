#define _CRT_SECURE_NO_WARNINGS

#include "GameCRUD.h"
#include <wx/dir.h>
#include <string>

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
    return fileName;
}