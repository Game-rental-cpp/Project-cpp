#include "MyAccPanel_Controller.h"
#include "MyAccPanel.h"
#include "Style.h"
#include "UserCRUD.h"
#include "UserNormal.h"
#include "UserPremium.h"


MyAccPanel_Controller::MyAccPanel_Controller(MyAccPanel* parentEl, wxStaticText* logoutLabel,
    wxPanel* userPanel,
    wxStaticText* loginLabel,
    wxButton* logoutBtn,
    wxTextCtrl* premiumInput,
    wxScrolledWindow* gamesPanel) : parentEl(parentEl), logoutLabel(logoutLabel), userPanel(userPanel), loginLabel(loginLabel), logoutBtn(logoutBtn), premiumInput(premiumInput), gamesPanel(gamesPanel) {
    // Reszta kodu konstruktora, jeúli jest taka potrzebna
}


void MyAccPanel_Controller::BindEvents() {

    parentEl->Bind(wxEVT_SHOW, &MyAccPanel_Controller::OnPanelShow, this);
    logoutBtn->Bind(wxEVT_BUTTON, &MyAccPanel_Controller::LogOut, this);
    premiumInput->Bind(wxEVT_CHAR_HOOK, &MyAccPanel_Controller::OnEnterPressed, this, wxID_ANY);


}

void MyAccPanel_Controller::OnEnterPressed(wxKeyEvent& event) {
    // Detect Enter key
    if (event.GetKeyCode() == WXK_RETURN) {
        wxString enteredText = premiumInput->GetValue();
        premiumInput->SetValue("");

        if (enteredText == "PREMIUM") {
            premiumInput->Hide();

            wxLogMessage("Jesteú cz≥onkiem premium");

            //std::vector<User::UserGame> userGames = user->getUserGames();
            //delete user;
            //pobierz login przez cruda albo od starego usera.
            // UtwÛrz nowego uøytkownika typu UserPremium, ale nadal uøywajπc istniejπcego obiektu
         /*   user = new (user) UserPremium("login_premium");
            user->setUserGames(userGames);*/

        }
        else
            wxLogMessage("Nieprawid≥owy kod");
    }


    event.Skip();
}

void MyAccPanel_Controller::LogOut(wxCommandEvent& event) {
    userPanel->Hide();

    logoutLabel->Show();
    //usuÒ usera i pusty string do _logged.txt
    //user.reset();
    event.Skip();

}

//OnPanelShow wykonuje siÍ za kaødym wyswietleniem i ukryciem myAccPanel na ekranie;
void MyAccPanel_Controller::OnPanelShow(wxShowEvent& event)
{
    //Wykonaj jesli MyAccPanel zostal wyswietlony na ekranie
    if (event.IsShown()) {

        std::string login = UserCRUD::ReadLogged();
        std::string userStr = UserCRUD::ReadUser(login);

        UpdateGamesPanel();
        //use json to extract information and pass it to the constructor
       /* if(isPremium)
            user = new UserPremium("login_normal");*/
            //else
        //user = new UserNormal("piotrek123");

        //wxLogMessage("Type of log: %s", user->stringifyUser());


        //wxLogMessage(wxString::Format("%s",user->stringifyUser()));
        //loginLabel = new wxStaticText(userPanel, wxID_ANY, wxString::Format("Zalogowany/a jako: %s", user->getLogin()), wxPoint(10, 10));
        logoutLabel->Hide();

        if (true) {
            // Sprawdü, czy user jest instancjπ UserNormal
            //UserNormal* userN = dynamic_cast<UserNormal*>(user);
            //if (!userN) {
                // User jest obiektem klasy UserNormal
                //premiumInput->Hide();
            //}
        }


        userPanel->Show();


        Layout(); // Zaktualizuj uklad
    }


    event.Skip();
}











void MyAccPanel_Controller::UpdateGamesPanel() {

    if (gamesPanel) {
        gamesPanel->Hide();
        gamesPanel->Destroy();
    }

    //this vector will contain all games that should appear on screen (except those that shouldn't)
    std::vector<User::UserGame> gamesVec; //= user.getUserGames();

    //wxLogMessage("Formatted message: %s", filteredVector[0].GetName());


    gamesPanel = nullptr;
    int height = gamesVec.size() <= 3 ? 330 : gamesVec.size() * 80;
    gamesPanel = new wxScrolledWindow(parentEl, wxID_ANY, wxPoint(0, 150), wxSize(parentEl->GetSize().GetWidth(), 330));
    gamesPanel->SetScrollRate(0, 10);  // Ustawienia przewijania - drugi argument to liczba pikseli na jedno przewiniÍcie
    //gamesPanel->Hide();
    gamesPanel->SetBackgroundColour(RED); // Set background color (optional)
    gamesPanel->SetVirtualSize(wxSize(410, height));




    if (gamesVec.size() == 0) {
        wxStaticText* noGameLabel = new wxStaticText(gamesPanel, wxID_ANY, "nie wypozyczono jeszcze zadnej gry", wxPoint(33, 150), wxDefaultSize);
        noGameLabel->SetForegroundColour(COLOR_LBL);
        //noGameLabel->SetBackgroundColour(COLOR_BACKGROUND_LOGINBTN);
        noGameLabel->SetFont(SetTheFont());
    }




    for (int i = 0; i < gamesVec.size(); i++) {
        //wxLogMessage("s");

        User::UserGame game = gamesVec[i];

        std::string gameName = game.GetName();
        std::string gameId = game.getId();
        std::string date = game.getDate();
        //int x = rand() % (100); // Losowa pozycja x na panelu
        //int y = rand() % (200); // Losowa pozycja y na panelu

        //Creating elements inside gamesPanel
        wxString labelText0 = wxString::Format("Nazwa gry: %s", gameName);

        // (label name is the same as game name + Lbl)
        wxStaticText* gameLabel0 = new wxStaticText(gamesPanel, wxID_ANY, labelText0, wxPoint(10, 10 + i * 80), wxDefaultSize, 0, gameName + "Lbl0");

        gameLabel0->SetForegroundColour(COLOR_LBL);
        gameLabel0->SetFont(SetTheFont());


        //wxStaticText* gameLabel = new wxStaticText(gamesPanel, wxID_ANY, labelText, wxPoint(x, y));

        std::string buttonText = "Wypoøycz";

        // (button name is the same as game name)
        wxButton* hireBtn = new wxButton(gamesPanel, wxID_ANY, buttonText, wxPoint(parentEl->GetSize().GetWidth() - 10 - 85, 10 + i * 85), wxSize(85, 35), 0, wxDefaultValidator, gameId);

        hireBtn->SetBackgroundColour(COLOR_BACKGROUND_BTN);
        hireBtn->SetForegroundColour(COLOR_TEXT_BTN);

        hireBtn->Bind(wxEVT_BUTTON, &MyAccPanel_Controller::UpdateUserGame, this, wxID_ANY, wxID_ANY);
        //hireBtn->Bind(wxEVT_ENTER_WINDOW, &MyAccPanbel_Controller::OnMouseHover, this);
        hireBtn->SetFont(SetTheFont());


        

        //    /* else
        //         hireBtn->Enable(true);*/


    }
    gamesPanel->Show();
}




// This metohod executes after clicking on "oddaj" button
void MyAccPanel_Controller::UpdateUserGame(wxCommandEvent & event)
{


    //get the clicked button name
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    wxString buttonName = button->GetName();


    //user.removeUserGame(buttonName.ToStdString());
    //wxLogMessage("Type of log: %s", user.getLogin());


    //std::string log = user.stringifyGames();
    //wxLogMessage("Type of log: %s", log);

    //gamesVector = MainPanel_Controller::updateGame(buttonName, gamesPanel, gamesVector);
}
