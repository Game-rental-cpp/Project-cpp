#pragma once

#include <wx/wx.h>

class MyAccPanel : public wxPanel
{
public:
    MyAccPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);

private:
    wxButton* button;
    wxStaticText* label;
};