#pragma once
#include <wx/wx.h>
#include <vector>
#include "Game.h"



class MainPanel_Controller : public wxPanel
{
public:
  
    static std::vector<Game> updateGame(wxCommandEvent& event, wxPanel* gamesPanel, std::vector<Game> gamesVector);
    static void disableButton(wxButton* button);

private:
    static std::vector<Game> vec;
};
