#pragma once
#include <wx/wx.h>
#include "MainPanel.h"
#include "LoginPanel.h"
#include "MyAccPanel.h"

class MainFrame_Controller {
public:
    MainFrame_Controller(wxButton* goBackBtn, wxButton* loginBtn, wxButton* myAccBtn, MainPanel* mainPanel, LoginPanel* loginPanel, MyAccPanel* myAccPanel);
    void BindEvents();

private:
    // Dodaj funkcje obs³ugi zdarzeñ tutaj, na przyk³ad:
    void OnGoBack(wxCommandEvent& event);
    void OnLogin(wxCommandEvent& event);
    void OnMyAcc(wxCommandEvent& event);
    void OnMouseHover(wxMouseEvent& event);

    wxButton* goBackBtn;
    wxButton* loginBtn;
    wxButton* myAccBtn;
    MainPanel* mainPanel;
    LoginPanel* loginPanel;
    MyAccPanel* myAccPanel;
};
