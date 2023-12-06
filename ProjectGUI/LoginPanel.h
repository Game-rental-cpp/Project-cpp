#pragma once
// LoginPanel.h
#include <wx/wx.h>
#include "FormsPanel.h"

class LoginPanel : public wxPanel
{
public:
    LoginPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
    void OnButtonClick(wxCommandEvent& event);

private:
    wxStaticText* label;
    FormsPanel* formsPanel;
};