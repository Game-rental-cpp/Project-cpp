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

    // use json to extract information and determine user type
    // For now, let's assume it's UserNormal
    //wxLogMessage(wxString::Format("%s", UserCRUD::ReadUser(login)));
    //wxLogMessage(wxString::Format("%s", UserCRUD::ReadLogged()));
    //wxLogMessage(wxString::Format("User existence: %s", std::to_string(UserCRUD::DoesExist(login)).c_str()));



    std::string userStr = UserCRUD::ReadUser(login);
    //wxLogMessage(wxString::Format("%s", userStr));

    try{
        json jsonData = json::parse(userStr); //parsing JSON string
        std::string passwordStr = jsonData.at("password"); //get value of key "password"
        //isPremium password = jsonData.at("password"); //get value of key "password"

        json gamesArray = jsonData.at("userGames");
        //if(gamesArray.size()>0)
        // Iterowanie po elementach tablicy
        for (const auto& game : gamesArray) {
            // Wyci¹ganie wartoœci z obiektu w tablicy
            User::UserGame userGame(game.at("name"));
            userGame.SetId(game.at("id"));
            userGame.SetDate(game.at("date"));
        }
    }
    catch (const std::exception& e) {
        wxLogMessage(wxString::Format("Error while processing JSON data: %s", e.what()));
        // Obs³u¿ b³¹d parsowania lub innego rodzaju b³êdu
    }





    User* user = new UserNormal(login);
    //wxLogMessage(wxString::Format("%s", user->stringifyUser()));

    MainPanel_Logic::SetUser(user);
    MyAccPanel_Logic::SetUser(user);
    return user;
}