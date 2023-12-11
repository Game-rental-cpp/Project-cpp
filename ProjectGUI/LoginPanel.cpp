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
    signupPassword1 = new wxTextCtrl(formsPanel, wxID_ANY, "signup password", wxPoint(10, 140), wxSize(200, 20), wxTE_PASSWORD);
    signupPassword2 = new wxTextCtrl(formsPanel, wxID_ANY, "confirm password", wxPoint(10, 170), wxSize(200, 20));
    signupBtn = new wxButton(formsPanel, wxID_ANY, "Zarejestruj się", wxPoint(10, 200));

    loginBtn->Bind(wxEVT_BUTTON, &LoginPanel::OnLogin, this);
    signupBtn->Bind(wxEVT_BUTTON, &LoginPanel::OnSignup, this);
}

// Funkcja obsługi zdarzenia po naciśnięciu przycisku "Zaloguj się"
// NA RAZIE NIC NIE ROBI BO NIE MA FUNKCJI Z "UserCRUD.h" !!!
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
    if (false)
    {
        wxMessageDialog* incorrectPasswordDlg = new wxMessageDialog(this, "Nieprawidłowe hasło.", "Błąd");
        incorrectPasswordDlg->ShowModal();
        return;
    }

    // Logowanie użytkownika
    // UserCRUD::Update_logged(userLoginName);
    // formsPanel->Hide();
    // successLabel->Show();
}

// Funkcja obsługi zdarzenia po naciśnięciu przycisku "Zarejestruj się"
void LoginPanel::OnSignup(wxCommandEvent& event)
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
    // UserCRUD::CreateUser(userSignupName, userSignupPassword)

    // Logowanie użytkownika
    // UserCRUD::Update_logged(userSignupName);
    formsPanel->Hide();
    successLabel->Show();
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