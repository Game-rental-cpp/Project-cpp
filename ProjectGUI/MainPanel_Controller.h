#pragma once
#include <wx/wx.h>
#include <vector>
#include "Game.h"
#include "User.h"

class MainPanel;

class MainPanel_Controller : public wxPanel
{
public:
    MainPanel_Controller(MainPanel* parenEl, wxTextCtrl* searchInput, wxButton* resetBtn, wxChoice* sortChoice);

    static std::vector<Game> updateGame(wxString buttonName, wxPanel* gamesPanel, std::vector<Game> gamesVector);
    static void disableButton(const wxString& buttonName);
    void BindEvents();
    void OnShowPanel(wxShowEvent& event);
    //void SetUser(User* u) { user = u; }

private:
    MainPanel* parentEl;
    wxTextCtrl* searchInput;
    wxButton* resetBtn;
    wxChoice* sortChoice;
    wxScrolledWindow* gamesPanel;

    std::vector<Game> gamesVector;
    int previousSortChoice;
    User* user;

    void OnSearchChange(wxCommandEvent& event);
    void UpdateGamesPanel(std::vector<Game> gamesVector);
    void OnMouseHover(wxMouseEvent& event);
    void UpdateGame(wxCommandEvent& event);
    void OnChoice(wxCommandEvent& event);
    void OnResetButtonClick(wxCommandEvent& event);

};



