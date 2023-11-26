// MainPanel.cpp
#include "MainPanel.h"
#include "MainPanel_Logic.h"
#include "MainPanel_Controller.h"
#include "Style.h"
#include "UserCRUD.h"
//for some reason code works without including <vector> and "GameCRUD.h"
#include <vector>
#include "GameCRUD.h"

std::vector<Game> gamesVector; 
//std::vector<Game> helpGamesVector;

//How many different games
int gameCount = GameCRUD::countGames();

MainPanel::MainPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    //Convert gameCount into string
    wxString gameCountStr = wxString::Format("%d", gameCount);
    // Creating a label
    label = new wxStaticText(this, wxID_ANY, "Liczba ró¿nych gier: " + gameCountStr, wxPoint(10, 50));
    label->SetForegroundColour(COLOR_LBL);
    label->SetFont(SetTheFont());

    /////////
    wxArrayString sortOptions;
    sortOptions.Add("Alfabetycznie (A-Z)");
    sortOptions.Add("Alfabetycznie (Z-A)");

    sortChoice = new wxChoice(this, wxID_ANY, wxPoint(10, 75+3), wxSize(146, 175), sortOptions);
    sortChoice->SetSelection(0);
    sortChoice->Bind(wxEVT_CHOICE, &MainPanel::OnChoice, this);
    sortChoice->SetFont(SetTheFont(11));  
    ////////////

    searchInput = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(GetClientSize().GetWidth() - 10 - 30 - 190, 75), wxSize(190, 30), wxBORDER_RAISED);
    searchInput->SetHint("Wyszukaj grê...");
    searchInput->Connect(wxEVT_TEXT, wxCommandEventHandler(MainPanel::OnSearchChange), nullptr, this);
    searchInput->SetFocus();
    searchInput->SetFont(SetTheFont());

    resetBtn = new wxButton(this, wxID_ANY, "X", wxPoint(GetClientSize().GetWidth() - 10 - 30, 74), wxSize(30, 31), wxBORDER_NONE);
    resetBtn->SetBackgroundColour(RED);
    resetBtn->SetForegroundColour(COLOR_TEXT_BTN);
    resetBtn->Bind(wxEVT_BUTTON, &MainPanel::OnResetButtonClick, this, wxID_ANY, wxID_ANY);
    resetBtn->SetFont(SetTheFont());
    resetBtn->Bind(wxEVT_ENTER_WINDOW, &MainPanel::OnMouseHover, this);

    /////////////

    gamesVector= MainPanel_Logic::fulfillGamesVector(gameCount);

    Bind(wxEVT_SHOW, &MainPanel::OnPanelShow, this);
}

void MainPanel::OnMouseHover(wxMouseEvent& event) {
    ChangeCursor(event);
}

//This functions executes when choosing sorting method (A-Z or Z-A)
void MainPanel::OnChoice(wxCommandEvent& event) {
    int currentSortChoice = sortChoice->GetSelection();

    // Check if user chose the same sort option two times in a row
    if (currentSortChoice == previousSortChoice) {
        return;
    }

    previousSortChoice = currentSortChoice;
    std::vector<Game> helpGamesVector = MainPanel_Logic::sortVector(gamesVector, currentSortChoice, gameCount);

    gamesVector = helpGamesVector;
    if (gamesPanel) {
        UpdateGamesPanel(MainPanel_Logic::sortVector(gamesVector, currentSortChoice, gameCount));
    }

}

void MainPanel::OnPanelShow(wxShowEvent& event)
{
     //Do if MainPanel has occured on the screen
    if (event.IsShown()) {
        this->SetBackgroundColour(COLOR_BACKGROUND_PANEL); // Set background color (optional)

        //if (gamesPanel) {
            UpdateGamesPanel(gamesVector);
        //}

    }

    event.Skip();
}


//This metohod executes after clicking on "wypozycz" button
void MainPanel::UpdateGame(wxCommandEvent& event)
{
    bool logged = UserCRUD::isLogged();

    if (!logged) {
        wxDialog* dialog = new wxDialog(this, wxID_ANY, "Musisz siê najpierw zalogowaæ, aby móc wypo¿yczyæ grê");
        dialog->ShowModal();
        dialog->Destroy();
        return;
    }

    gamesVector=  MainPanel_Controller::updateGame(event, gamesPanel, gamesVector);
}

void MainPanel::OnSearchChange(wxCommandEvent& event) {
    UpdateGamesPanel(gamesVector);
    event.Skip(); 
}

void MainPanel::OnResetButtonClick(wxCommandEvent& event) {
    //if input is already empty, dont't rerender gamesPanel
    if (searchInput->GetValue() == "")
        return;

    searchInput->SetValue("");  // set empty string to the input
    OnSearchChange(event);
    event.Skip();
}













/*
Function adds labels of games and hire buttons to gamesPanel
@param std::vector<Game> gamesVector
*/
void MainPanel::UpdateGamesPanel(std::vector<Game> gamesVector)
{
    if (gamesPanel) {
        gamesPanel->Hide();
        gamesPanel->Destroy();
    }
    
   
    //this vector will contain all games that should appear on screen (except those that shouldn't)
    std::vector<Game> filteredVector;
    wxString enteredText = searchInput->GetValue();

    //This loop pushes appropriate vectors to filteredVector
    for (int i = 0; i < gameCount; i++) {
        Game game = gamesVector[i];
        if (game.GetName().find(enteredText.Lower()) == std::string::npos && enteredText != "")
            continue;
        filteredVector.push_back(game);
    }


    gamesPanel = nullptr;
    int height = filteredVector.size() <= 3 ? 350 : filteredVector.size() * 50;
    gamesPanel = new wxScrolledWindow(this, wxID_ANY, wxPoint(0, 150), wxSize(GetClientSize().GetWidth(), height));
    gamesPanel->SetScrollRate(0, 10);  // Ustawienia przewijania - drugi argument to liczba pikseli na jedno przewiniêcie
    //gamesPanel->Hide();
    gamesPanel->SetBackgroundColour(RED); // Set background color (optional)
    gamesPanel->SetVirtualSize(wxSize(410, 300));




    if (filteredVector.size() == 0) {
        wxStaticText* noGameLabel = new wxStaticText(gamesPanel, wxID_ANY, "¯adna z gier nie spe³nia warunków wyszukiwania", wxPoint(33, 150), wxDefaultSize);
        noGameLabel->SetForegroundColour(COLOR_LBL);
        //noGameLabel->SetBackgroundColour(COLOR_BACKGROUND_LOGINBTN);
        noGameLabel->SetFont(SetTheFont());
    }




    for (int i = 0; i < filteredVector.size(); i++) {

        Game game = filteredVector[i];

        std::string gameName = std::string(game.GetName());
        int gameQuantity = game.GetQuantity();

        //int x = rand() % (100); // Losowa pozycja x na panelu
        //int y = rand() % (200); // Losowa pozycja y na panelu

        //Creating elements inside gamesPanel
        wxString labelText = wxString::Format("Nazwa gry: %s, iloœæ sztuk: %d", gameName, gameQuantity);
        // (label name is the same as game name + Lbl)
        wxStaticText* gameLabel = new wxStaticText(gamesPanel, wxID_ANY, labelText, wxPoint(10, 10 + i * 35), wxDefaultSize, 0, gameName + "Lbl");
        gameLabel->SetForegroundColour(COLOR_LBL);
        gameLabel->SetFont(SetTheFont());


        //wxStaticText* gameLabel = new wxStaticText(gamesPanel, wxID_ANY, labelText, wxPoint(x, y));
        
        std::string buttonText= "Wypo¿ycz";

        // (button name is the same as game name)
        wxButton* hireBtn = new wxButton(gamesPanel, wxID_ANY, buttonText, wxPoint(GetClientSize().GetWidth() - 10 - 85, 10+ i* 35), wxSize(85, 35), 0, wxDefaultValidator, gameName);
        
        hireBtn->SetBackgroundColour(COLOR_BACKGROUND_BTN);
        hireBtn->SetForegroundColour(COLOR_TEXT_BTN);

        hireBtn->Bind(wxEVT_BUTTON, &MainPanel::UpdateGame, this, wxID_ANY, wxID_ANY);
        hireBtn->Bind(wxEVT_ENTER_WINDOW, &MainPanel::OnMouseHover, this);
        hireBtn->SetFont(SetTheFont());
      
        if (gameQuantity == 0) 
            MainPanel_Controller::disableButton(hireBtn);
        
       /* else
            hireBtn->Enable(true);*/


    }
    gamesPanel->Show();


}



