#pragma once

#include <wx/wx.h>
#include "UserCRUD.h"
#include "user.h"

class MyAccPanel : public wxPanel
{
public:
    MyAccPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
    User* GetUser()  { return user; }

private:
    wxButton* button;
    wxStaticText* label;
    User* user;

    void OnPanelShow(wxShowEvent& event);
    void ChangeToPremium(wxCommandEvent& event);
    void LogOut();
};