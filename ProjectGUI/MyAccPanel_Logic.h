#pragma once


#include "User.h"

class MyAccPanel_Logic
{
public:

    static User* GetUser();
    static void SetUser(User* u);

private:
    //static std::vector<Game> vec;
    static User* user;
};
