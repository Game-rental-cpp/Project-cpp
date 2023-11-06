#pragma once

#include <wx/wx.h>
#include "MainPanel.h"
#include "LoginPanel.h"
#include "MyAccPanel.h"
#include "MainFrame_Logic.h"
#include "MainFrame_Controller.h"
#include "UserCRUD.h"

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnGoBack(wxCommandEvent& event);
    void OnLogin(wxCommandEvent& event);
    void OnMyAcc(wxCommandEvent& event);

private:
    wxButton* goBackBtn;
    wxButton* loginBtn;
    wxButton* myAccBtn;
    MainPanel* mainPanel;
    LoginPanel* loginPanel;
    MyAccPanel* myAccPanel;

};

