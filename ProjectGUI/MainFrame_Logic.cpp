#include "MainFrame_Logic.h"
#include "UserCRUD.h"
//#include "User.h"
#include "UserNormal.h"
#include "UserPremium.h"
#include "User.h"
#include "MainPanel_Logic.h"
#include "MyAccPanel_Logic.h"


void MainFrame_Logic::HideButton(wxButton* loginBtn, wxButton* myAccBtn) {
	if (UserCRUD::isLogged())
		loginBtn->Hide();
	else
		myAccBtn->Hide();
}

User* MainFrame_Logic::CreateUser() {
    std::string login = UserCRUD::ReadLogged();
    if (login == "")
        return nullptr;

    // use json to extract information and determine user type
    // For now, let's assume it's UserNormal
    User* user = new UserNormal(login);
    //user->SetIsPremium(false);

    MainPanel_Logic::SetUser(user);
    MyAccPanel_Logic::SetUser(user);
    return user;
}