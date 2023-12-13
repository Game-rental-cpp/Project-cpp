// MainFrame_Logic.h
#pragma once
#include <wx/wx.h>
#include "MainPanel.h"
#include "MyAccPanel.h"
#include "LoginPanel.h"

class MainFrame_Logic {
public:
    static void HideButton(wxButton* loginBtn, wxButton* myAccBtn);
    static void CreateUser(User* user, MainPanel* mainPanel, MyAccPanel* myAccPanel, LoginPanel* loginPanel);
};

