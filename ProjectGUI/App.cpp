// App.cpp
#include <wx/wx.h>
#include "MainFrame.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        MainFrame* frame = new MainFrame("Moja aplikacja wxWidgets", wxPoint(50, 50), wxSize(450, 600));
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
