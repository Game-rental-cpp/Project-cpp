#pragma once
#include <wx/wx.h>
#include "User.h"

class MyAccPanel;

class MyAccPanel_Controller : public wxPanel
{
public:
    MyAccPanel_Controller(MyAccPanel* parenEl);

 
    void BindEvents();
    void OnPanelShow(wxShowEvent& event);

private:
    MyAccPanel* parentEl;
   

};



