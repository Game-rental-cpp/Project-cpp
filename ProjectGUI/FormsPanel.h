#pragma once
// FormsPanel.h
#include <wx/wx.h>


class FormsPanel : public wxPanel
{
public:
    FormsPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
    void OnLogin(wxCommandEvent& event);
    void OnSignup(wxCommandEvent& event);

private:
    wxTextCtrl* loginName;
    wxTextCtrl* loginPassword;
    wxButton* loginBtn;

    wxTextCtrl* signupName;
    wxTextCtrl* signupPassword;
    wxButton* signupBtn;
};