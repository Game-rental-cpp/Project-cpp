#pragma once

#include <wx/textfile.h>
#include <wx/wx.h>
#include "Game.h"
#include "json.hpp"
#include <vector>
#include "MainPanel_Logic.h"

class MainPanel_Controller : public wxPanel
{
public:
  
    static std::vector<Game> updateGame(wxCommandEvent& event, wxPanel* gamesPanel, std::vector<Game> gamesVector);

private:
    static std::vector<Game> vec;
};
