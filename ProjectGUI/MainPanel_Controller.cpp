#include "MainPanel_Controller.h"
#include "MainPanel_Logic.h"
#include "MainPanel.h"
#include "Style.h"
#include "UserCRUD.h"
#include "UserNormal.h"
#include "UserPremium.h"
#include "Log.h"

int gameCount = GameCRUD::countGames();

MainPanel_Controller::MainPanel_Controller(MainPanel* parentEl, wxTextCtrl* searchInput, wxButton* resetBtn, wxChoice* sortChoice)
    : parentEl(parentEl), searchInput(searchInput), resetBtn(resetBtn), sortChoice(sortChoice), gamesPanel(gamesPanel),
    gamesVector(MainPanel_Logic::fulfillGamesVector(gameCount)) {
}


void MainPanel_Controller::BindEvents() {

    searchInput->Connect(wxEVT_TEXT, wxCommandEventHandler(MainPanel_Controller::OnSearchChange), nullptr, this);
    sortChoice->Bind(wxEVT_CHOICE, &MainPanel_Controller::OnChoice, this);
    resetBtn->Bind(wxEVT_BUTTON, &MainPanel_Controller::OnResetButtonClick, this, wxID_ANY, wxID_ANY);
    resetBtn->Bind(wxEVT_ENTER_WINDOW, &MainPanel_Controller::OnMouseHover, this);
    sortChoice->Bind(wxEVT_ENTER_WINDOW, &MainPanel_Controller::OnMouseHover, this);
    parentEl->Bind(wxEVT_SHOW, &MainPanel_Controller::OnShowPanel, this);

}

void MainPanel_Controller::OnShowPanel(wxShowEvent& event) {

    //Execute if MainPanel has occured on the screen
    if (event.IsShown()) {
        parentEl->SetBackgroundColour(COLOR_BACKGROUND_PANEL); // Set background color (optional)
        searchInput->SetFocus();
        gamesVector = MainPanel_Logic::fulfillGamesVector(gameCount);
        UpdateGamesPanel(gamesVector);
    }

    event.Skip();
}



//This metohod executes after clicking on "wypozycz" button
void MainPanel_Controller::UpdateGame(wxCommandEvent& event)
{
    bool logged = UserCRUD::isLogged();
    if (!logged) {
        wxMessageDialog* signupNameErrorDlg = new wxMessageDialog(parentEl, L"Aby wypożyczyć grę najpierw musisz się zalogować", "Informacja");
        signupNameErrorDlg->ShowModal();
        return;
    }


    //get the clicked button name
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    wxString buttonName = button->GetName();

    User* user = MainPanel_Logic::createUser();

    if (!user->addUserGame(buttonName.ToStdString())) {
        wxMessageDialog* signupNameErrorDlg = new wxMessageDialog(parentEl, L"Przekroczono maksymalną ilość gier wypożyczonych na raz. Aby wypożyczyć nową grę zostań członkiem premium lub oddaj którąś z już wypożyczonych gier.", "Informacja");
        signupNameErrorDlg->ShowModal();

        return;
    }

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
            // Update performance log
            writeToLog(user->getLogin() + " wypozyczyl/a gre " + gamesVector[i].GetName() + ".  Liczba dostepnych do wypozyczania kopii gry wynosi: "
                + std::to_string(gamesVector[i].GetQuantity()));

            break; // The game has been found, break the loop
        }

    }

    correspondingLabel1->Refresh();
}





void MainPanel_Controller::OnSearchChange(wxCommandEvent& event) {
    UpdateGamesPanel(gamesVector);
    event.Skip();
}

void MainPanel_Controller::disableButton(const wxString& buttonName) {
    // Find the button based on its name.
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
Function adds labels of games and hire buttons to gamesPanel view
@param std::vector<Game> gamesVector
*/
void MainPanel_Controller::UpdateGamesPanel(std::vector<Game> gamesVector)
{

    if (gamesPanel) {
        gamesPanel->Hide();
        gamesPanel->Destroy();
    }

    //this vector contains all games that should appear on screen (except those that shouldn't)
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
    int height = filteredVector.size() <= 3 ? 330 : filteredVector.size() * 85;
    gamesPanel = new wxScrolledWindow(parentEl, wxID_ANY, wxPoint(0, 120), wxSize(parentEl->GetSize().GetWidth(), 380));
    gamesPanel->SetScrollRate(0, 10);
    gamesPanel->SetBackgroundColour(COLOR_BACKGROUND_PANEL); // Set background color (optional)
    gamesPanel->SetVirtualSize(wxSize(410, height));



    if (filteredVector.size() == 0) {
        wxStaticText* noGameLabel = new wxStaticText(gamesPanel, wxID_ANY, L"Żadna z gier nie spełnia warunków wyszukiwania", wxPoint(21, 150), wxDefaultSize);
        noGameLabel->SetForegroundColour(COLOR_LBL);
        noGameLabel->SetFont(SetTheFont(12, true));
    }


    for (int i = 0; i < filteredVector.size(); i++) {

        Game game = filteredVector[i];

        std::string gameName = std::string(game.GetName());
        int gameQuantity = game.GetQuantity();
        int nrOfLoans = game.GetNrOfLoans();
        float rate = game.GetRate();

        //Creating elements inside gamesPanel
        wxString gameNameLabelText = wxString::Format("%s", gameName);
        wxString quantityLabelText = wxString::Format(L"Ilość dostępnych sztuk: %d", gameQuantity);
        wxString nrOfLoansLabelText = wxString::Format(L"Całkowita ilość wypożyczeń: %d", nrOfLoans);
        wxString rateLabelText = wxString::Format("ocena: %.2f/5", rate);
        // (label name is the same as game name + Lbl)
        wxStaticText* gameNameLabel = new wxStaticText(gamesPanel, wxID_ANY, gameNameLabelText, wxPoint(50, 12 + i * 80), wxDefaultSize, 0, gameName + "Lbl0");
        wxStaticText* quantityLabel = new wxStaticText(gamesPanel, wxID_ANY, quantityLabelText, wxPoint(50, 40 + i * 80), wxDefaultSize, 0, gameName + "Lbl1");
        wxStaticText* nrOfLoansLabel = new wxStaticText(gamesPanel, wxID_ANY, nrOfLoansLabelText, wxPoint(50, 60 + i * 80), wxDefaultSize, 0, gameName + "Lbl2");
        wxStaticText* rateLabel = new wxStaticText(gamesPanel, wxID_ANY, rateLabelText, wxPoint(145, 15 + i * 80), wxDefaultSize, 0, gameName + "Lbl3");

        gameNameLabel->SetForegroundColour(COLOR_LBL);
        gameNameLabel->SetFont(SetTheFont(14, true));
        quantityLabel->SetForegroundColour(COLOR_LBL);
        quantityLabel->SetFont(SetTheFont());
        nrOfLoansLabel->SetForegroundColour(COLOR_LBL);
        nrOfLoansLabel->SetFont(SetTheFont());
        rateLabel->SetForegroundColour(COLOR_LBL);
        rateLabel->SetFont(SetTheFont(13));



        // (button name is the same as game name)
        wxButton* hireBtn = new wxButton(gamesPanel, wxID_ANY, L"Wypożycz", wxPoint(parentEl->GetSize().GetWidth() - 10 - 150, 10 + i * 80), wxSize(85, 35), 0, wxDefaultValidator, gameName);

        hireBtn->SetBackgroundColour(COLOR_BACKGROUND_BTN);
        hireBtn->SetForegroundColour(COLOR_TEXT_BTN);

        hireBtn->Bind(wxEVT_BUTTON, &MainPanel_Controller::UpdateGame, this, wxID_ANY, wxID_ANY);
        hireBtn->Bind(wxEVT_ENTER_WINDOW, &MainPanel_Controller::OnMouseHover, this);
        hireBtn->SetFont(SetTheFont());


        if (gameQuantity == 0)
            MainPanel_Controller::disableButton(gameName);


    }
    gamesPanel->Show();
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