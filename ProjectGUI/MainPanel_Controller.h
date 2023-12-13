#pragma once
#include <wx/wx.h>
#include <vector>
#include "Game.h"
#include "User.h"


class MainPanel_Controller : public wxPanel
{
public:
  
    static std::vector<Game> updateGame(wxString buttonName, wxPanel* gamesPanel, std::vector<Game> gamesVector);
    static void disableButton(const wxString& buttonName);

private:
    static std::vector<Game> vec;
};
