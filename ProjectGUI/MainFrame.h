// MainFrame.h
#pragma once

#include <wx/wx.h>
#include "MainPanel.h"
#include "LoginPanel.h"
#include "MyAccPanel.h"
#include "MainFrame_Logic.h"
#include "MainFrame_Controller.h"
//#include "UserCRUD.h"

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    // ... inne deklaracje funkcji i sk�adnik�w klasy

private:
    User* user;
    wxButton* goBackBtn;
    wxButton* loginBtn;
    wxButton* myAccBtn;
    MainPanel* mainPanel;
    LoginPanel* loginPanel;
    MyAccPanel* myAccPanel;
    // ... inne prywatne sk�adniki klasy

    // ... inne deklaracje funkcji prywatnych klasy
    //void OnMouseHover(wxMouseEvent& event);
};

