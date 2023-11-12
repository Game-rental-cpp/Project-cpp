#include "MainPanel_Logic.h"
#include <wx/dir.h>
#include <string>


using json = nlohmann::json;

//Ta funkcja tworzy obiekt typu Game na podstawie plików json
Game MainPanel_Logic::CreateGameFromJSON(int i)
{
    std::string name;
    int quantity;

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

            file.Close();
        }
    }

    Game game(name, quantity);

    return game;
}

std::vector<Game> MainPanel_Logic::vec;

std::vector<Game> MainPanel_Logic::fulfillGamesVector(int gameCount) {
    for (int i = 0; i < gameCount; i++)
    {
        Game game = MainPanel_Logic::CreateGameFromJSON(i);

        //wxLogMessage("ededewd");
        vec.push_back(game); // Dodawanie gry do wektora

    }
    return vec;
}

std::vector<Game> MainPanel_Logic::sortVector(std::vector<Game> gamesVector, int choice, int gameCount) {
    // Sortowanie obiektów w gamesVector wed³ug pola name
    switch (choice) {
        case 0:
            //sprto A-Z
            for (int i = 0; i < gameCount - 1; i++) {
                for (int j = 0; j < gameCount - i - 1; j++) {
                    if (gamesVector[j].GetName() > gamesVector[j + 1].GetName()) {
                        // Zamieñ miejscami, jeœli warunek nie jest spe³niony
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
                        // Zamieñ miejscami, jeœli warunek nie jest spe³niony
                        std::swap(gamesVector[j], gamesVector[j + 1]);
                    }
                }
            }
           break;
    }
    return gamesVector;
}