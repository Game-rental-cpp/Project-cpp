// MyAccPanel.cpp
#include "MyAccPanel.h"
#include "MyAccPanel_Controller.h"
#include <string>
#include <string>
#include "UserNormal.h"
#include "UserPremium.h"
#include <vector>
#include "Style.h"


MyAccPanel::MyAccPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{

    logoutLabel = new wxStaticText(this, wxID_ANY, L"wylogowano pomyślnie", wxPoint(100, 250));
    logoutLabel->SetForegroundColour(COLOR_LBL);
    logoutLabel->SetFont(SetTheFont(12, true));

    userPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 10), wxSize(410, 500));

    loginLabel = new wxStaticText(userPanel, wxID_ANY, "", wxPoint(10, 0));
    loginLabel->SetForegroundColour(COLOR_LBL);
    loginLabel->SetFont(SetTheFont(12, true));

    // Creating a button
    logoutBtn = new wxButton(userPanel, wxID_ANY, "Wyloguj", wxPoint(GetClientSize().GetWidth() - 100, 0), wxSize(75, 30));
    logoutBtn->SetFont(SetTheFont(10).MakeBold());
    logoutBtn->SetBackgroundColour(COLOR_BACKGROUND_NAVBTN);
    logoutBtn->SetForegroundColour(COLOR_TEXT_BTN);

    premiumInput = new wxTextCtrl(userPanel, wxID_ANY, wxEmptyString, wxPoint(100, GetClientSize().GetHeight() - 50), wxSize(220, 30), wxBORDER_RAISED);
    premiumInput->SetHint("Wpisz kod, by zyskac konto premium");

    MyAccPanel_Controller* controller = new MyAccPanel_Controller(this, logoutLabel, userPanel, loginLabel, logoutBtn, premiumInput, gamesPanel);
    controller->BindEvents();

}

















