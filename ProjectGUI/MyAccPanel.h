#pragma once

#include <wx/wx.h>
#include "UserCRUD.h"
#include "user.h"

class MyAccPanel : public wxPanel
{
public:
    MyAccPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
    void SetUser(User* u){user = u;}

private:
    wxStaticText* logoutLabel;
    wxPanel* userPanel;
    wxStaticText* loginLabel;
    wxButton* logoutBtn;
    wxTextCtrl* premiumInput;
    wxScrolledWindow* gamesPanel;

    User* user;

};