#include "MainFrame_Controller.h"

void goBackHandle(wxButton* goBackBtn, wxButton* loginBtn, wxButton* myAccBtn, MainPanel* mainPanel, LoginPanel* loginPanel, MyAccPanel* myAccPanel) {
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
