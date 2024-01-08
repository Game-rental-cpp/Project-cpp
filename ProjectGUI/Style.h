
// Style.h

#ifndef STYLDEF_H
#define STYLDEF_H

#include <wx/wx.h>


//panels
//#define COLOR_BACKGROUND_PANEL wxColour(250, 250, 250)
#define COLOR_BACKGROUND_PANEL wxColour(250, 240, 250)
#define COLOR_BACKGROUND_FRAME wxColour(230, 220, 230)
//#define COLOR_BACKGROUND_FRAME wxColour(14, 17, 22)

// buttons
#define COLOR_BACKGROUND_BTN wxColour(66, 2, 60)
#define COLOR_TEXT_BTN wxColour(255, 255, 255)

#define COLOR_BACKGROUND_NAVBTN wxColour(23, 27, 33)


#define COLOR_BACKGROUND_LOGINBTN wxColour(50, 150, 50)
#define COLOR_TEXT_LOGINBTN wxColour(0,0,0)


//labels
#define COLOR_LBL wxColour(23, 27, 33)
#define FONT_SIZE_LBL 12


#define RED wxColour(220, 50, 50)

// character limits for usernames and passwords
#define MIN_CHAR_NAME 3
#define MAX_CHAR_NAME 15
#define MIN_CHAR_PASSWORD 8
#define MAX_CHAR_PASSWORD 40

// Deklaracja funkcji GetLabelFont
wxFont SetTheFont(int fontSize = FONT_SIZE_LBL, bool bold=false);
void OnCursorHover(wxMouseEvent& event);


#endif // STYLDEF_H
