// MainFrame_Logic.h
#pragma once
#include <wx/wx.h>
#include "MainPanel.h"
#include "MyAccPanel.h"
#include "LoginPanel.h"
#include "User.h"

class MainFrame_Logic {
public:
    
    // This function hides loginBtn or myAccBtn depending on whether the user is logged in
    static void HideButton(wxButton* loginBtn, wxButton* myAccBtn);

    // Creates user object if someone is logged in right after opening the app
    static User* CreateUser();
};

