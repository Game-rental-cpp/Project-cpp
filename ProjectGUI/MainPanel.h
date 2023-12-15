#pragma once
// MainPanel.h
#include <wx/wx.h>
#include "Game.h"
#include "user.h";

class MainPanel : public wxPanel
{
public:
    MainPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
    //void SetUser(User* u){user = u;}

private:
    wxStaticText* label;
    wxChoice* sortChoice;
    wxTextCtrl* searchInput;
    wxButton* resetBtn;
    //User* user;

};


