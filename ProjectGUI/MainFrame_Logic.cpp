#include "MainFrame_Logic.h"
#include "UserCRUD.h"
//#include "User.h"
#include "UserNormal.h"
#include "UserPremium.h"
#include "User.h"
#include "MainPanel_Logic.h"
#include "MyAccPanel_Logic.h"
#include <wx/wx.h>
#include "json.hpp"
//#include <wx/wx.h>

using json = nlohmann::json;

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

    std::string userStr = UserCRUD::ReadUser(login);

    json jsonData = json::parse(userStr); //parsing JSON string
    bool isPremium = jsonData.at("isPremium"); //extract isPremium value

    User* user;
    
    if(isPremium)
        user = new UserPremium(login);
    else
        user = new UserNormal(login);

    MainPanel_Logic::SetUser(user);
    MyAccPanel_Logic::SetUser(user);
    return user;
}