// LoginPanel.cpp
#include "LoginPanel.h"
#include <filesystem>
#include "FormsPanel.h"

LoginPanel::LoginPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{

    // Tworzenie etykiety
    label = new wxStaticText(this, wxID_ANY, "Zalogowano", wxPoint(10, 50)); 
    // Tworzenia panela z formularzami
    //formsPanel = new FormsPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(410, 500));
    //formsPanel->setCo
}
