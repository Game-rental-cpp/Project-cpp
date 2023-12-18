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
    wxLogMessage(wxString::Format("%.3f", game->GetRate()));

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


        // Create lambda expression wihich passes additional argument (gameName)
        auto updateGamesLambda = [this, gameName](wxCommandEvent& event) {
            // Call function with an additional argument
            UpdateUserGames(event, gameName);
            };

        std::string buttonText = "Oddaj";
        // (button name is the same as game id)
        wxButton* hireBtn = new wxButton(gamePanel, wxID_ANY, buttonText, wxPoint(parentEl->GetSize().GetWidth() - 10 - 85, 10), wxSize(85, 35), 0, wxDefaultValidator, gameId);

        hireBtn->SetBackgroundColour(COLOR_BACKGROUND_BTN);
        hireBtn->SetForegroundColour(COLOR_TEXT_BTN);

        //instead of direct binding with UpdateUserGames use lambda expression
        hireBtn->Bind(wxEVT_BUTTON, updateGamesLambda);
        hireBtn->Bind(wxEVT_ENTER_WINDOW, &MyAccPanel_Controller::OnMouseHover, this);
        hireBtn->SetFont(SetTheFont());
        ////////////////////
        /////////////////////

        std::string login = user->getLogin();
        User* user = MyAccPanel_Logic::GetUser();

        auto rateGameLambda = [this, gameName, login](wxCommandEvent& event) {
            // Call function with an additional argument
            RateGame(event, gameName, login);
            };

        // (button name is the same as game id)
        wxButton* rateBtn = new wxButton(gamePanel, wxID_ANY, "Oceñ", wxPoint(parentEl->GetSize().GetWidth() - 10 - 85, 50), wxSize(85, 35), 0, wxDefaultValidator, gameId);

        rateBtn->SetBackgroundColour(COLOR_BACKGROUND_BTN);
        rateBtn->SetForegroundColour(COLOR_TEXT_BTN);

        //instead of direct binding with UpdateUserGames use lambda expression
        rateBtn->Bind(wxEVT_BUTTON, rateGameLambda);
        rateBtn->Bind(wxEVT_ENTER_WINDOW, &MyAccPanel_Controller::OnMouseHover, this);
        rateBtn->SetFont(SetTheFont());


        auto it = game.GetUserRates().find(user->getLogin());

        // SprawdŸ, czy login zosta³ znaleziony
        if (it != game.GetUserRates().end()) {
            // Znaleziono ocenê dla danego u¿ytkownika
            int userRating = it->second;
            //slider->SetValue(userRating);
        }

    }
    gamesPanel->Show();
}




void MyAccPanel_Controller::RateGame(wxCommandEvent& event, std::string gameName, std::string login) {
    // Tutaj mo¿esz uzyskaæ wartoœæ suwaka za pomoc¹: event.GetPosition()

    Game* game = MyAccPanel_Logic::CreateGameFromJSON(gameName);

    //get current user rate
    std::map <std::string, int> userRates = game->GetUserRates();
    auto it = userRates.find(login);
    int currentRate;
    if (it != userRates.end()) 
        currentRate = it->second;
      
    GameCRUD::updateGame(game->GetName(), game->GetQuantity(), game->GetNrOfLoans(), game->GetRate(), game->GetUserRates());

    wxDialog* rateGameDialog= new wxDialog(parentEl, wxID_ANY, wxString::Format("Oceñ grê %s", gameName), wxDefaultPosition, wxSize(300, 150));
    rateGameDialog->SetMinSize(wxSize(500, 450));

    wxRadioButton* radio1 = new wxRadioButton(rateGameDialog, wxID_ANY, "Ocena 1", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "radio1");
    wxRadioButton* radio2 = new wxRadioButton(rateGameDialog, wxID_ANY, "Ocena 2", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "radio2");
    wxRadioButton* radio3 = new wxRadioButton(rateGameDialog, wxID_ANY, "Ocena 3", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "radio3");
    wxRadioButton* radio4 = new wxRadioButton(rateGameDialog, wxID_ANY, "Ocena 4", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "radio4");
    wxRadioButton* radio5 = new wxRadioButton(rateGameDialog, wxID_ANY, "Ocena 5", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "radio5");


    radio1->Bind(wxEVT_RADIOBUTTON, &MyAccPanel_Controller::OnRadioSelect, this);
    radio2->Bind(wxEVT_RADIOBUTTON, &MyAccPanel_Controller::OnRadioSelect, this);
    radio3->Bind(wxEVT_RADIOBUTTON, &MyAccPanel_Controller::OnRadioSelect, this);
    radio4->Bind(wxEVT_RADIOBUTTON, &MyAccPanel_Controller::OnRadioSelect, this);
    radio5->Bind(wxEVT_RADIOBUTTON, &MyAccPanel_Controller::OnRadioSelect, this);

    switch (currentRate) {
    case 1: radio1->SetValue(true);
        break;
    case 2: radio2->SetValue(true);
        break;
    case 3: radio3->SetValue(true);
        break;
    case 4: radio4->SetValue(true);
        break;
    case 5: radio5->SetValue(true);
        break;
    default: radio1->SetValue(true);
        break;
    }

    // Dodaj radio buttony do sizer'a (jeœli u¿ywasz sizer'a)
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(radio1, 0, wxALL, 5);
    sizer->Add(radio2, 0, wxALL, 5);
    sizer->Add(radio3, 0, wxALL, 5);
    sizer->Add(radio4, 0, wxALL, 5);
    sizer->Add(radio5, 0, wxALL, 5);

    rateGameDialog->SetSizer(sizer);
    rateGameDialog->Layout();
    rateGameDialog->Fit();

    wxButton* okButton = new wxButton(rateGameDialog, wxID_OK, "OK", wxPoint(50, 50), wxSize(85, 35), 0, wxDefaultValidator, "OK");
    okButton->Bind(wxEVT_BUTTON, [this, game, login](wxCommandEvent& event) {
        OnOKButtonClick(event, game, login);
        });

    wxButton* resetBtn = new wxButton(rateGameDialog, wxID_OK, "Cofnij ocenê", wxPoint(100, 50), wxSize(85, 35), 0, wxDefaultValidator, "OK");

    // Wyœwietlamy dialog
    int result = rateGameDialog->ShowModal();
}

void MyAccPanel_Controller::OnRadioSelect(wxCommandEvent& event) {
    wxRadioButton* radioButton = dynamic_cast<wxRadioButton*>(event.GetEventObject());
    if (radioButton) {
        wxString label = radioButton->GetLabel();
        //wxLogMessage("Wybrano ocenê: %s", label);


        // Przyk³adowy kod, który zwraca wartoœæ int w zale¿noœci od wybranego przycisku radio
        if (label == "Ocena 1") {
            newRate= 1;
        }
        else if (label == "Ocena 2") {
            newRate = 2;
        }
        else if (label == "Ocena 3") {
            newRate = 3;
        }
        else if (label == "Ocena 4") {
            newRate = 4;
        }
        else if (label == "Ocena 5") {
            newRate = 5;
        }
    }

}

void MyAccPanel_Controller::OnOKButtonClick(wxCommandEvent& event, Game* game, std::string login) {

    wxLogMessage(wxString::Format("%d %s", newRate, login));
    game->SetRate(newRate, login);
    GameCRUD::updateGame(game->GetName(), game->GetQuantity(), game->GetNrOfLoans(), game->GetRate(), game->GetUserRates());
    newRate = -1;
    wxButton* okButton = dynamic_cast<wxButton*>(event.GetEventObject());
    if (okButton) {
        wxDialog* dialog = dynamic_cast<wxDialog*>(okButton->GetParent());
        if (dialog) {
            dialog->EndModal(wxID_OK);  // Zamknij dialog po naciœniêciu OK
        }
    }
}
