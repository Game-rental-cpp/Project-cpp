#pragma once
// MainPanel.h

#include <wx/textfile.h>
#include <wx/wx.h>
#include "Game.h"
#include "GameCRUD.h"

class MainPanel : public wxPanel
{
public:
    MainPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);

private:
    wxButton* button;
    wxStaticText* label;
    wxPanel* gamesPanel;

    // Deklaracja metody obs³ugi zdarzenia wxShowEvent
    void OnPanelShow(wxShowEvent& event);
    void LoadGames();
    //int CountGames();
    Game CreateGameBasedOnFile(int i);
    void UpdateGame(wxCommandEvent& event);
    /*void CreateOrShowGamesPanel();
    void HideGamesPanel();*/
};


