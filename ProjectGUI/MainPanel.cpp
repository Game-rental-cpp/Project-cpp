// MainPanel.cpp
#include "MainPanel.h"
#include <wx/dir.h>
#include <string>
#include <vector>

using json = nlohmann::json;

std::vector<Game> gamesVector; 
std::vector<Game> helpGamesVector;

//How many different games
int gameCount = GameCRUD::countGames();

MainPanel::MainPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    // Creating a button
    button = new wxButton(this, wxID_ANY, "Przycisk w MainPanel", wxPoint(10, 10));

    //Convert gameCount into string
    wxString gameCountStr = wxString::Format("%d", gameCount);
    // Creating a label
    label = new wxStaticText(this, wxID_ANY, "Liczba ró¿nych gier: " + gameCountStr, wxPoint(10, 50));

    wxArrayString sortOptions;
    sortOptions.Add("Alfabetycznie (A-Z)");
    sortOptions.Add("Alfabetycznie (Z-A)");
    
    sortChoice= new wxChoice(this, wxID_ANY, wxPoint(10, 75), wxSize(130, -1), sortOptions);
    sortChoice->SetSelection(0);

    // Dodaj zdarzenie EVT_CHOICE do kontrolki wxChoice
    sortChoice->Bind(wxEVT_CHOICE, &MainPanel::OnChoice, this);

    gamesVector= MainPanel_Logic::fulfillGamesVector(gameCount);

    // Creating the gamesPanel
    gamesPanel = new wxPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(400, 300));

    // Przypisanie funkcji obs³ugi zdarzenia wxShowEvent
    Bind(wxEVT_SHOW, &MainPanel::OnPanelShow, this);
}


//
void MainPanel::OnChoice(wxCommandEvent& event) {
    int selection = sortChoice->GetSelection();
    wxString selectedOption = sortChoice->GetString(selection);

    // Sortowanie obiektów w gamesVector wed³ug pola name
    gamesVector[0].GetName();

    switch (selection) {
    case 0: 
        //sprto A-Z
        for (int i = 0; i < gameCount - 1; i++) {
            for (int j = 0; j < gameCount - i - 1; j++) {
                if (gamesVector[j].GetName() > gamesVector[j + 1].GetName()) {
                    // Zamieñ miejscami, jeœli warunek nie jest spe³niony
                    std::swap(gamesVector[j], gamesVector[j + 1]);
                }
            }
        }

        break;
    case 1: 
        //sort Z-A
        for (int i = 0; i < gameCount - 1; i++) {
            for (int j = 0; j < gameCount - i - 1; j++) {
                if (gamesVector[j].GetName() < gamesVector[j + 1].GetName()) {
                    // Zamieñ miejscami, jeœli warunek nie jest spe³niony
                    std::swap(gamesVector[j], gamesVector[j + 1]);
                }
            }
        }
        break;
    }

    if (gamesPanel) {
        UpdateGamesPanel(gamesVector);
    }

}

void MainPanel::OnPanelShow(wxShowEvent& event)
{
     //Do if MainPanel has occured on the screen
    if (event.IsShown()) {
        //wxLogMessage(gamesVector[0].GetName().c_str());
                // Delete existing gamesPanel if it already exists
        if (gamesPanel) {
            UpdateGamesPanel(gamesVector);
        }

    }

    event.Skip();
}


//This metohods executes after clicking on "wypozycz" button
void MainPanel::UpdateGame(wxCommandEvent& event)
{
    // Pobierz obiekt przycisku, który zosta³ naciœniêty
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());


    // SprawdŸ, czy uda³o siê pobraæ obiekt przycisku
    if (button) {
        //take the unique name of the clicked button
        wxString buttonName = button->GetName();
        //wxLogMessage(buttonName);

        //Search for the corresponding label for the clicked button
        wxStaticText* correspondingLabel = wxDynamicCast(gamesPanel->FindWindowByName(buttonName+"Lbl"), wxStaticText);
        
        // Pobierz aktualn¹ wartoœæ etykiety
        wxString labelText = correspondingLabel->GetLabel();
        
        // Pobierz liczbê z tekstu etykiety
        int quantity;
        labelText.AfterLast(' ').ToInt(&quantity);
        
        //W pêtli jest aktualizowany odpowiedni obiekt Game z wektora, a nastêpnie na tej podstawie aktuazlizowany jest laebl
        for (int i = 0; i < gamesVector.size(); i++) {
        
            if ( gamesVector[i].GetName() == buttonName) {
        
                //wxLogMessage(wxString(gamesVector[i].GetName().c_str()));
                gamesVector[i].SetQuantity(gamesVector[i].GetQuantity()-1);
        
                wxString newLabelText = labelText.BeforeLast(' ') + wxString::Format(" %ld", gamesVector[i].GetQuantity());
                correspondingLabel->SetLabel(newLabelText);

                if(gamesVector[i].GetQuantity()== 0)
                    button->Enable(false);

                break; // Znaleziono grê, przerywamy pêtlê
            }
           
        }

            correspondingLabel->Refresh();  
    }

}


//Funkcja dodaje do gamesPanel labele z grami i przyciski do wypo¿yczenia
void MainPanel::UpdateGamesPanel(std::vector<Game> gamesVector)
{
    gamesPanel->Destroy();
    gamesPanel = nullptr;
    // Create new gamesPanel
    gamesPanel = new wxPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(400, 300));
    gamesPanel->SetBackgroundColour(wxColour(255, 0, 0)); // Set background color (optional)
        //Game game1= gamesVector[0];
    for (int i = 0; i < gameCount; i++) {

        // Tworzenie nowej gry na podstawie pliku i dodawanie jej do wektora
        //Game game = MainPanel_Logic::CreateGameFromJSON(i);

        //gamesVector.push_back(game); // Dodawanie gry do wektora



        //Game game = gamesVector[i];
        //wxLogMessage(gamesVector[i].GetName().c_str());
        Game game = gamesVector[i];
        // 
        // 
        // Pobierz nazwê i liczbê sztuk
        //wxString gameNameWx = game.GetName();
        std::string gameName = std::string(game.GetName());
        int gameQuantity = game.GetQuantity();

        //int x = rand() % (100); // Losowa pozycja x na panelu
        //int y = rand() % (200); // Losowa pozycja y na panelu

        //Creating elements inside gamesPanel
        wxString labelText = wxString::Format("Nazwa gry: %s, iloœæ sztuk: %d", gameName, gameQuantity);
        wxStaticText* gameLabel = new wxStaticText(gamesPanel, wxID_ANY, labelText, wxPoint(10, 70 + i * 20), wxDefaultSize, 0, gameName + "Lbl");
        //wxStaticText* gameLabel = new wxStaticText(gamesPanel, wxID_ANY, labelText, wxPoint(x, y));
        
        wxButton* hireBtn = new wxButton(gamesPanel, wxID_ANY, "Wypo¿ycz", wxPoint(250, 70+ i* 20), wxDefaultSize,0, wxDefaultValidator,gameName);
        hireBtn->Bind(wxEVT_BUTTON, &MainPanel::UpdateGame, this, wxID_ANY, wxID_ANY);

        if (gameQuantity == 0)
            hireBtn->Enable(false);
       /* else
            hireBtn->Enable(true);*/


    }


}



