#pragma once
// FormsPanel.h
#include <wx/wx.h>

class FormsPanel : public wxPanel
{
public:
    FormsPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);

private:
    wxStaticText* label;
};
