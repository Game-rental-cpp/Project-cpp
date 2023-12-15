#include "MyAccPanel_Controller.h"
#include "MyAccPanel.h"
#include "Style.h"
#include "UserCRUD.h"
#include "UserNormal.h"
#include "UserPremium.h"
#include "MyAccPanel_Logic.h"

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
    //user.reset();
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

        Layout(); 
    }
    event.Skip();
}

// This metohod executes after clicking on "oddaj" button
void MyAccPanel_Controller::UpdateUserGames(wxCommandEvent& event)
{
    User* user = MyAccPanel_Logic::GetUser();
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    wxString buttonName = button->GetName();
    user->removeUserGame(buttonName.ToStdString());
    UpdateGamesPanel();
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
    gamesPanel->SetScrollRate(0, 10);  // Ustawienia przewijania - drugi argument to liczba pikseli na jedno przewiniêcie
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

        //Creating elements inside gamesPanel
        wxString labelText0 = wxString::Format("Nazwa gry: %s", gameName);

        // (label name is the same as game id + Lbl)
        wxStaticText* gameLabel0 = new wxStaticText(gamesPanel, wxID_ANY, labelText0, wxPoint(10, 10 + i * 80), wxDefaultSize, 0, gameId + "Lbl0");

        gameLabel0->SetForegroundColour(COLOR_LBL);
        gameLabel0->SetFont(SetTheFont());

        std::string buttonText = "Oddaj";

        // (button name is the same as game id)
        wxButton* hireBtn = new wxButton(gamesPanel, wxID_ANY, buttonText, wxPoint(parentEl->GetSize().GetWidth() - 10 - 85, 10 + i * 85), wxSize(85, 35), 0, wxDefaultValidator, gameId);

        hireBtn->SetBackgroundColour(COLOR_BACKGROUND_BTN);
        hireBtn->SetForegroundColour(COLOR_TEXT_BTN);

        hireBtn->Bind(wxEVT_BUTTON, &MyAccPanel_Controller::UpdateUserGames, this, wxID_ANY, wxID_ANY);
        hireBtn->Bind(wxEVT_ENTER_WINDOW, &MyAccPanel_Controller::OnMouseHover, this);
        hireBtn->SetFont(SetTheFont());
    }
    gamesPanel->Show();
}



