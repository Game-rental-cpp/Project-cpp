// FormsPanel.cpp
#include "FormsPanel.h"
#include <wx/wx.h>
#include <wx/textctrl.h>
#include <string>


FormsPanel::FormsPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    // Tworzenie formularza Zaloguj
    loginName = new wxTextCtrl(this, wxID_ANY, "login", wxPoint(10, 0), wxSize(200, 20));
    loginPassword = new wxTextCtrl(this, wxID_ANY, "login pass", wxPoint(10, 30), wxSize(200, 20));
    loginBtn = new wxButton(this, wxID_ANY, "Zaloguj się", wxPoint(10, 60));

    // Tworzenie formularza Zarejestruj
    signupName = new wxTextCtrl(this, wxID_ANY, "signup", wxPoint(10, 110), wxSize(200, 20));
    signupPassword1 = new wxTextCtrl(this, wxID_ANY, "signup password", wxPoint(10, 140), wxSize(200, 20));
    signupPassword2 = new wxTextCtrl(this, wxID_ANY, "confirm password", wxPoint(10, 170), wxSize(200, 20));
    signupBtn = new wxButton(this, wxID_ANY, "Zarejestruj się", wxPoint(10, 200));

    loginBtn->Bind(wxEVT_BUTTON, &FormsPanel::OnLogin, this);
    signupBtn->Bind(wxEVT_BUTTON, &FormsPanel::OnSignup, this);
}

// Funkcja obsługi zdarzenia po naciśnięciu przycisku "Zaloguj się"
void FormsPanel::OnLogin(wxCommandEvent& event)
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
    if (false)
    {
        wxMessageDialog* incorrectPasswordDlg = new wxMessageDialog(this, "Nieprawidłowe hasło.", "Błąd");
        incorrectPasswordDlg->ShowModal();
        return;
    }

    // Logowanie użytkownika
    // UserCRUD::Update_logged(userLoginName);
}


// Funkcja obsługi zdarzenia po naciśnięciu przycisku "Zarejestruj się"
void FormsPanel::OnSignup(wxCommandEvent& event)
{
    std::string userSignupName = signupName->GetValue().ToStdString();
    // Sprawdzanie czy taki użytkownik już istnieje
    //if (UserCRUD::DoesExist(userSignupName))
    if (false)
    {
        wxMessageDialog* userAlreadyExistsDlg = new wxMessageDialog(this, "Użytkownik o takim loginie już istnieje", "Błąd");
        userAlreadyExistsDlg->ShowModal();
        return;
    }

    if (!loginNameIsValid(userSignupName))
        return;

    std::string userSignupPassword = signupPassword1->GetValue().ToStdString();
    if (userSignupPassword != signupPassword2->GetValue().ToStdString())
    {
        wxMessageDialog* differentPasswordsDlg = new wxMessageDialog(this, "Hasła muszą być takie same", "Błąd");
        differentPasswordsDlg->ShowModal();
        return;
    }

}

// Funckja sprawdzająca login podany przez użytkownika przy rejestracji 
bool FormsPanel::loginNameIsValid(std::string loginName)
{
    constexpr int MIN_CHAR_NAME{3};
    constexpr int MAX_CHAR_NAME{15};
    
    std::string loginNameErrorMessage = "";
    int length = loginName.size();

    if (length < MIN_CHAR_NAME || length > MAX_CHAR_NAME)
        loginNameErrorMessage += "Login musi zawierać od " + std::to_string(MIN_CHAR_NAME) + " do " + std::to_string(MAX_CHAR_NAME) + " znaków.\n";

    // może składać się tylko z cyfr, podkreśleń, myślników oraz małych i dużych liter alfabetu angielskiego
    for (int i = 0; i < length; i++)
    {
        char c = loginName[i];
        if (!isalpha(c) && !isdigit(c) && c != '-' && c != '_')
        {
            loginNameErrorMessage += "Login może składać się tylko z cyfr, podkreśleń, myślników oraz małych i dużych liter alfabetu angielskiego.\n";
            break;
        }
    }

    if (loginNameErrorMessage == "")
        return true;

    wxMessageDialog* loginNameErrorDlg = new wxMessageDialog(this, loginNameErrorMessage, "Błąd");
    loginNameErrorDlg->ShowModal();
    return false;
}


bool FormsPanel::loginPasswordIsValid(std::string loginPassword)
{
    return true;
}