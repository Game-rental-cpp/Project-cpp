#pragma once

#include <wx/wx.h>

class LoginPanel : public wxPanel
{
public:
    LoginPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
    void OnButtonClick(wxCommandEvent& event);

private:
    wxButton* button;
    wxStaticText* label;
};