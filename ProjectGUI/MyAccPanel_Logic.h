#pragma once


#include "User.h"
#include "Game.h"
#include <string>

class MyAccPanel_Logic
{
public:

    static User* GetUser();
    static void SetUser(User* u);

    static Game* CreateGameFromJSON(std::string gameName);

private:
    static User* user;

};
