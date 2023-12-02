#pragma once
// LoginPanel.h
#include <wx/wx.h>
#include "FormsPanel.h"

class LoginPanel : public wxPanel
{
public:
    LoginPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
    void OnShowPanel(wxShowEvent& event);

private:
    FormsPanel* formsPanel;
    wxStaticText* label;
};
