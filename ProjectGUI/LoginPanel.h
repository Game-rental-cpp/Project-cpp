#pragma once

#include <wx/wx.h>
#include "FormsPanel.h"

class LoginPanel : public wxPanel
{
public:
    LoginPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
    //void OnShowPanel(wxShowEvent& event);

private:
    wxStaticText* label;
    //FormsPanel* formsPanel;
};