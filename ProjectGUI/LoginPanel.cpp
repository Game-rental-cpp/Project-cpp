// LoginPanel.cpp
#include "LoginPanel.h"
#include "FormsPanel.h"
#include "UserCRUD.h"


LoginPanel::LoginPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    // Tworzenie etykiety
    label = new wxStaticText(this, wxID_ANY, "Zalogowano", wxPoint(10, 50)); 

    // Tworzenie panelu z formularzami
    formsPanel = new FormsPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(410, 300));
    formsPanel->SetBackgroundColour(wxColour(0, 255, 0)); // Ustawiony na zielony kolor (0, 255, 0)
    //formsPanel->Hide()

}

void LoginPanel::OnShowPanel(wxShowEvent& event)
{
    if (!UserCRUD::isLogged()) {
        label->Hide();
        formsPanel->Show();
    }
    
    Layout();
}
