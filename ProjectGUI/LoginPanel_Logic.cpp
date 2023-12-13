#include "LoginPanel.h"
#include "LoginPanel_Logic.h"
#include <wx/wx.h>
#include "UserCRUD.h"


bool LoginPanel_Logic::loginValidated(std::string loginName, std::string loginPassword, LoginPanel* loginPanel) {
    // Sprawdzanie czy istnieje użytkownik o podanym loginie
    if (!UserCRUD::DoesExist(loginName))
    {
        wxMessageDialog* noKnownUserDlg = new wxMessageDialog(loginPanel, "Brak użytkownika o takim loginie.", "Błąd");
        noKnownUserDlg->ShowModal();
        return false;
    }

    // Sprawdzanie hasła
    //if (UserCRUD::ReadPassword(loginName) != loginPassword)
    if (false)
    {
        wxMessageDialog* incorrectPasswordDlg = new wxMessageDialog(loginPanel, "Nieprawidłowe hasło.", "Błąd");
        incorrectPasswordDlg->ShowModal();
        return false;
    }

    // Logowanie użytkownika 
    UserCRUD::Update_logged(loginName);
    return true;
}

bool  LoginPanel_Logic::signupNameValidated(std::string signupName, LoginPanel* loginPanel) {
    return true;
}
bool  LoginPanel_Logic::signupPasswordValidated(std::string signupPassword1, std::string signupPassword2, LoginPanel* loginPanel) {
    return true;
}