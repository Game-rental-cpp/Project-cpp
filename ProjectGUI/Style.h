
// Style.h

#ifndef STYLDEF_H
#define STYLDEF_H

#include <wx/wx.h>


//panels
#define COLOR_BACKGROUND_PANEL wxColour(23, 27, 33)
#define COLOR_BACKGROUND_FRAME wxColour(14, 17, 22)

// buttons
#define COLOR_BACKGROUND_BTN wxColour(100, 100, 100)
#define COLOR_TEXT_BTN wxColour(255, 255, 255)

#define COLOR_BACKGROUND_LOGINBTN wxColour(50, 150, 50)
#define COLOR_TEXT_LOGINBTN wxColour(0,0,0)


//labels
#define COLOR_LBL wxColour(255, 255, 255)
#define FONT_SIZE_LBL 12


#define RED wxColour(220, 50, 50)

// Deklaracja funkcji GetLabelFont
wxFont SetTheFont(int fontSize = FONT_SIZE_LBL);
void ChangeCursor(wxMouseEvent& event);


#endif // STYLDEF_H
