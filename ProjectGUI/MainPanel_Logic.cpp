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