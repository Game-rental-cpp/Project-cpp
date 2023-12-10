#pragma once

#include <wx/wx.h>

class LoginPanel : public wxPanel
{
public:
    LoginPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
    
    void OnLogin(wxCommandEvent& event);
    /*void OnSignup(wxCommandEvent& event);
    bool signupNameIsValid(std::string signupName);
    bool signupPasswordIsValid(std::string signupPassword);
    */
    

private:
    wxStaticText* successLabel;
    wxPanel* formsPanel;

    wxTextCtrl* loginName;
    wxTextCtrl* loginPassword;
    wxButton* loginBtn;

    wxTextCtrl* signupName;
    wxTextCtrl* signupPassword1;
    wxTextCtrl* signupPassword2;
    wxButton* signupBtn;
};