// FormsPanel.cpp
#include "FormsPanel.h"
#include <wx/wx.h>
#include <wx/textctrl.h>

FormsPanel::FormsPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    // Tworzenie formularza Zaloguj
    loginName = new wxTextCtrl(this, wxID_ANY, "login", wxPoint(10, 20), wxSize(200, 20));
    loginPassword = new wxTextCtrl(this, wxID_ANY, "login pass", wxPoint(10, 50), wxSize(200, 20));
    loginBtn = new wxButton(this, wxID_ANY, "Zaloguj się", wxPoint(10, 80));

    // Tworzenie formularza Zarejestruj
    signupName = new wxTextCtrl(this, wxID_ANY, "signup", wxPoint(10, 130), wxSize(200, 20));
    signupPassword = new wxTextCtrl(this, wxID_ANY, "signup pass", wxPoint(10, 160), wxSize(200, 20));
    signupBtn = new wxButton(this, wxID_ANY, "Zarejestruj się", wxPoint(10, 190));

    loginBtn->Bind(wxEVT_BUTTON, &FormsPanel::OnLogin, this);
    signupBtn->Bind(wxEVT_BUTTON, &FormsPanel::OnSignup, this);
}

// Funkcja obsługi zdarzenia po naciśnięciu przycisku "Zaloguj się"
void FormsPanel::OnLogin(wxCommandEvent& event)
{
    

    this->Layout();
}

void FormsPanel::OnSignup(wxCommandEvent& event)
{


    this->Layout();
}