#pragma once

#include <wx/wx.h>
#include "MainPanel.h"
#include "LoginPanel.h"
#include "MyAccPanel.h"
#include "Logic.h"

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnGoBack(wxCommandEvent& event);
    void OnLogin(wxCommandEvent& event);
    void OnMyAcc(wxCommandEvent& event);
    bool IsLogged() const;

private:
    wxButton* goBackBtn;
    wxButton* loginBtn;
    wxButton* myAccBtn;
    MainPanel* mainPanel;
    LoginPanel* loginPanel;
    MyAccPanel* myAccPanel;

};

