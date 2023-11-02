#pragma once
// MainFrame.h
//#ifndef MAINFRAME_H
//#define MAINFRAME_H

#include <wx/wx.h>
#include "MainPanel.h"
#include "LoginPanel.h"
#include "MyAccPanel.h"

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
    // Inne deklaracje
};

//#endif // MAINFRAME_H
