#pragma once
// MainPanel.h

#include <wx/textfile.h>
#include <wx/wx.h>
#include "Game.h"

class MainPanel : public wxPanel
{
public:
    MainPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);

private:
    wxButton* button;
    wxStaticText* label;

    // Deklaracja metody obs�ugi zdarzenia wxShowEvent
    void OnPanelShow(wxShowEvent& event);
    void LoadGames();
    int CountGames();
    Game CreateGameBasedOnFile(int i);
};


