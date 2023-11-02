#pragma once
// MainPanel.h
//#ifndef MAINPANEL_H
//#define MAINPANEL_H

#include <wx/wx.h>
#include "Game.h"

class MainPanel : public wxPanel
{
public:
    MainPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);

private:
    wxButton* button;
    wxStaticText* label;

    // Deklaracja metody obs³ugi zdarzenia wxShowEvent
    void OnPanelShow(wxShowEvent& event);
    void LoadGamesFromFiles();
};

//#endif // MAINPANEL_H
