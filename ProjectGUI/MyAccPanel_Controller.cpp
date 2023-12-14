#include "MyAccPanel_Controller.h"
#include "MyAccPanel.h"
#include "Style.h"
#include "UserCRUD.h"
#include "UserNormal.h"
#include "UserPremium.h"


MyAccPanel_Controller::MyAccPanel_Controller(MyAccPanel* parentEl) : parentEl(parentEl) {
    // Reszta kodu konstruktora, jeúli jest taka potrzebna
}


void MyAccPanel_Controller::BindEvents() {

    parentEl->Bind(wxEVT_SHOW, &MyAccPanel_Controller::OnPanelShow, this);

}

//OnPanelShow wykonuje siÍ za kaødym wyswietleniem i ukryciem myAccPanel na ekranie;
void MyAccPanel_Controller::OnPanelShow(wxShowEvent& event)
{
    //Wykonaj jesli MyAccPanel zostal wyswietlony na ekranie
    if (event.IsShown()) {

        std::string login = UserCRUD::ReadLogged();
        std::string userStr = UserCRUD::ReadUser(login);
        //use json to extract information and pass it to the constructor
       /* if(isPremium)
            user = new UserPremium("login_normal");*/
            //else
        //user = new UserNormal("piotrek123");

        //wxLogMessage("Type of log: %s", user->stringifyUser());


        //wxLogMessage(wxString::Format("%s",user->stringifyUser()));
        //loginLabel = new wxStaticText(userPanel, wxID_ANY, wxString::Format("Zalogowany/a jako: %s", user->getLogin()), wxPoint(10, 10));
        //logoutLabel->Hide();

        if (true) {
            // Sprawdü, czy user jest instancjπ UserNormal
            //UserNormal* userN = dynamic_cast<UserNormal*>(user);
            //if (!userN) {
                // User jest obiektem klasy UserNormal
                //premiumInput->Hide();
            //}
        }


        //userPanel->Show();


        Layout(); // Zaktualizuj uklad
    }


    event.Skip();
}