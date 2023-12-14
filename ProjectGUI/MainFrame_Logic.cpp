#include "MainFrame_Logic.h"
#include "UserCRUD.h"
//#include "User.h"
#include "UserNormal.h"
#include "UserPremium.h"


void MainFrame_Logic::HideButton(wxButton* loginBtn, wxButton* myAccBtn) {
	if (UserCRUD::isLogged())
		loginBtn->Hide();
	else
		myAccBtn->Hide();
}

void MainFrame_Logic::CreateUser(User* user, MainPanel* mainPanel, MyAccPanel* myAccPanel, LoginPanel* loginPanel) {
    //std::string login= UserCRUD::WhoIsLogged();
      //std::string userStr= UserCRUD::ReadUser(login);
      // use json to extract information and pass it to the constructor
      //if(isPremium)
      //user = new UserPremium("login_normal");
      //else
    user = new UserNormal("login_normal");


    //myAccPanel->SetUser(user);
    //mainPanel->SetUser(user);
    //loginPanel->SetUser(user);
};
