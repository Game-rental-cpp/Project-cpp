#pragma once
// MainPanel.h
#include "MainPanel.h"
#include "MainPanel_Logic.h"
#include <wx/textfile.h>
#include <wx/wx.h>
#include "Game.h"
#include "GameCRUD.h"
#include "json.hpp"
#include <vector>

class MainPanel : public wxPanel
{
public:
    MainPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);

private:
    wxButton* button;
    wxStaticText* label;
    wxPanel* gamesPanel;
    wxChoice* sortChoice;

    // Deklaracja metody obs³ugi zdarzenia wxShowEvent
    void OnPanelShow(wxShowEvent& event);
    void OnChoice(wxCommandEvent& event);
    void UpdateGamesPanel(std::vector<Game>);
    //int CountGames();
    Game CreateGameBasedOnFile(int i);
    void UpdateGame(wxCommandEvent& event);
    /*void CreateOrShowGamesPanel();
    void HideGamesPanel();*/
};


