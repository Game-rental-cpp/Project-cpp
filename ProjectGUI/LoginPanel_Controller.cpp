﻿// LoginPanel_Controller.cpp
#include "LoginPanel_Controller.h"
#include "LoginPanel.h"
#include "LoginPanel_Logic.h"
#include "Style.h"
#include "Log.h"
#include <wx/wx.h>

LoginPanel_Controller::LoginPanel_Controller(LoginPanel* parentEl, wxStaticText* successLabel,
    wxPanel* formsPanel,
    wxTextCtrl* loginName,
    wxTextCtrl* loginPassword,
    wxButton* loginBtn,
    wxTextCtrl* signupName,
    wxTextCtrl* signupPassword1,
    wxTextCtrl* signupPassword2,
    wxButton* signupBtn) :
    parentEl(parentEl),
    successLabel(successLabel),
    formsPanel(formsPanel),
    loginName(loginName),
    loginPassword(loginPassword),
    loginBtn(loginBtn),
    signupName(signupName),
    signupPassword1(signupPassword1),
    signupPassword2(signupPassword2),
    signupBtn(signupBtn) {}

void LoginPanel_Controller::BindEvents() {
    parentEl->Bind(wxEVT_SHOW, &LoginPanel_Controller::OnPanelShow, this);
    loginBtn->Bind(wxEVT_BUTTON, &LoginPanel_Controller::OnLogin, this);
    loginBtn->Bind(wxEVT_ENTER_WINDOW, &LoginPanel_Controller::OnMouseHover, this);
    signupBtn->Bind(wxEVT_BUTTON, &LoginPanel_Controller::OnSignup, this);
    signupBtn->Bind(wxEVT_ENTER_WINDOW, &LoginPanel_Controller::OnMouseHover, this);
}

// Function called when LoginPanel is shown on screen
void LoginPanel_Controller::OnPanelShow(wxShowEvent& event) {
    if (event.IsShown()) {
        loginName->Clear();
        loginPassword->Clear();
        signupName->Clear();
        signupPassword1->Clear();
        signupPassword2->Clear();

        successLabel->Hide();
        formsPanel->Show();

        Layout();
    }
    event.Skip();
}

void LoginPanel_Controller::OnMouseHover(wxMouseEvent& event) {
    OnCursorHover(event);
}

// Function called when "Zaloguj" button is pressed
void LoginPanel_Controller::OnLogin(wxCommandEvent& event) {
    std::string userLoginName = loginName->GetValue().ToStdString();
    std::string userLoginPassword = loginPassword->GetValue().ToStdString();

    if (!LoginPanel_Logic::LoginValidated(userLoginName, userLoginPassword, parentEl))
        return;

    formsPanel->Hide();
    successLabel->Show();
    
    // Update performance log
    writeToLog("Zalogowano uzytkownika: " + userLoginName);
}

// Function called when "Zarejestruj" button is pressed
void LoginPanel_Controller::OnSignup(wxCommandEvent& event) {
    std::string userSignupName = signupName->GetValue().ToStdString();
    std::string userSignupPassword1 = signupPassword1->GetValue().ToStdString();
    std::string userSignupPassword2 = signupPassword2->GetValue().ToStdString();

    if (!LoginPanel_Logic::SignupValidated(userSignupName, userSignupPassword1, userSignupPassword2, parentEl))
        return;

    formsPanel->Hide();
    successLabel->Show();

    // Update performance log
    writeToLog("Utworzono nowe konto: " + userSignupName);
    writeToLog("Zalogowano uzytkownika: " + userSignupName);
}
