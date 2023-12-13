// LoginPanel.cpp
#include "LoginPanel.h"
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


// Funkcja obsługi zdarzenia wyświetlenia LoginPanel
void LoginPanel::OnPanelShow(wxShowEvent& event)
{
    if (event.IsShown()) {
        successLabel->Hide();
        formsPanel->Show();

    }

    event.Skip();
}

// Funkcja obsługi zdarzenia po naciśnięciu przycisku "Zaloguj się"
void LoginPanel::OnLogin(wxCommandEvent& event)
{
    std::string userLoginName = loginName->GetValue().ToStdString();

    // Sprawdzanie czy istnieje użytkownik o podanym loginie
    if (!UserCRUD::DoesExist(userLoginName))
    {
        wxMessageDialog* noKnownUserDlg = new wxMessageDialog(this, "Brak użytkownika o takim loginie.", "Błąd");
        noKnownUserDlg->ShowModal();
        return;
    }

    // Sprawdzanie hasła
    //if (UserCRUD::ReadPassword(userLoginName) != loginPassword->GetValue().ToStdString())
    if (false)
    {
        wxMessageDialog* incorrectPasswordDlg = new wxMessageDialog(this, "Nieprawidłowe hasło.", "Błąd");
        incorrectPasswordDlg->ShowModal();
        return;
    }

    // Logowanie użytkownika
    UserCRUD::Update_logged(userLoginName);
    formsPanel->Hide();
    successLabel->Show();

    event.Skip();
}

// Funkcja obsługi zdarzenia po naciśnięciu przycisku "Zarejestruj się"
void LoginPanel::OnSignup(wxCommandEvent& event)
{
    std::string userSignupName = signupName->GetValue().ToStdString();
    // Sprawdzanie czy taki użytkownik już istnieje
    if (UserCRUD::DoesExist(userSignupName))
    {
        wxMessageDialog* userAlreadyExistsDlg = new wxMessageDialog(this, "Użytkownik o takim loginie już istnieje", "Błąd");
        userAlreadyExistsDlg->ShowModal();
        return;
    }

    // Walidacja loginu
    if (!signupNameIsValid(userSignupName))
        return;

    std::string userSignupPassword = signupPassword1->GetValue().ToStdString();

    // Sprawdzanie czy hasła podane przez użytkownika są jednakowe 
    if (userSignupPassword != signupPassword2->GetValue().ToStdString())
    {
        wxMessageDialog* differentPasswordsDlg = new wxMessageDialog(this, "Hasła muszą być takie same", "Błąd");
        differentPasswordsDlg->ShowModal();
        return;
    }

    // Walidacja hasła
    if (!signupPasswordIsValid(userSignupPassword))
        return;

    // Jeśli rejestracja przebiegła pomyślnie
    // Tworzenie nowego konta
    UserCRUD::CreateUser(userSignupName, userSignupPassword);

    // Logowanie użytkownika
    UserCRUD::Update_logged(userSignupName);
    formsPanel->Hide();
    successLabel->Show();

    event.Skip();
}

// Funckja sprawdzająca login podany przez użytkownika przy rejestracji 
bool LoginPanel::signupNameIsValid(std::string signupName)
{
    constexpr int MIN_CHAR_NAME{ 3 };
    constexpr int MAX_CHAR_NAME{ 15 };

    std::string signupNameErrorMessage = "";
    int length = signupName.size();

    // Sprawdzanie długości logina
    if (length < MIN_CHAR_NAME || length > MAX_CHAR_NAME)
        signupNameErrorMessage += "Login musi zawierać od " + std::to_string(MIN_CHAR_NAME) + " do " + std::to_string(MAX_CHAR_NAME) + " znaków.\n";

    // Sprawdzanie zawartości logina
    for (int i = 0; i < length; i++)
    {
        char c = signupName[i];
        if (!isalpha(c) && !isdigit(c) && c != '-' && c != '_')
        {
            signupNameErrorMessage += "Login może składać się tylko z cyfr, podkreśleń, myślników oraz małych i dużych liter alfabetu angielskiego.\n";
            break;
        }
    }

    if (signupNameErrorMessage == "")
        return true;

    // Wyświetlanie odpowiedniego komunikatu jeśli login jest niewłaściry
    wxMessageDialog* signupNameErrorDlg = new wxMessageDialog(this, signupNameErrorMessage, "Błąd");
    signupNameErrorDlg->ShowModal();
    return false;
}


// Funckja sprawdzająca hasło podane przez użytkownika przy rejestracji
bool LoginPanel::signupPasswordIsValid(std::string signupPassword)
{
    constexpr int MIN_CHAR_PSSWRD{ 8 };
    constexpr int MAX_CHAR_PSSWRD{ 30 };

    std::string signupPasswordErrorMessage = "";
    int length = signupPassword.size();

    // Sprawdzanie długości hasła
    if (length < MIN_CHAR_PSSWRD || length > MAX_CHAR_PSSWRD)
        signupPasswordErrorMessage += "Hasło musi zawierać od " + std::to_string(MIN_CHAR_PSSWRD) + " do " + std::to_string(MAX_CHAR_PSSWRD) + " znaków.\n";

    // Sprawdzanie zawartości hasła
    bool hasLower{ false }; bool hasUpper{ false }; bool hasDigit{ false }; bool hasSpecial{ false };
    for (int i = 0; i < length; i++)
    {
        if (hasLower && hasUpper && hasDigit && hasSpecial)
            break;
        char c = signupPassword[i];
        if (islower(c))
            hasLower = true;
        else if (isupper(c))
            hasUpper = true;
        else if (isdigit(c))
            hasDigit = true;
        else
            hasSpecial = true;
    }

    // Dodawanie odpowiednich komunikatów
    if (!hasLower)
        signupPasswordErrorMessage += "Hasło musi zawierać małe litery.\n";
    if (!hasUpper)
        signupPasswordErrorMessage += "Hasło musi zawierać duże litery.\n";
    if (!hasDigit)
        signupPasswordErrorMessage += "Hasło musi zawierać cyfry.\n";
    if (!hasSpecial)
        signupPasswordErrorMessage += "Hasło musi zawierać znaki specjalne.\n";

    if (signupPasswordErrorMessage == "")
        return true;

    // Wyświetlanie odpowiedniego komunikatu jeśli hasło jest niewłaściwe
    wxMessageDialog* signupPasswordErrorDlg = new wxMessageDialog(this, signupPasswordErrorMessage, "Błąd");
    signupPasswordErrorDlg->ShowModal();
    return false;
}