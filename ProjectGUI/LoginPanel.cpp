// LoginPanel.cpp
#include "LoginPanel.h"
#include <wx/wx.h>

LoginPanel::LoginPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{

    // Tworzenie i ukrywanie etykiety sukces
    successLabel = new wxStaticText(this, wxID_ANY, "Zalogowano", wxPoint(10, 50));
    successLabel->Hide();

    // Tworzenie panela z formularzami
    formsPanel = new wxPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(410, 500));

    // Tworzenie formularza Zaloguj
    loginName = new wxTextCtrl(formsPanel, wxID_ANY, "login", wxPoint(10, 0), wxSize(200, 20));
    loginPassword = new wxTextCtrl(formsPanel, wxID_ANY, "login pass", wxPoint(10, 30), wxSize(200, 20));
    loginBtn = new wxButton(formsPanel, wxID_ANY, "Zaloguj się", wxPoint(10, 60));

    // Tworzenie formularza Zarejestruj
    signupName = new wxTextCtrl(formsPanel, wxID_ANY, "signup", wxPoint(10, 110), wxSize(200, 20));
    signupPassword1 = new wxTextCtrl(formsPanel, wxID_ANY, "signup password", wxPoint(10, 140), wxSize(200, 20));
    signupPassword2 = new wxTextCtrl(formsPanel, wxID_ANY, "confirm password", wxPoint(10, 170), wxSize(200, 20));
    signupBtn = new wxButton(formsPanel, wxID_ANY, "Zarejestruj się", wxPoint(10, 200));

    loginBtn->Bind(wxEVT_BUTTON, &LoginPanel::OnLogin, this);
    //signupBtn->Bind(wxEVT_BUTTON, &FormsPanel::OnSignup, this);
}

// Funkcja obsługi zdarzenia po naciśnięciu przycisku "Zaloguj się"
void LoginPanel::OnLogin(wxCommandEvent& event)
{
    std::string userLoginName = loginName->GetValue().ToStdString();

    // Sprawdzanie czy istnieje użytkownik o podanym loginie
    //if (!UserCRUD::DoesExist(userLoginName))
    if (false)
    {
        wxMessageDialog* noKnownUserDlg = new wxMessageDialog(this, "Brak użytkownika o takim loginie.", "Błąd");
        noKnownUserDlg->ShowModal();
        return;
    }

    // Sprawdzanie hasła
    //if (UserCRUD::ReadPassword(userLoginName) != loginPass->GetValue().ToStdString())
    if (true)
    {
        wxMessageDialog* incorrectPasswordDlg = new wxMessageDialog(this, "Nieprawidłowe hasło.", "Błąd");
        incorrectPasswordDlg->ShowModal();
        return;
    }

    // Logowanie użytkownika
    // UserCRUD::Update_logged(userLoginName);
}
