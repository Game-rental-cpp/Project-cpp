// MainPanel.cpp
#include "MainPanel.h"
#include <wx/dir.h>
#include <string>
#include <map>
#include <vector>

using json = nlohmann::json;

std::map<wxButton*, wxStaticText*> buttonLabelMap;
std::vector<Game> gamesVector; 


MainPanel::MainPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    // Tworzenie przycisku
    button = new wxButton(this, wxID_ANY, "Przycisk w MainPanel", wxPoint(10, 10));

    // Tworzenie etykiety
    label = new wxStaticText(this, wxID_ANY, "To jest etykieta w MainPanel", wxPoint(10, 50));

    // Tworzenie panelu booksPanel
    gamesPanel = new wxPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(400, 300));
    gamesPanel->SetBackgroundColour(wxColour(255, 0, 0)); // Ustawiony na czerwony kolor (255, 0, 0)
    // Dodanie gamesPanel do ramki i ustawienie, ¿e ma zajmowaæ ca³¹ dostêpn¹ szerokoœæ
    //gamesSizer->Add(gamesPanel, 1, wxEXPAND | wxALL | wxALIGN_CENTER, 10);

    // Przypisanie funkcji obs³ugi zdarzenia wxShowEvent
    Bind(wxEVT_SHOW, &MainPanel::OnPanelShow, this);

    LoadGames();

}

void MainPanel::OnPanelShow(wxShowEvent& event)
{
     //Wykonaj jeœli MainPanel zosta³ pokazany na ekranie
    if (event.IsShown()) {

        // Usuñ istniej¹cy gamesPanel, jeœli istnieje
        if (gamesPanel) {
            gamesPanel->Destroy();
            gamesPanel = nullptr;
            gamesVector.clear();
            buttonLabelMap.clear();
        }

        // Twórz nowy gamesPanel
        gamesPanel = new wxPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(400, 300));
        gamesPanel->SetBackgroundColour(wxColour(255, 0, 0)); // Ustaw kolor t³a (opcjonalnie)

        LoadGames();
        Layout(); // Zaktualizuj uk³ad

    }

    event.Skip();
}

void MainPanel::UpdateGame(wxCommandEvent& event)
{
    // Pobierz obiekt przycisku, który zosta³ naciœniêty
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());

    // SprawdŸ, czy uda³o siê pobraæ obiekt przycisku
    if (button) {
        // SprawdŸ, czy istnieje etykieta odpowiadaj¹ca temu przyciskowi w mapie
        if (buttonLabelMap.find(button) != buttonLabelMap.end()) {
            // Pobierz etykietê odpowiadaj¹c¹ przyciskowi
            wxStaticText* label = buttonLabelMap[button];

            // Pobierz aktualn¹ wartoœæ etykiety
            wxString labelText = label->GetLabel();

            // Pobierz liczbê z tekstu etykiety
            int quantity;
            labelText.AfterLast(' ').ToInt(&quantity);

            // Pobierz nazwê gry z tekstu etykiety
            wxString gameName = labelText.BeforeFirst(',').substr(11);
 
            //W pêtli jest aktualizowany odpowiedni obiekt Game z wektora, a nastêpnie na tej podstawie aktuazlizowany jest laebl
            for (int i = 0; i < gamesVector.size(); i++) {

                if ( gamesVector[i].GetName() == gameName) {

                    //wxLogMessage(wxString(gamesVector[i].GetName().c_str()));
                    //jeszcze setQuantity powinno aktualiziowaæ pliki txt
                    gamesVector[i].SetQuantity(gamesVector[i].GetQuantity()-1);

                    wxString newLabelText = labelText.BeforeLast(' ') + wxString::Format(" %ld", gamesVector[i].GetQuantity());
                    label->SetLabel(newLabelText);
                    break; // Znaleziono grê, przerywamy pêtlê
                }
               
            }


            label->Refresh();
        }
    }

}

//Funkcja dodaje do gamesPanel labele z grami i przyciski do wypo¿yczenia
void MainPanel::LoadGames()
{
    //liczba gier
    int n = GameCRUD::countGames();

    for (int i = 0; i < n; i++) {
        // Tworzenie nowej gry na podstawie pliku i dodawanie jej do wektora
        Game game = MainPanel_Logic::CreateGameBasedOnFile(i);

        gamesVector.push_back(game); // Dodawanie gry do wektora


        // Pobierz nazwê i liczbê sztuk
        wxString gameNameWx = game.GetName();
        std::string gameName = std::string(gameNameWx.ToStdString());
        int gameQuantity = game.GetQuantity();

        //int x = rand() % (100); // Losowa pozycja x na panelu
        //int y = rand() % (200); // Losowa pozycja y na panelu

        wxString labelText = wxString::Format("Nazwa gry: %s, iloœæ sztuk: %d", gameName, gameQuantity);
        wxStaticText* gameLabel = new wxStaticText(gamesPanel, wxID_ANY, labelText, wxPoint(10, 70 + i * 20));
        //wxStaticText* gameLabel = new wxStaticText(gamesPanel, wxID_ANY, labelText, wxPoint(x, y));
        wxButton* hireBtn = new wxButton(gamesPanel, wxID_ANY, "Wypo¿ycz", wxPoint(250, 70+ i* 20));
        hireBtn->Bind(wxEVT_BUTTON, &MainPanel::UpdateGame, this, wxID_ANY, wxID_ANY);

        // Dodaj przycisk i etykietê do kontenera
        buttonLabelMap[hireBtn] = gameLabel;

        // Mo¿esz dostosowaæ pozycjê i inne w³aœciwoœci etykiety, jeœli to konieczne
    }

    // Konwertujemy fileCount na string i aktualizujemy etykietê
    wxString fileCountStr = wxString::Format("%d", n);
    label->SetLabel("Liczba ró¿nych gier: " + fileCountStr);
}



