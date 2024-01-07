// LoginPanel_Controller.h
#pragma once
#include <wx/wx.h>

class LoginPanel;

class LoginPanel_Controller : public wxPanel
{
public:
    LoginPanel_Controller(LoginPanel* parentEl, wxStaticText* successLabel,
    wxPanel* formsPanel,
    wxTextCtrl* loginName,
    wxTextCtrl* loginPassword,
    wxButton* loginBtn,
    wxTextCtrl* signupName,
    wxTextCtrl* signupPassword1,
    wxTextCtrl* signupPassword2,
    wxButton* signupBtn);

    void BindEvents();

private:
    LoginPanel* parentEl;
    wxStaticText* successLabel;
    wxPanel* formsPanel;

    wxTextCtrl* loginName;
    wxTextCtrl* loginPassword;
    wxButton* loginBtn;

    wxTextCtrl* signupName;
    wxTextCtrl* signupPassword1;
    wxTextCtrl* signupPassword2;
    wxButton* signupBtn;

    void OnPanelShow(wxShowEvent& event);
    void OnLogin(wxCommandEvent& event);
    void OnSignup(wxCommandEvent& event);
    void OnMouseHover(wxMouseEvent& event);
};

