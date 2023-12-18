// style.cpp

#include "style.h"
#include <wx/font.h>
#include <wx/wx.h>

// Helps to set font size
// @param int fontSize (optional)
// @param bool bold (optional)
// @returns wxFont
wxFont SetTheFont(int fontSize, bool bold) {
    wxFontInfo fontInfo(fontSize);

    // Ustawienie rodziny czcionki
    fontInfo.Family(wxFONTFAMILY_DEFAULT);

    // Jeœli bold == true, ustaw pogrubienie
    if (bold) {
        fontInfo.Bold();
    }

    return wxFont(fontInfo);
}


// set cursor
void OnCursorHover(wxMouseEvent& event) {
    wxWindow* element = dynamic_cast<wxWindow*>(event.GetEventObject());

    wxCursor cursor(wxCURSOR_HAND);
    element->SetCursor(cursor);
    event.Skip();
}

