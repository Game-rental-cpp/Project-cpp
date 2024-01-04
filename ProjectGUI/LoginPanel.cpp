// LoginPanel.cpp
#include "LoginPanel.h"
#include "LoginPanel_Logic.h"
//#include "LoginPanel_Length_Reqs.h"
#include "UserCRUD.h"
#include "Style.h"
#include <wx/wx.h>

constexpr int MIN_CHAR_NAME = 3;
constexpr int MAX_CHAR_NAME = 15;
constexpr int MIN_CHAR_PASSWORD = 8;
constexpr int MAX_CHAR_PASSWORD = 40;

LoginPanel::LoginPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{   
    successLabel = new wxStaticText(this, wxID_ANY, "Zalogowano", wxPoint(145, 120));
    successLabel->SetFont(SetTheFont(15, true));

    formsPanel = new wxPanel(this, wxID_ANY, wxPoint(10, 10), wxSize(410, 500));

    // Log-in form
    loginPrompt = new wxStaticText(formsPanel, wxID_ANY, "Zaloguj się", wxPoint(150, 0));
    loginPrompt->SetFont(SetTheFont(12, true));

    loginName = new wxTextCtrl(formsPanel, wxID_ANY, wxEmptyString, wxPoint(80, 30), wxSize(220, 22));
    loginName->SetHint("Login");
    loginName->SetFont(SetTheFont(11));

    loginPassword = new wxTextCtrl(formsPanel, wxID_ANY, wxEmptyString, wxPoint(80, 60), wxSize(220, 22), wxTE_PASSWORD);
    loginPassword->SetHint("Hasło");
    loginPassword->SetFont(SetTheFont(11));

    loginBtn = new wxButton(formsPanel, wxID_ANY, "Zaloguj", wxPoint(140, 95));
    loginBtn->SetFont(SetTheFont(11));

    // Sign-up form
    signupPrompt = new wxStaticText(formsPanel, wxID_ANY, "Nie masz konta? Zarejestruj się!", wxPoint(80, 140));
    signupPrompt->SetFont(SetTheFont(12, true));

    signupName = new wxTextCtrl(formsPanel, wxID_ANY, wxEmptyString, wxPoint(80, 170), wxSize(220, 22));
    signupName->SetHint("Login");
    signupName->SetFont(SetTheFont(11));

    signupPassword1 = new wxTextCtrl(formsPanel, wxID_ANY, wxEmptyString, wxPoint(80, 200), wxSize(220, 22), wxTE_PASSWORD);
    signupPassword1->SetHint("Hasło");
    signupPassword1->SetFont(SetTheFont(11));

    signupPassword2 = new wxTextCtrl(formsPanel, wxID_ANY, wxEmptyString, wxPoint(80, 230), wxSize(220, 22), wxTE_PASSWORD);
    signupPassword2->SetHint("Potwierdz hasło");
    signupPassword2->SetFont(SetTheFont(11));

    signupBtn = new wxButton(formsPanel, wxID_ANY, "Zarejestruj", wxPoint(140, 265));
    signupBtn->SetFont(SetTheFont(11));

    // TODO Username requirements
    std::string Requirements;
    Requirements += "Login musi zawierać od " + std::to_string(MIN_CHAR_NAME) + " do " + std::to_string(MAX_CHAR_NAME) + " znaków " 
        + "i składać się tylko z cyfr,\n podkreśleń, myślników oraz małych i dużych liter alfabetu angielskiego.\n";
    wxStaticText* nameReqsLabel = new wxStaticText(formsPanel, wxID_ANY, Requirements, wxPoint(10, 300));
    // TODO Password requirements
    std::string passReqs = "Hasło musi zawierać: \n \t od";
    wxStaticText* passReqsLabel = new wxStaticText(formsPanel, wxID_ANY, passReqs, wxPoint(70, 340));

    loginBtn->Bind(wxEVT_BUTTON, &LoginPanel::OnLogin, this);
    signupBtn->Bind(wxEVT_BUTTON, &LoginPanel::OnSignup, this);

    Bind(wxEVT_SHOW, &LoginPanel::OnPanelShow, this);
}


// Function called when LoginPanel is shown
void LoginPanel::OnPanelShow(wxShowEvent& event)
{   
    if (event.IsShown()) {
        loginName->Clear();
        loginPassword->Clear();
        signupName->Clear();
        signupPassword1->Clear();
        signupPassword2->Clear();

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

    if (!LoginPanel_Logic::LoginValidated(userLoginName, userLoginPassword, this))
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
    
    if (!LoginPanel_Logic::SignupValidated(userSignupName, userSignupPassword1, userSignupPassword2, this))
        return;

    formsPanel->Hide();
    successLabel->Show();
}

