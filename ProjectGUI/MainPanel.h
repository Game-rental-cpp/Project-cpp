#pragma once
// MainPanel.h
//#ifndef MAINPANEL_H
//#define MAINPANEL_H

#include <wx/wx.h>

class MainPanel : public wxPanel
{
public:
    MainPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);

private:
    wxButton* button;
    wxStaticText* label;
};

//#endif // MAINPANEL_H
