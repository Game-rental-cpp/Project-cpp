#include "MyAccPanel_Controller.h"
#include "MyAccPanel.h"
#include "Style.h"
#include "UserCRUD.h"
#include "UserNormal.h"
#include "UserPremium.h"
#include "MyAccPanel_Logic.h"
#include "MainPanel_Logic.h"
#include "Game.h"
#include <wx/datetime.h>
//#include <wx/timespan.h>


MyAccPanel_Controller::MyAccPanel_Controller(MyAccPanel* parentEl, wxStaticText* logoutLabel,
    wxPanel* userPanel,
    wxStaticText* loginLabel,
    wxButton* logoutBtn,
    wxTextCtrl* premiumInput,
    wxScrolledWindow* gamesPanel) : 
    parentEl(parentEl), 
    logoutLabel(logoutLabel), 
    userPanel(userPanel), 
    loginLabel(loginLabel), 
    logoutBtn(logoutBtn), 
    premiumInput(premiumInput), 
    gamesPanel(gamesPanel) {}

void MyAccPanel_Controller::BindEvents() {
    parentEl->Bind(wxEVT_SHOW, &MyAccPanel_Controller::OnPanelShow, this);
    logoutBtn->Bind(wxEVT_BUTTON, &MyAccPanel_Controller::LogOut, this);
    premiumInput->Bind(wxEVT_CHAR_HOOK, &MyAccPanel_Controller::OnEnterPressed, this, wxID_ANY);
}

void MyAccPanel_Controller::OnMouseHover(wxMouseEvent& event) {
    OnCursorHover(event);
}

void MyAccPanel_Controller::OnEnterPressed(wxKeyEvent& event) {
    // Detect Enter key
    if (event.GetKeyCode() == WXK_RETURN) {
        wxString enteredText = premiumInput->GetValue();
        premiumInput->SetValue("");

        if (enteredText == "PREMIUM") {
            User* user = MyAccPanel_Logic::GetUser();
            std::string login = user->getLogin();
            delete user;
            user = nullptr;

            user = new UserPremium(login);
            MainPanel_Logic::SetUser(user);
            MyAccPanel_Logic::SetUser(user);

            premiumInput->Hide();
            wxLogMessage("Jesteœ cz³onkiem premium");
        }
        else
            wxLogMessage("Nieprawid³owy kod");
    }
    event.Skip();
}


void MyAccPanel_Controller::LogOut(wxCommandEvent& event) {
    userPanel->Hide();

    logoutLabel->Show();
    //TODO: usuñ usera i pusty string do _logged.txt
    UserCRUD::Update_logged("");
    User* user = MyAccPanel_Logic::GetUser();
    delete user;
    user = nullptr;
    event.Skip();
}

void MyAccPanel_Controller::OnPanelShow(wxShowEvent& event) {
    if (event.IsShown()) {

        std::string login = UserCRUD::ReadLogged();
        std::string userStr = UserCRUD::ReadUser(login);

        UpdateGamesPanel();

        User* user = MyAccPanel_Logic::GetUser();
        loginLabel = new wxStaticText(userPanel, wxID_ANY, wxString::Format("Zalogowany/a jako: %s", user->getLogin()), wxPoint(10, 10));
        logoutLabel->Hide();
        userPanel->Show();

        // Check if user is premium
        if(user->getPremium())
                premiumInput->Hide();
        else 
                premiumInput->Show();

        //wxLogMessage(wxString::Format("Wartoœæ bool: %s", user->getPremium() ? "true" : "false"));


        Layout();
    }
    event.Skip();
}


// This metohod executes after clicking on "oddaj" button
void MyAccPanel_Controller::UpdateUserGames(wxCommandEvent& event, std::string gameName)
{
    User* user = MyAccPanel_Logic::GetUser();
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    //button name is the same as game id
    wxString buttonName = button->GetName();
    user->removeUserGame(buttonName.ToStdString());
    UpdateGamesPanel();

    Game* game = MyAccPanel_Logic::CreateGameFromJSON(gameName);
    game->SetQuantity(game->GetQuantity()+1);

}


void MyAccPanel_Controller::UpdateGamesPanel() {

    if (gamesPanel) {
        gamesPanel->Hide();
        gamesPanel->Destroy();
    }

    User* user = MyAccPanel_Logic::GetUser();

    std::vector<User::UserGame> gamesVec = user->getUserGames();

    gamesPanel = nullptr;
    int height = gamesVec.size() <= 3 ? 330 : gamesVec.size() * 80;
    gamesPanel = new wxScrolledWindow(userPanel, wxID_ANY, wxPoint(0, 15), wxSize(userPanel->GetSize().GetWidth(), 330));
    gamesPanel->SetScrollRate(0, 10);  
    gamesPanel->SetBackgroundColour(COLOR_BACKGROUND_PANEL); // Set background color (optional)
    gamesPanel->SetVirtualSize(wxSize(410, height));


    if (gamesVec.size() == 0) {
        wxStaticText* noGameLabel = new wxStaticText(gamesPanel, wxID_ANY, "nie wypozyczono jeszcze zadnej gry", wxPoint(33, 150), wxDefaultSize);
        noGameLabel->SetForegroundColour(COLOR_LBL);
        noGameLabel->SetFont(SetTheFont());
    }


    for (int i = 0; i < gamesVec.size(); i++) {

        User::UserGame game = gamesVec[i];

        std::string gameName = game.GetName();
        std::string gameId = game.getId();
        std::string date = game.getDate();

        wxDateTime dt; //declare wxDateTime variable
        wxString::const_iterator end; // iterator

        dt.ParseFormat(date, "%d-%m-%y__%H-%M-%S", &end); //define formatted wxdateTime variable

        wxDateTime today = wxDateTime::Today();
        wxTimeSpan diff = dt - today; //time difference between the day of hiring the game and today

        int daysDifference = diff.GetDays(); //how many days passed from the day of hiring the game to today
        int daysLeft = (30 - daysDifference) < 0 ? 0 : (30 - daysDifference);

        //Creating gamePanel
        wxPanel* gamePanel = new wxPanel(gamesPanel, wxID_ANY, wxPoint(0, i*100), wxSize(userPanel->GetSize().GetWidth(), 100));
        //gamePanel->SetBackgroundColour(COLOR_BACKGROUND_FRAME); // Set background color (optional)

        wxGauge* progressBar = new wxGauge(gamePanel, wxID_ANY, 100, wxPoint(0, 50), wxDefaultSize, wxGA_SMOOTH);
        progressBar->SetValue(15);
        progressBar->SetRange(30);


        wxString labelNameText = wxString::Format("Nazwa gry: %s", gameName);

        // (label name is the same as game id + Lbl)
        wxStaticText* labelName = new wxStaticText(gamePanel, wxID_ANY, labelNameText, wxPoint(10, 10), wxDefaultSize, 0, gameId + "Lbl0");

        labelName->SetForegroundColour(COLOR_LBL);
        labelName->SetFont(SetTheFont());

        std::string buttonText = "Oddaj";

        // Create lambda expression wihich passes additional argument (gameName)
        auto updateGamesLambda = [this, gameName](wxCommandEvent& event) {
            // Call function with an additional argument
            UpdateUserGames(event, gameName);
            };

        // (button name is the same as game id)
        wxButton* hireBtn = new wxButton(gamePanel, wxID_ANY, buttonText, wxPoint(parentEl->GetSize().GetWidth() - 10 - 85, 10), wxSize(85, 35), 0, wxDefaultValidator, gameId);

        hireBtn->SetBackgroundColour(COLOR_BACKGROUND_BTN);
        hireBtn->SetForegroundColour(COLOR_TEXT_BTN);

        //instead of direct binding with UpdateUserGames use lambda expression
        hireBtn->Bind(wxEVT_BUTTON, updateGamesLambda);
        hireBtn->Bind(wxEVT_ENTER_WINDOW, &MyAccPanel_Controller::OnMouseHover, this);
        hireBtn->SetFont(SetTheFont());
    }
    gamesPanel->Show();
}



