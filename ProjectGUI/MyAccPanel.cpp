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

    logoutLabel = new wxStaticText(this, wxID_ANY, "wylogowano pomyœlnie", wxPoint(10, 10));
    //logoutLabel->Hide();
    userPanel = new wxPanel(this, wxID_ANY, wxPoint(10, 10), wxSize(410, 500));
    // Tworzenie przycisku
    logoutBtn = new wxButton(userPanel, wxID_ANY, "Wyloguj", wxPoint(10, GetClientSize().GetHeight()-100));
    //button->Bind(wxEVT_BUTTON, &MyAccPanel::LoadUser, this);

    premiumInput = new wxTextCtrl(userPanel, wxID_ANY, wxEmptyString, wxPoint(GetClientSize().GetWidth() - 10 - 30 - 190, GetClientSize().GetHeight() - 100), wxSize(190, 30), wxBORDER_RAISED);
    premiumInput->SetHint("Wpisz kod, by zyskaæ konto premium");
    // Tworzenie etykiety



    this->SetBackgroundColour(RED); // Set background color (optional)


    //debugowanie
   /* if(isLogged())
        wxLogMessage("ktos jest zalogowany");
    else
        wxLogMessage("nikt nie jest zalogowany");*/
    MyAccPanel_Controller* controller = new MyAccPanel_Controller(this, logoutLabel, userPanel, loginLabel, logoutBtn, premiumInput, myGamesPanel);
    controller->BindEvents();



    //Bind(wxEVT_SHOW, &MyAccPanel::OnPanelShow, this);
}

















