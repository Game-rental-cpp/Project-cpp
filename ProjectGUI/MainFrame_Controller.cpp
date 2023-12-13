#include "MainFrame_Controller.h"
#include "UserCRUD.h"
#include "Style.h"

MainFrame_Controller::MainFrame_Controller(wxButton* goBackBtn, wxButton* loginBtn, wxButton* myAccBtn, MainPanel* mainPanel, LoginPanel* loginPanel, MyAccPanel* myAccPanel)
    : goBackBtn(goBackBtn), loginBtn(loginBtn), myAccBtn(myAccBtn), mainPanel(mainPanel), loginPanel(loginPanel), myAccPanel(myAccPanel) {
    //loginBtn->Bind(wxEVT_ENTER_WINDOW, &MainFrame_Controller::OnMouseHover, this);
    //goBackBtn->Bind(wxEVT_ENTER_WINDOW, &MainFrame_Controller::OnMouseHover, this);
    //myAccBtn->Bind(wxEVT_ENTER_WINDOW, &MainFrame_Controller::OnMouseHover, this);
}

void MainFrame_Controller::BindEvents() {
    goBackBtn->Bind(wxEVT_BUTTON, &MainFrame_Controller::OnGoBack, this);
    loginBtn->Bind(wxEVT_BUTTON, &MainFrame_Controller::OnLogin, this);
    myAccBtn->Bind(wxEVT_BUTTON, &MainFrame_Controller::OnMyAcc, this);
    loginBtn->Bind(wxEVT_ENTER_WINDOW, &MainFrame_Controller::OnMouseHover, this);
    goBackBtn->Bind(wxEVT_ENTER_WINDOW, &MainFrame_Controller::OnMouseHover, this);
    myAccBtn->Bind(wxEVT_ENTER_WINDOW, &MainFrame_Controller::OnMouseHover, this);
}

void MainFrame_Controller::OnGoBack(wxCommandEvent& event) {
    goBackBtn->Hide();

    if (UserCRUD::isLogged()) {
        loginBtn->Hide();
        myAccBtn->Show();
    }
    else {
        loginBtn->Show();
        myAccBtn->Hide();
    }

    mainPanel->Show();
    loginPanel->Hide();
    myAccPanel->Hide();
}

void MainFrame_Controller::OnLogin(wxCommandEvent& event) {
    goBackBtn->Show();
    loginBtn->Hide();
    myAccBtn->Hide();

    loginPanel->Show();
    myAccPanel->Hide();
    mainPanel->Hide();

    // Jeœli to konieczne, mo¿esz dodaæ kod do odœwie¿enia widoku
}

void MainFrame_Controller::OnMyAcc(wxCommandEvent& event) {
    goBackBtn->Show();
    loginBtn->Hide();
    myAccBtn->Hide();

    myAccPanel->Show();
    loginPanel->Hide();
    mainPanel->Hide();
}

void MainFrame_Controller::OnMouseHover(wxMouseEvent& event) {
    OnCursorHover(event);
}

