﻿#include "LoginPanel.h"
#include "LoginPanel_Logic.h"
#include <wx/wx.h>
#include "UserCRUD.h"


// Log in attempt validation
bool LoginPanel_Logic::LoginValidated(std::string loginName, std::string loginPassword, LoginPanel* loginPanel) {
    // Handle user not existing
    if (!UserCRUD::DoesExist(loginName))
    {
        wxMessageDialog* noKnownUserDlg = new wxMessageDialog(loginPanel, "Brak użytkownika o takim loginie.", "Błąd");
        noKnownUserDlg->ShowModal();
        return false;
    }

    // Handle incorrect password
    // if (UserCRUD::ReadPassword(loginName) != loginPassword)
    if (false)
    {
        wxMessageDialog* incorrectPasswordDlg = new wxMessageDialog(loginPanel, "Nieprawidłowe hasło.", "Błąd");
        incorrectPasswordDlg->ShowModal();
        return false;
    }

    // Log in user if there aren't any issues
    UserCRUD::Update_logged(loginName);
    return true;
}

// Sign up attempt validation
bool  LoginPanel_Logic::SignupValidated(std::string signupName, std::string signupPassword1, std::string signupPassword2, LoginPanel* loginPanel) {

    // Login username min and max length
    constexpr int MIN_CHAR_NAME{ 3 };
    constexpr int MAX_CHAR_NAME{ 15 };
    
    // Login password min and max length
    constexpr int MIN_CHAR_PASSWORD{ 8 };
    constexpr int MAX_CHAR_PASSWORD{ 40 };

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
    if (nameLength < MIN_CHAR_PASSWORD || nameLength > MAX_CHAR_PASSWORD)
        signupNameErrorMessage += "Login musi zawierać od " + std::to_string(MIN_CHAR_PASSWORD) + " do " + std::to_string(MAX_CHAR_PASSWORD) + " znaków.\n";

    // Check if username meets character content requirements
    for (int i = 0; i < nameLength; i++)
    {
        char c = signupName[i];
        if (!isalpha(c) && !isdigit(c) && c != '-' && c != '_')
        {
            signupNameErrorMessage += "Login może składać się tylko z cyfr, podkreśleń, myślników oraz małych i dużych liter alfabetu angielskiego.\n";
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

    return true;
}

