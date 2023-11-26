#pragma once
// MainPanel.h
#include <wx/wx.h>
#include "Game.h"


class MainPanel : public wxPanel
{
public:
    MainPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);

private:
    wxStaticText* label;
    wxScrolledWindow* gamesPanel;
    wxChoice* sortChoice;
    wxTextCtrl* searchInput;
    wxButton* resetBtn;

    int previousSortChoice;
    // Deklaracja metody obs³ugi zdarzenia wxShowEvent
    void OnPanelShow(wxShowEvent& event);
    void OnChoice(wxCommandEvent& event);
    void UpdateGamesPanel(std::vector<Game>);
    void UpdateGame(wxCommandEvent& event);
    void OnSearchChange(wxCommandEvent& event);
    void OnResetButtonClick(wxCommandEvent& event);
    void OnMouseHover(wxMouseEvent& event);
};


