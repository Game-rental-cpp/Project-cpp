// FormsPanel.cpp
#include "FormsPanel.h"

FormsPanel::FormsPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    // Tworzenie etykiety
    label = new wxStaticText(this, wxID_ANY, "Label formsPanel", wxPoint(10, 50));

}
