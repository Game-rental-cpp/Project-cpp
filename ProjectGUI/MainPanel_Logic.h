#pragma once

#include <wx/wx.h>
#include <vector>
#include "Game.h"
#include "User.h"

class MainPanel_Logic : public wxPanel
{
public:
    static Game CreateGameFromJSON(int i);
    static std::vector<Game> fulfillGamesVector(int n);
    static std::vector<Game> sortVector(std::vector<Game> gamesVector, int choice, int gameCount);
    //void SetUser(User* u) { user = u; }
    static User* createUser();
    static void SetUser(User* u);
    
private:
    //static std::vector<Game> vec;
    static User* user;
};
