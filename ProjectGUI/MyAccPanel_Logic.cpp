#include "MyAccPanel_Logic.h"

//#include "UserCRUD.h"
//#include "GameCRUD.h"

#include "User.h"
#include "UserNormal.h"
#include "UserPremium.h"



User* MyAccPanel_Logic::user = nullptr;

User* MyAccPanel_Logic::GetUser() {

    return MyAccPanel_Logic::user;
    //return user;
}


void MyAccPanel_Logic::SetUser(User* u) {
    MyAccPanel_Logic::user = u;
}