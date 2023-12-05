// FormsPanel.cpp
#include "FormsPanel.h"
#include <wx/wx.h>
#include <wx/textctrl.h>

FormsPanel::FormsPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    // Tworzenie etykiety
    loginName = new wxTextCtrl(this, wxID_ANY, "login", wxPoint(10, 20));
    loginPassword = new wxTextCtrl(this, wxID_ANY, "login pass", wxPoint(10, 60));

    signupName = new wxTextCtrl(this, wxID_ANY, "signup", wxPoint(10, 120));
    signupPassword = new wxTextCtrl(this, wxID_ANY, "signup pass", wxPoint(10, 160));
}