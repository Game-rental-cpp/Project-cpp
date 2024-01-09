#include "MyAccPanel_Controller.h"
#include "MyAccPanel.h"
#include "Style.h"
#include "UserCRUD.h"
#include "UserNormal.h"
#include "UserPremium.h"
#include "MyAccPanel_Logic.h"
#include "Log.h"
#include "MainPanel_Logic.h"
#include "Game.h"
#include <wx/datetime.h>



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
            wxMessageDialog* signupNameErrorDlg = new wxMessageDialog(parentEl, "Gratulacje! Zdobywasz konto premium", "Informacja");
            signupNameErrorDlg->ShowModal();
        }
        else{
            wxMessageDialog* signupNameErrorDlg = new wxMessageDialog(parentEl, "Nieprawid³owy kod", "B³¹d");
            signupNameErrorDlg->ShowModal();
        }
    }
    event.Skip();
}


void MyAccPanel_Controller::LogOut(wxCommandEvent& event) {
    userPanel->Hide();

    logoutLabel->Show();
    loginLabel->SetLabel("");
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
        loginLabel->SetLabel(wxString::Format("Zalogowany/a jako: %s", user->getLogin()));


        logoutLabel->Hide();
        userPanel->Show();

        // Check if user is premium
        if(user->getPremium())
                premiumInput->Hide();
        else 
                premiumInput->Show();


        Layout();
    }
    //else {
    //   /* if(loginLabel)
    //    loginLabel->Hide();*/
    //}
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
    int y = user->getPremium() ? 460 : 400;
    gamesPanel = nullptr;
    int height = gamesVec.size() <= 3 ? 330 : gamesVec.size() * 100+20;
    gamesPanel = new wxScrolledWindow(userPanel, wxID_ANY, wxPoint(0, 40), wxSize(userPanel->GetSize().GetWidth(), y));
    gamesPanel->SetScrollRate(0, 10);  
    gamesPanel->SetBackgroundColour(COLOR_BACKGROUND_PANEL); // Set background color (optional)
    gamesPanel->SetVirtualSize(wxSize(410, height));


    if (gamesVec.size() == 0) {
        wxStaticText* noGameLabel = new wxStaticText(gamesPanel, wxID_ANY, "Nie wypo¿yczono jeszcze ¿adnej gry", wxPoint(55, 150), wxDefaultSize);
        noGameLabel->SetForegroundColour(COLOR_LBL);
        noGameLabel->SetFont(SetTheFont(12, true));

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
        wxTimeSpan diff = today - dt; //time difference between the day of hiring the game and today

        int days; //How many days the user has to return
        if (user->getPremium())
            days = 60;
        else days = 30;

        int daysDifference = diff.GetDays(); //how many days passed from the day of hiring the game to today
        int daysLeft = (days - daysDifference) < 0 ? 0 : (days - daysDifference);


        //Creating gamePanel
        wxPanel* gamePanel = new wxPanel(gamesPanel, wxID_ANY, wxPoint(0, i*100), wxSize(userPanel->GetSize().GetWidth(), 100));
        wxGauge* progressBar = new wxGauge(gamePanel, wxID_ANY, 100, wxPoint(50, 65), wxDefaultSize, wxGA_SMOOTH);
        progressBar->SetValue(daysLeft);
        if(user->getPremium())
            progressBar->SetRange(60);
        else 
            progressBar->SetRange(30);

       
        wxString labelNameText = wxString::Format("%s", gameName);
        // (label name is the same as game id + Lbl)
        wxStaticText* labelName = new wxStaticText(gamePanel, wxID_ANY, labelNameText, wxPoint(50, 10), wxDefaultSize, 0, gameId + "Lbl0");
        labelName->SetForegroundColour(COLOR_LBL);
        labelName->SetFont(SetTheFont(15, true));

        wxString labelTimeText;
        if(daysLeft==0)
            labelTimeText = wxString::Format("Czas na oddanie up³yn¹³");
        else
            labelTimeText = wxString::Format("Do oddania zosta³o ci %d dni", daysLeft);

        // (label name is the same as game id + Lbl)
        wxStaticText* labelTime = new wxStaticText(gamePanel, wxID_ANY, labelTimeText, wxPoint(50, 40), wxDefaultSize, 0, gameId + "Lbl1");
        labelTime->SetForegroundColour(COLOR_LBL);
        labelTime->SetFont(SetTheFont(12));

        // Create lambda expression wihich passes additional argument (gameName)
        auto updateGamesLambda = [this, gameName](wxCommandEvent& event) {
            // Call function with an additional argument
            UpdateUserGames(event, gameName);
            };

        std::string buttonText = "Oddaj";
        // (button name is the same as game id)
        wxButton* hireBtn = new wxButton(gamePanel, wxID_ANY, buttonText, wxPoint(parentEl->GetSize().GetWidth() - 10 - 120, 10), wxSize(85, 35), 0, wxDefaultValidator, gameId);

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
        wxButton* rateBtn = new wxButton(gamePanel, wxID_ANY, "Oceñ", wxPoint(parentEl->GetSize().GetWidth() - 10 - 120, 50), wxSize(85, 35), 0, wxDefaultValidator, gameId);

        rateBtn->SetBackgroundColour(COLOR_BACKGROUND_BTN);
        rateBtn->SetForegroundColour(COLOR_TEXT_BTN);

        //instead of direct binding with UpdateUserGames use lambda expression
        rateBtn->Bind(wxEVT_BUTTON, rateGameLambda);
        rateBtn->Bind(wxEVT_ENTER_WINDOW, &MyAccPanel_Controller::OnMouseHover, this);
        rateBtn->SetFont(SetTheFont());


        auto it = game.GetUserRates().find(user->getLogin());

        //Check if the login has been found
        if (it != game.GetUserRates().end()) {
            // Found the rate of the user
            int userRating = it->second;
        }

    }
    gamesPanel->Show();
}



/// ////////////// Rating feature

// executes after clicking rateBtn
void MyAccPanel_Controller::RateGame(wxCommandEvent& event, std::string gameName, std::string login) {
    

    Game* game = MyAccPanel_Logic::CreateGameFromJSON(gameName);

    //get current user rate
    std::map <std::string, int> userRates = game->GetUserRates();
    auto it = userRates.find(login);
    int currentRate;
    if (it != userRates.end())
        currentRate = it->second;
    else currentRate = 0;
      
    GameCRUD::updateGame(game->GetName(), game->GetQuantity(), game->GetNrOfLoans(), game->GetRate(), game->GetUserRates());

    wxDialog* rateGameDialog= new wxDialog(parentEl, wxID_ANY, wxString::Format("Oceñ grê %s", gameName), wxDefaultPosition, wxSize(250, 70));
    rateGameDialog->SetMinSize(wxSize(250, 120));

    wxRadioButton* radio1 = new wxRadioButton(rateGameDialog, wxID_ANY, "Ocena: 1", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "radio1");
    wxRadioButton* radio2 = new wxRadioButton(rateGameDialog, wxID_ANY, "Ocena: 2", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "radio2");
    wxRadioButton* radio3 = new wxRadioButton(rateGameDialog, wxID_ANY, "Ocena: 3", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "radio3");
    wxRadioButton* radio4 = new wxRadioButton(rateGameDialog, wxID_ANY, "Ocena: 4", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "radio4");
    wxRadioButton* radio5 = new wxRadioButton(rateGameDialog, wxID_ANY, "Ocena: 5", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "radio5");



    radio1->Bind(wxEVT_RADIOBUTTON, &MyAccPanel_Controller::OnRadioSelect, this);
    radio2->Bind(wxEVT_RADIOBUTTON, &MyAccPanel_Controller::OnRadioSelect, this);
    radio3->Bind(wxEVT_RADIOBUTTON, &MyAccPanel_Controller::OnRadioSelect, this);
    radio4->Bind(wxEVT_RADIOBUTTON, &MyAccPanel_Controller::OnRadioSelect, this);
    radio5->Bind(wxEVT_RADIOBUTTON, &MyAccPanel_Controller::OnRadioSelect, this);

    switch (currentRate) {
    case 1: radio1->SetValue(true);
        newRate = 1;
        break;
    case 2: radio2->SetValue(true);
        newRate = 2;
        break;
    case 3: radio3->SetValue(true);
        newRate = 3;
        break;
    case 4: radio4->SetValue(true);
        newRate = 4;
        break;
    case 5: radio5->SetValue(true);
        newRate = 5;
        break;
    default: radio5->SetValue(true);
        newRate = 5;
        break;
    }

   
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(radio1, 0, wxALL, 5);
    sizer->Add(radio2, 0, wxALL, 5);
    sizer->Add(radio3, 0, wxALL, 5);
    sizer->Add(radio4, 0, wxALL, 5);
    sizer->Add(radio5, 0, wxALL, 5);

    rateGameDialog->SetSizer(sizer);
    rateGameDialog->Layout();
    rateGameDialog->Fit();

    wxButton* okButton = new wxButton(rateGameDialog, wxID_ANY, "Oceñ", wxPoint(100, 35), wxSize(85, 35), 0, wxDefaultValidator);
    okButton->Bind(wxEVT_BUTTON, [this, game, login](wxCommandEvent& event) {
        OnOcenButtonClick(event, game, login);
        });


    std::vector<wxRadioButton*> radioButtons = { radio1, radio2, radio3, radio4, radio5 };
    wxButton* resetBtn = new wxButton(rateGameDialog, wxID_ANY, "Cofnij ocenê", wxPoint(200, 35), wxSize(85, 35), 0, wxDefaultValidator);
    resetBtn->Bind(wxEVT_BUTTON, [this, &radioButtons](wxCommandEvent& event) {
        newRate = 0;

        // Uncheck all radio buttons
        for (auto& radioButton : radioButtons) {
            radioButton->SetValue(false);
        }
        });

    int result = rateGameDialog->ShowModal();
}

void MyAccPanel_Controller::OnRadioSelect(wxCommandEvent& event) {
    wxRadioButton* radioButton = dynamic_cast<wxRadioButton*>(event.GetEventObject());
    if (radioButton) {
        wxString label = radioButton->GetLabel();
       
        if (label == "Ocena: 1") {
            newRate= 1;
        }
        else if (label == "Ocena: 2") {
            newRate = 2;
        }
        else if (label == "Ocena: 3") {
            newRate = 3;
        }
        else if (label == "Ocena: 4") {
            newRate = 4;
        }
        else if (label == "Ocena: 5") {
            newRate = 5;
        }
    }

}

void MyAccPanel_Controller::OnOcenButtonClick(wxCommandEvent& event, Game* game, std::string login) {
    game->SetRate(newRate, login);
    GameCRUD::updateGame(game->GetName(), game->GetQuantity(), game->GetNrOfLoans(), game->GetRate(), game->GetUserRates());
    //newRate = -1;
    wxButton* okButton = dynamic_cast<wxButton*>(event.GetEventObject());
    if (okButton) {
        wxDialog* dialog = dynamic_cast<wxDialog*>(okButton->GetParent());
        if (dialog) {
            dialog->EndModal(wxID_OK);  // Close the dialog after clicking Oceñ
        }
    }
}
