#pragma once

#include <wx/textfile.h>
#include <wx/wx.h>
#include "Game.h"
#include "GameCRUD.h"
#include "json.hpp"
#include <vector>

class MainPanel_Logic : public wxPanel
{
public:
//    MainPanel_Logic();
//private:


    // Deklaracja metody obs³ugi zdarzenia wxShowEvent

    //void LoadGames();
    //int CountGames();
    static Game CreateGameFromJSON(int i);
    static std::vector<Game> fulfillGamesVector(int n);
    static std::vector<Game> sortVector(std::vector<Game> gamesVector, int choice, int gameCount);
    //void UpdateGame(wxCommandEvent& event);
    /*void CreateOrShowGamesPanel();
    void HideGamesPanel();*/

private:
    static std::vector<Game> vec;
};
