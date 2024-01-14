// App.cpp
#include <wx/wx.h>
#include "MainFrame.h"
#include "Log.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        wxDateTime now = wxDateTime::Now(); // Today's date and time 
        std::string date = now.Format(wxT("%d-%m-%y__%H-%M-%S"), wxDateTime::CET).ToStdString(); // convert wxDateTime to string
        writeToLog("\n" + date + "\nProgram zostal uruchomiony");
        MainFrame* frame = new MainFrame(L"Wypożyczalnia gier planszowych", wxPoint(50, 50), wxSize(435, 610));
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
