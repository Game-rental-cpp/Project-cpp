#pragma once

#include <wx/wx.h>
#include "FormsPanel.h"

class LoginPanel : public wxPanel
{
public:
    LoginPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);

private:
    wxStaticText* label;
    FormsPanel* formsPanel;
};