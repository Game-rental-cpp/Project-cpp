#include "LoginPanel.h"
#include "LoginPanel_Logic.h"
//#include "LoginPanel_Length_Reqs.h"
#include <wx/wx.h>
#include "Style.h"
#include "UserCRUD.h"
#include "MainPanel_Logic.h"
#include "MyAccPanel_Logic.h"
#include "User.h"
#include "UserNormal.h"
#include "UserPremium.h"
#include "json.hpp"

using json = nlohmann::json;

// Log in attempt validation
bool LoginPanel_Logic::LoginValidated(std::string loginName, std::string loginPassword, LoginPanel* loginPanel) {
    // Handle user not existing
    if (!UserCRUD::DoesExist(loginName))
    {
        wxMessageDialog* noKnownUserDlg = new wxMessageDialog(loginPanel, "Brak użytkownika o takim loginie.", "Błąd");
        noKnownUserDlg->ShowModal();
        return false;
    }

    std::string userStr = UserCRUD::ReadUser(loginName); //string representation of user model
    json jsonData = json::parse(userStr); //parsing JSON string
    std::string password = jsonData.at("password"); //get value of key "password"

    // Handle incorrect password
     if (password != loginPassword){
        wxMessageDialog* incorrectPasswordDlg = new wxMessageDialog(loginPanel, "Nieprawidłowe hasło.", "Błąd");
        incorrectPasswordDlg->ShowModal();
        return false;
    }

    // Log in user if there aren't any issues
    UserCRUD::Update_logged(loginName);
    User* user = nullptr;
    if (jsonData.at("isPremium"))
        user = new UserPremium(loginName);
    else
        user = new UserNormal(loginName);
    MainPanel_Logic::SetUser(user);
    MyAccPanel_Logic::SetUser(user);

    return true;
}

// Sign up attempt validation
bool  LoginPanel_Logic::SignupValidated(std::string signupName, std::string signupPassword1, std::string signupPassword2, LoginPanel* loginPanel) {

    ////////////////////////////////////////////////////////////////////////////////
    // Username validation //
    ////////////////////////////////////////////////////////////////////////////////
    
    // Handle user already existing
    if (UserCRUD::DoesExist(signupName))
    {
        wxMessageDialog* userAlreadyExistsDlg = new wxMessageDialog(loginPanel, "Użytkownik o takim loginie już istnieje", "Błąd");
        userAlreadyExistsDlg->ShowModal();
        return false;
    }

    // Check if the username meets the requirements //

    // Variable for storing an error message 
    std::string signupNameErrorMessage = "";

    int nameLength = signupName.size();

    // Check if username meets length requirements
    if (nameLength < MIN_CHAR_NAME || nameLength > MAX_CHAR_NAME)
        signupNameErrorMessage += "Login musi zawierać od " + std::to_string(MIN_CHAR_NAME) + " do " + std::to_string(MAX_CHAR_NAME) + " znaków.\n";

    // Check if username meets character content requirements
    for (int i = 0; i < nameLength; i++)
    {
        char c = signupName[i];
        if (!isalpha(c) && !isdigit(c) && c != '-' && c != '_')
        {
            signupNameErrorMessage += "Login może składać się tylko z cyfr, podkreśleń, myślników lub małych i dużych liter alfabetu angielskiego.\n";
            break;
        }
    }

    // Handle errors
    if (!signupNameErrorMessage.empty()) {
        wxMessageDialog* signupNameErrorDlg = new wxMessageDialog(loginPanel, signupNameErrorMessage, "Błąd");
        signupNameErrorDlg->ShowModal();
        return false;
    }
    
    //////////////////////////////////////////////////////////////////
    // Password validation //
    //////////////////////////////////////////////////////////////////

    // Handle passwords given by the user being different
    if (signupPassword1 != signupPassword2)
    {
        wxMessageDialog* differentPasswordsDlg = new wxMessageDialog(loginPanel, "Hasła muszą być takie same", "Błąd");
        differentPasswordsDlg->ShowModal();
        return false;
    }

    // Variable for storing invalid password error message
    std::string signupPasswordErrorMessage = "";

    // Check if password meets length requirements
    int passwordLength = signupPassword1.size();
    if (passwordLength < MIN_CHAR_PASSWORD || passwordLength > MAX_CHAR_PASSWORD)
        signupPasswordErrorMessage += "Hasło musi zawierać od " + std::to_string(MIN_CHAR_PASSWORD) + " do " + std::to_string(MAX_CHAR_PASSWORD) + " znaków.\n";

    // Check if password meets character content requirements
    bool hasLower{ false }; bool hasUpper{ false }; bool hasDigit{ false }; bool hasSpecial{ false };
    for (int i = 0; i < passwordLength; i++)
    {
        if (hasLower && hasUpper && hasDigit && hasSpecial)
            break;
        char c = signupPassword1[i];
        if (islower(c))
            hasLower = true;
        else if (isupper(c))
            hasUpper = true;
        else if (isdigit(c))
            hasDigit = true;
        else
            hasSpecial = true;
    }

    // Add respective error messages
    if (!hasLower)
        signupPasswordErrorMessage += "Hasło musi zawierać małe litery.\n";
    if (!hasUpper)
        signupPasswordErrorMessage += "Hasło musi zawierać duże litery.\n";
    if (!hasDigit)
        signupPasswordErrorMessage += "Hasło musi zawierać cyfry.\n";
    if (!hasSpecial)
        signupPasswordErrorMessage += "Hasło musi zawierać znaki specjalne.\n";

    // Handle errors
    if (!signupPasswordErrorMessage.empty()) {
        wxMessageDialog* signupPasswordErrorDlg = new wxMessageDialog(loginPanel, signupPasswordErrorMessage, "Błąd");
        signupPasswordErrorDlg->ShowModal();
        return false;
    }
        
    // If sign up is successfull 
    // Create and log in new user
    UserCRUD::CreateUser(signupName, signupPassword1);
    UserCRUD::Update_logged(signupName);

    User* user = new UserNormal(signupName);
    MainPanel_Logic::SetUser(user);
    MyAccPanel_Logic::SetUser(user);

    return true;
}

