#pragma once
#include <wx/wx.h>
#include "User.h"
#include "Game.h"

class MyAccPanel;

class MyAccPanel_Controller : public wxPanel
{
public:
    MyAccPanel_Controller(MyAccPanel* parenEl, wxStaticText* logoutLabel,
    wxPanel* userPanel,
    wxStaticText* loginLabel,
    wxButton* logoutBtn,
    wxTextCtrl* premiumInput,
    wxScrolledWindow* gamesPanel);

    void BindEvents();
 

private:
    MyAccPanel* parentEl;
    wxStaticText* logoutLabel;
    wxPanel* userPanel;
    wxStaticText* loginLabel;
    wxButton* logoutBtn;
    wxTextCtrl* premiumInput;
    wxScrolledWindow* gamesPanel;
    
    void OnPanelShow(wxShowEvent& event);
    void LogOut(wxCommandEvent& event);
    void OnEnterPressed(wxKeyEvent& event);
    void UpdateGamesPanel();
    void UpdateUserGames(wxCommandEvent& event, std::string gameName);
    void OnMouseHover(wxMouseEvent& event);
    void RateGame(wxCommandEvent& event, std::string gameName, std::string login);
    void OnOcenButtonClick(wxCommandEvent& event, Game* game, std::string login);
    void OnRadioSelect(wxCommandEvent& event);

    int newRate;

};



