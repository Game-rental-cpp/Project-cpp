// style.cpp

#include "style.h"
#include <wx/font.h>
#include <wx/wx.h>

// Helps to set font size
// @param int fontSize (optional)
// @returns wxFont
wxFont SetTheFont(int fontSize) {
    return wxFont(wxFontInfo(fontSize).Family(wxFONTFAMILY_DEFAULT));
}

// set cursor
void OnCursorHover(wxMouseEvent& event) {
    wxWindow* element = dynamic_cast<wxWindow*>(event.GetEventObject());

    wxCursor cursor(wxCURSOR_HAND);
    element->SetCursor(cursor);
    event.Skip();
}

