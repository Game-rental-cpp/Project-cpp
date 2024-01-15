#include "MainPanel_Logic.h"

#include <wx/dir.h>
#include <string>
#include <wx/textfile.h>

#include "UserCRUD.h"
#include "GameCRUD.h"
#include "json.hpp"
#include "User.h"
#include "UserNormal.h"
#include "UserPremium.h"
#include <wx/wx.h>


using json = nlohmann::json;

/*
Ta funkcja tworzy obiekt typu Game na podstawie plików json
@param int i - the index number of a game.json file inside Games directory
@returns Game game - game model
*/
Game MainPanel_Logic::CreateGameFromJSON(int i)
{
    std::string name;
    int quantity;
    int nrOfRentals;
    float rate;
    std::map<std::string, int> userRates;

    wxString parentDir = wxGetCwd();
    wxString gamesDir = parentDir + "/Games";

    wxArrayString files;
    wxDir::GetAllFiles(gamesDir, &files, wxEmptyString, wxDIR_FILES);

    if (i >= 0 && i < files.GetCount()) {
        wxString filePath = files[i];
        wxTextFile file(filePath);

        if (file.Exists() && file.Open()) {
            wxString fileName = wxFileNameFromPath(filePath);
            //cut the .json extension from the name
            std::string truncatedFileName = fileName.ToStdString().substr(0, fileName.length() - 5);

            wxString fileContents = GameCRUD::readGame(truncatedFileName);
            json jsonData = json::parse(fileContents);

            name = jsonData["name"];
            quantity = jsonData["quantity"];
            nrOfRentals = jsonData["nrOfRentals"];
            rate = jsonData["rate"];
            userRates = jsonData["userRates"];

            file.Close();
        }
    }

    Game game(name, quantity, nrOfRentals, rate, userRates);

    return game;
}


/*
Creates vector of games
@param int gameCount - number of files inside Games directory
@returns std::vector<Game>
*/
std::vector<Game> MainPanel_Logic::fulfillGamesVector(int gameCount) {

    std::vector<Game> vector;

    for (int i = 0; i < gameCount; i++)
    {
        Game game = MainPanel_Logic::CreateGameFromJSON(i);

        vector.push_back(game); // Add game to vector

    }
    return vector;
}

/*
Function sorts elements of the given vector
@param std::vector<Game> gamesVector - vector we want to sort
@param int choice - 0 if A-Z; 1 if Z-A
@param int gamesCount - number of files inside Games directory
*/
std::vector<Game> MainPanel_Logic::sortVector(std::vector<Game> gamesVector, int choice, int gameCount) {
    // Sortowanie obiektów w gamesVector wed³ug pola name
    switch (choice) {
        case 0:
            //sort A-Z
            for (int i = 0; i < gameCount - 1; i++) {
                for (int j = 0; j < gameCount - i - 1; j++) {
                    if (gamesVector[j].GetName() > gamesVector[j + 1].GetName()) {
                        
                        std::swap(gamesVector[j], gamesVector[j + 1]);
                    }
                }
            }

           break;
        case 1:
            //sort Z-A
            for (int i = 0; i < gameCount - 1; i++) {
                for (int j = 0; j < gameCount - i - 1; j++) {
                    if (gamesVector[j].GetName() < gamesVector[j + 1].GetName()) {
                        
                        std::swap(gamesVector[j], gamesVector[j + 1]);
                    }
                }
            }
            break;
        case 2:
            //Nr of rentals
            for (int i = 0; i < gameCount - 1; i++) {
                for (int j = 0; j < gameCount - i - 1; j++) {
                    if (gamesVector[j].GetNrOfRentals() < gamesVector[j + 1].GetNrOfRentals()) {
                        
                        std::swap(gamesVector[j], gamesVector[j + 1]);
                    }
                }
            }
           break;
        case 3:
            //Rate
            for (int i = 0; i < gameCount - 1; i++) {
                for (int j = 0; j < gameCount - i - 1; j++) {
                    if (gamesVector[j].GetRate() < gamesVector[j + 1].GetRate()) {

                        std::swap(gamesVector[j], gamesVector[j + 1]);
                    }
                }
            }
            break;
    }
    return gamesVector;
}



User* MainPanel_Logic::createUser() {
    return MainPanel_Logic::user;
}

User* MainPanel_Logic::user = nullptr;

void MainPanel_Logic::SetUser(User* u) {
    MainPanel_Logic::user = u;
}