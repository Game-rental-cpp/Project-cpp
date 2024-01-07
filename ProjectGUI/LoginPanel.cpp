// LoginPanel.cpp
#include "LoginPanel.h"
#include "LoginPanel_Controller.h"
#include "UserCRUD.h"
#include "Style.h"
#include <wx/wx.h>

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

    loginBtn = new wxButton(formsPanel, wxID_ANY, "Zaloguj", wxPoint(140, 95), wxSize(100, 30));
    loginBtn->SetFont(SetTheFont(10, true));
    loginBtn->SetBackgroundColour(COLOR_BACKGROUND_LOGINBTN);
    loginBtn->SetForegroundColour(COLOR_TEXT_LOGINBTN);

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

    signupBtn = new wxButton(formsPanel, wxID_ANY, "Zarejestruj", wxPoint(140, 265), wxSize(100, 30));
    signupBtn->SetFont(SetTheFont(10, true));
    signupBtn->SetBackgroundColour(COLOR_BACKGROUND_LOGINBTN);
    signupBtn->SetForegroundColour(COLOR_TEXT_LOGINBTN);


    std::string Requirements;
    Requirements += "* Login musi zawierać od " + std::to_string(MIN_CHAR_NAME) + " do " + std::to_string(MAX_CHAR_NAME) + " znaków " 
        + "i może składać się tylko z cyfr,\n podkreśleń, myślników lub małych i dużych liter alfabetu angielskiego.\n"
        + "\n* Hasło musi zawierać: \n \t" 
        + "- od " + std::to_string(MIN_CHAR_PASSWORD) + " do " + std::to_string(MAX_CHAR_PASSWORD) + " znaków \n \t"
        + "- małe litery\n \t"
        + "- duże litery\n \t"
        + "- cyfry\n \t"
        + "- znaki specjalne";
    wxStaticText* reqsLabel = new wxStaticText(formsPanel, wxID_ANY, Requirements, wxPoint(10, 310));
   
    LoginPanel_Controller* controller = new LoginPanel_Controller(this, successLabel, formsPanel,
        loginName, loginPassword, loginBtn, signupName, signupPassword1, signupPassword2, signupBtn);
    controller->BindEvents();
}
