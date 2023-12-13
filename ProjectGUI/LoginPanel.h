#pragma once
// LoginPanel.h
#include <wx/wx.h>

class LoginPanel : public wxPanel
{
public:
    LoginPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
    void OnPanelShow(wxShowEvent& event);
    
    void OnLogin(wxCommandEvent& event);
    void OnSignup(wxCommandEvent& event);
    bool signupNameIsValid(std::string signupName);
    bool signupPasswordIsValid(std::string signupPassword);

private:
    wxStaticText* successLabel;
    wxPanel* formsPanel;

    wxStaticText* loginPrompt;
    wxTextCtrl* loginName;
    wxTextCtrl* loginPassword;
    wxButton* loginBtn;

    wxStaticText* signupPrompt;
    wxTextCtrl* signupName;
    wxTextCtrl* signupPassword1;
    wxTextCtrl* signupPassword2;
    wxButton* signupBtn;
};