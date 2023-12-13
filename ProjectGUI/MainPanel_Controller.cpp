#include "MainPanel_Controller.h"
#include "MainPanel_Logic.h"
#include "MainPanel.h"
#include "Style.h"
#include "UserCRUD.h"

int gameCount = GameCRUD::countGames();

MainPanel_Controller::MainPanel_Controller(MainPanel* parentEl, wxTextCtrl* searchInput, wxButton* resetBtn, wxChoice* sortChoice)
    : parentEl(parentEl), searchInput(searchInput), resetBtn(resetBtn), sortChoice(sortChoice), gamesPanel(gamesPanel),
    gamesVector(MainPanel_Logic::fulfillGamesVector(gameCount)) {
    // Reszta kodu konstruktora, jeœli jest taka potrzebna
}


void MainPanel_Controller::BindEvents() {

    searchInput->Connect(wxEVT_TEXT, wxCommandEventHandler(MainPanel_Controller::OnSearchChange), nullptr, this);
    sortChoice->Bind(wxEVT_CHOICE, &MainPanel_Controller::OnChoice, this);
    resetBtn->Bind(wxEVT_BUTTON, &MainPanel_Controller::OnResetButtonClick, this, wxID_ANY, wxID_ANY);
    resetBtn->Bind(wxEVT_ENTER_WINDOW, &MainPanel_Controller::OnMouseHover, this);
    //Bind(wxEVT_SHOW, &MainPanel_Controller::OnShowPanel, this);
    parentEl->Bind(wxEVT_SHOW, &MainPanel_Controller::OnShowPanel, this);

}

void MainPanel_Controller::OnShowPanel(wxShowEvent& event) {
    //wxLogMessage("Show");
    //Do if MainPanel has occured on the screen
    if (event.IsShown()) {
        parentEl->SetBackgroundColour(COLOR_BACKGROUND_PANEL); // Set background color (optional)
        searchInput->SetFocus();
        //if (gamesPanel) {
        UpdateGamesPanel(gamesVector);
        //}

    }

    event.Skip();
}

/*
This function updates game label (and button) 
@param wxCommandEvent& event
@param wxPanel* gamesPanel
@param std::vector<Game> gamesVector
*/
std::vector<Game> MainPanel_Controller::updateGame(wxString buttonName, wxPanel* gamesPanel, std::vector<Game> gamesVector) {
    

        //take the unique name of the clicked button

        //wxLogMessage(buttonName);

        //Search for the corresponding label for the clicked button 
        wxStaticText* correspondingLabel1 = wxDynamicCast(gamesPanel->FindWindowByName(buttonName + "Lbl1"), wxStaticText);
        wxStaticText* correspondingLabel2 = wxDynamicCast(gamesPanel->FindWindowByName(buttonName + "Lbl2"), wxStaticText);
        
        // Take current label text
        wxString labelText1 = correspondingLabel1->GetLabel();
        wxString labelText2 = correspondingLabel2->GetLabel();

        // Take number (quantity) from label
        int quantity;
        int nrOfLoans;

        labelText1.AfterLast(' ').ToInt(&quantity);
        labelText2.AfterLast(' ').ToInt(&nrOfLoans);

        //In loop the Game object from the vector is updated and then the label is updated
        for (int i = 0; i < gamesVector.size(); i++) {

            //search for the Game which name is the same as the name of clicked button
            if (gamesVector[i].GetName() == buttonName) {

                //wxLogMessage(wxString(gamesVector[i].GetName().c_str()));
                
                //update json file - set the current value of available games (quantity) decreased by one
                gamesVector[i].SetQuantity(gamesVector[i].GetQuantity() - 1);
                gamesVector[i].SetNrOfLoans(gamesVector[i].GetNrOfLoans() + 1);

                wxString newLabelText1 = labelText1.BeforeLast(' ') + wxString::Format(" %ld", gamesVector[i].GetQuantity());
                correspondingLabel1->SetLabel(newLabelText1);
                wxString newLabelText2 = labelText2.BeforeLast(' ') + wxString::Format(" %ld", gamesVector[i].GetNrOfLoans());
                correspondingLabel2->SetLabel(newLabelText2);

                //If there are no games available, disable hire button
                if (gamesVector[i].GetQuantity() == 0) {
                    disableButton(buttonName);               
                }
                    

                break; // The game has been found, break the loop
            }

        }

        correspondingLabel1->Refresh();
    
    return gamesVector;
}

void MainPanel_Controller::OnSearchChange(wxCommandEvent& event) {
    //wxLogMessage("qwqw");
    UpdateGamesPanel(gamesVector);

    event.Skip();
}

// MainPanel_Controller.cpp
void MainPanel_Controller::disableButton(const wxString& buttonName) {
    // Wyszukaj przycisk na podstawie jego nazwy
    wxButton* button = wxDynamicCast(FindWindowByName(buttonName), wxButton);

    if (button) {
        wxColour backgroundColor(200, 200, 200);  // Kolor t³a
        wxColour textColor(55, 55, 55);            // Kolor tekstu

        button->SetBackgroundColour(backgroundColor);
        button->SetForegroundColour(textColor);
        button->Enable(false);
    }
}

void MainPanel_Controller::OnMouseHover(wxMouseEvent& event) {
    OnCursorHover(event);

}

/*
Function adds labels of games and hire buttons to gamesPanel
@param std::vector<Game> gamesVector
*/
void MainPanel_Controller::UpdateGamesPanel(std::vector<Game> gamesVector)
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
        wxLogMessage("s");
        Game game = gamesVector[i];
        if (game.GetName().find(enteredText.Lower()) == std::string::npos && enteredText != "")
            continue;
        filteredVector.push_back(game);
    }


    gamesPanel = nullptr;
    int height = filteredVector.size() <= 3 ? 330 : filteredVector.size() * 80;
    gamesPanel = new wxScrolledWindow(parentEl, wxID_ANY, wxPoint(0, 150), wxSize(GetClientSize().GetWidth(), 330));
    gamesPanel->SetScrollRate(0, 10);  // Ustawienia przewijania - drugi argument to liczba pikseli na jedno przewiniêcie
    //gamesPanel->Hide();
    gamesPanel->SetBackgroundColour(RED); // Set background color (optional)
    gamesPanel->SetVirtualSize(wxSize(410, height));




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
        int nrOfLoans = game.GetNrOfLoans();
        //int x = rand() % (100); // Losowa pozycja x na panelu
        //int y = rand() % (200); // Losowa pozycja y na panelu

        //Creating elements inside gamesPanel
        wxString labelText0 = wxString::Format("Nazwa gry: %s", gameName);
        wxString labelText1 = wxString::Format("Iloœæ dostêpnych sztuk: %d", gameQuantity);
        wxString labelText2 = wxString::Format("Ca³kowita iloœæ wypo¿yczeñ: %d", nrOfLoans);
        // (label name is the same as game name + Lbl)
        wxStaticText* gameLabel0 = new wxStaticText(gamesPanel, wxID_ANY, labelText0, wxPoint(10, 10 + i * 80), wxDefaultSize, 0, gameName + "Lbl0");
        wxStaticText* gameLabel1 = new wxStaticText(gamesPanel, wxID_ANY, labelText1, wxPoint(10, 30 + i * 80), wxDefaultSize, 0, gameName + "Lbl1");
        wxStaticText* gameLabel2 = new wxStaticText(gamesPanel, wxID_ANY, labelText2, wxPoint(10, 50 + i * 80), wxDefaultSize, 0, gameName + "Lbl2");

        gameLabel0->SetForegroundColour(COLOR_LBL);
        gameLabel0->SetFont(SetTheFont());
        gameLabel1->SetForegroundColour(COLOR_LBL);
        gameLabel1->SetFont(SetTheFont());
        gameLabel2->SetForegroundColour(COLOR_LBL);
        gameLabel2->SetFont(SetTheFont());


        //wxStaticText* gameLabel = new wxStaticText(gamesPanel, wxID_ANY, labelText, wxPoint(x, y));

        std::string buttonText = "Wypo¿ycz";

        // (button name is the same as game name)
        wxButton* hireBtn = new wxButton(gamesPanel, wxID_ANY, buttonText, wxPoint(GetClientSize().GetWidth() - 10 - 85, 10 + i * 85), wxSize(85, 35), 0, wxDefaultValidator, gameName);

        hireBtn->SetBackgroundColour(COLOR_BACKGROUND_BTN);
        hireBtn->SetForegroundColour(COLOR_TEXT_BTN);

        hireBtn->Bind(wxEVT_BUTTON, &MainPanel_Controller::UpdateGame, this, wxID_ANY, wxID_ANY);
        hireBtn->Bind(wxEVT_ENTER_WINDOW, &MainPanel_Controller::OnMouseHover, this);
        hireBtn->SetFont(SetTheFont());


        if (gameQuantity == 0)
            MainPanel_Controller::disableButton(gameName);

    //    /* else
    //         hireBtn->Enable(true);*/


    }
    gamesPanel->Show();
}

//This metohod executes after clicking on "wypozycz" button
void MainPanel_Controller::UpdateGame(wxCommandEvent& event)
{
    bool logged = UserCRUD::isLogged();

    if (!logged) {
        wxDialog* dialog = new wxDialog(this, wxID_ANY, "Musisz siê najpierw zalogowaæ, aby móc wypo¿yczyæ grê");
        dialog->ShowModal();
        dialog->Destroy();
        return;
    }

    //get the clicked button name
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    wxString buttonName = button->GetName();

    //wxLogMessage("Type of log: %s", user->getLogin());

    if (user && !user->addUserGame(buttonName.ToStdString())) {
        wxDialog* dialog = new wxDialog(this, wxID_ANY, "Przekroczono maksymaln¹ iloœæ gier wypo¿yczonych na raz. Aby wypo¿yczyæ now¹ grê zostañ cz³onkiem premium lub oddaj któr¹œ z ju¿ wypo¿yczonych gier.");
        dialog->ShowModal();
        dialog->Destroy();
        return;
    }

    //std::string log = user.stringifyGames();
    //wxLogMessage("Type of log: %s", log);

    gamesVector = MainPanel_Controller::updateGame(buttonName, gamesPanel, gamesVector);
}

//This functions executes when choosing sorting method (A-Z or Z-A)
void MainPanel_Controller::OnChoice(wxCommandEvent& event) {
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

void MainPanel_Controller::OnResetButtonClick(wxCommandEvent& event) {
    //if input is already empty, dont't rerender gamesPanel

    if (searchInput->GetValue() == "")
        return;

    searchInput->SetValue("");  // set empty string to the input
    OnSearchChange(event);
    event.Skip();
}