// LoginPanel.cpp
#include "LoginPanel.h"
#include "LoginPanel_Logic.h"
#include "UserCRUD.h"
#include <wx/wx.h>



LoginPanel::LoginPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{

    // Tworzenie i ukrywanie etykiety sukces
    successLabel = new wxStaticText(this, wxID_ANY, "Zalogowano", wxPoint(10, 50));
    successLabel->Hide();

    // Tworzenie panela z formularzami
    formsPanel = new wxPanel(this, wxID_ANY, wxPoint(10, 50), wxSize(410, 500));

    // Tworzenie formularza Zaloguj
    loginPrompt = new wxStaticText(formsPanel, wxID_ANY, "Zaloguj się", wxPoint(10, 10));

    loginName = new wxTextCtrl(formsPanel, wxID_ANY, wxEmptyString, wxPoint(10, 40), wxSize(200, 20));
    loginName->SetHint("Login");

    loginPassword = new wxTextCtrl(formsPanel, wxID_ANY, wxEmptyString, wxPoint(10, 70), wxSize(200, 20));
    loginPassword->SetHint("Hasło");

    loginBtn = new wxButton(formsPanel, wxID_ANY, "Zaloguj", wxPoint(10, 100));

    // Tworzenie formularza Zarejestruj
    loginPrompt = new wxStaticText(formsPanel, wxID_ANY, "Nie masz konta? Zarejestruj się!", wxPoint(10, 160));

    signupName = new wxTextCtrl(formsPanel, wxID_ANY, wxEmptyString, wxPoint(10, 190), wxSize(200, 20));
    signupName->SetHint("Login");

    signupPassword1 = new wxTextCtrl(formsPanel, wxID_ANY, wxEmptyString, wxPoint(10, 220), wxSize(200, 20));
    signupPassword1->SetHint("Hasło");

    signupPassword2 = new wxTextCtrl(formsPanel, wxID_ANY, wxEmptyString, wxPoint(10, 250), wxSize(200, 20));
    signupPassword2->SetHint("Potwierdz hasło");

    signupBtn = new wxButton(formsPanel, wxID_ANY, "Zarejestruj", wxPoint(10, 280));


    loginBtn->Bind(wxEVT_BUTTON, &LoginPanel::OnLogin, this);
    signupBtn->Bind(wxEVT_BUTTON, &LoginPanel::OnSignup, this);

    Bind(wxEVT_SHOW, &LoginPanel::OnPanelShow, this);
}


// Function called when LoginPanel is shown
void LoginPanel::OnPanelShow(wxShowEvent& event)
{   
    if (event.IsShown()) {
        successLabel->Hide();
        formsPanel->Show();
    }

    event.Skip();
}

//  Function called when loginBtn is pressed
void LoginPanel::OnLogin(wxCommandEvent& event)
{
    std::string userLoginName = loginName->GetValue().ToStdString();
    std::string userLoginPassword = loginPassword->GetValue().ToStdString();

    if (!LoginPanel_Logic::loginValidated(userLoginName, userLoginPassword, this))
        return;

    formsPanel->Hide();
    successLabel->Show();
}

// Function called when signupBtn is pressed
void LoginPanel::OnSignup(wxCommandEvent& event)
{
    std::string userSignupName = signupName->GetValue().ToStdString();
    std::string userSignupPassword1 = signupPassword1->GetValue().ToStdString();
    std::string userSignupPassword2 = signupPassword2->GetValue().ToStdString();
    
    if (!LoginPanel_Logic::signupValidated(userSignupName, userSignupPassword1, userSignupPassword2, this))
        return;

    formsPanel->Hide();
    successLabel->Show();
}

