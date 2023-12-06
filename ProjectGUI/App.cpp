// App.cpp
#include <wx/wx.h>
#include "MainFrame.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        MainFrame* frame = new MainFrame("Wypo¿yczalnia gier planszowych", wxPoint(50, 50), wxSize(435, 597));
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
