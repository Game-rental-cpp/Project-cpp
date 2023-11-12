#pragma once

#include <wx/textfile.h>
#include <wx/wx.h>
#include "Game.h"
#include "GameCRUD.h"
#include "json.hpp"

class MainPanel_Logic : public wxPanel
{
public:
//    MainPanel_Logic();
//private:


    // Deklaracja metody obs³ugi zdarzenia wxShowEvent

    //void LoadGames();
    //int CountGames();
    static Game CreateGameFromJSON(int i);
    //void UpdateGame(wxCommandEvent& event);
    /*void CreateOrShowGamesPanel();
    void HideGamesPanel();*/
};
