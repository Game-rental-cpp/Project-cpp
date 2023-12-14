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

    userPanel = new wxPanel(this, wxID_ANY, wxPoint(10, 10), wxSize(410, 500));
    // Tworzenie przycisku
    logoutBtn = new wxButton(userPanel, wxID_ANY, "Wyloguj", wxPoint(10, GetClientSize().GetHeight()-100));
    //button->Bind(wxEVT_BUTTON, &MyAccPanel::LoadUser, this);
    logoutBtn->Bind(wxEVT_BUTTON, &MyAccPanel::LogOut, this);

    premiumInput = new wxTextCtrl(userPanel, wxID_ANY, wxEmptyString, wxPoint(GetClientSize().GetWidth() - 10 - 30 - 190, GetClientSize().GetHeight() - 100), wxSize(190, 30), wxBORDER_RAISED);
    premiumInput->Bind(wxEVT_CHAR_HOOK, &MyAccPanel::OnEnterPressed, this, wxID_ANY);
    premiumInput->SetHint("Wpisz kod, by zyskaæ konto premium");
    // Tworzenie etykiety



    this->SetBackgroundColour(RED); // Set background color (optional)


    //debugowanie
   /* if(isLogged())
        wxLogMessage("ktos jest zalogowany");
    else
        wxLogMessage("nikt nie jest zalogowany");*/
    MyAccPanel_Controller* controller = new MyAccPanel_Controller(this);
    controller->BindEvents();

    //Bind(wxEVT_SHOW, &MyAccPanel::OnPanelShow, this);
}















void MyAccPanel::OnEnterPressed(wxKeyEvent& event) {
    // SDetect Enter key
    if (event.GetKeyCode() == WXK_RETURN) {
        wxString enteredText = premiumInput->GetValue();
        premiumInput->SetValue("");
        
        if (enteredText == "PREMIUM") {
            premiumInput->Hide();

            wxLogMessage("Jesteœ cz³onkiem premium");

            std::vector<User::UserGame> userGames = user->getUserGames();
            delete user;
            //pobierz login przez cruda albo od starego usera.
            // Utwórz nowego u¿ytkownika typu UserPremium, ale nadal u¿ywaj¹c istniej¹cego obiektu
            user = new (user) UserPremium("login_premium");
            user->setUserGames(userGames);

        } else
            wxLogMessage("Nieprawid³owy kod");
    }


    event.Skip();
}

void MyAccPanel::LogOut(wxCommandEvent& event) {
    userPanel->Hide();
    logoutLabel->Show();
    //usuñ usera i pusty string do _logged.txt
    //user.reset();
    
}