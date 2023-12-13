#pragma once
#include <wx/wx.h>
#include "MainPanel.h"
#include "LoginPanel.h"
#include "MyAccPanel.h"

class MainFrame;

class MainFrame_Controller {
public:
    MainFrame_Controller(MainFrame* parentEl, wxButton* goBackBtn, wxButton* loginBtn, wxButton* myAccBtn, MainPanel* mainPanel, LoginPanel* loginPanel, MyAccPanel* myAccPanel);
    void BindEvents();

private:
    void OnGoBack(wxCommandEvent& event);
    void OnLogin(wxCommandEvent& event);
    void OnMyAcc(wxCommandEvent& event);
    void OnMouseHover(wxMouseEvent& event);

    MainFrame* parentEl;
    wxButton* goBackBtn;
    wxButton* loginBtn;
    wxButton* myAccBtn;
    MainPanel* mainPanel;
    LoginPanel* loginPanel;
    MyAccPanel* myAccPanel;
};
