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
    // Dodanie gamesPanel do ramki i ustawienie, �e ma zajmowa� ca�� dost�pn� szeroko��
    //gamesSizer->Add(gamesPanel, 1, wxEXPAND | wxALL | wxALIGN_CENTER, 10);

    // Przypisanie funkcji obs�ugi zdarzenia wxShowEvent
    Bind(wxEVT_SHOW, &MainPanel::OnPanelShow, this);

    LoadGames();

}

void MainPanel::OnPanelShow(wxShowEvent& event)
{
     //Wykonaj je�li MainPanel zosta� pokazany na ekranie
    if (event.IsShown()) {

        // Usu� istniej�cy gamesPanel, je�li istnieje
        if (gamesPanel) {
            gamesPanel->Destroy();
            gamesPanel = nullptr;
            gamesVector.clear();
            buttonLabelMap.clear();
        }

        // Tw�rz nowy gamesPanel
        gamesPanel = new wxPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(400, 300));
        gamesPanel->SetBackgroundColour(wxColour(255, 0, 0)); // Ustaw kolor t�a (opcjonalnie)

        LoadGames();
        Layout(); // Zaktualizuj uk�ad

    }

    event.Skip();
}

void MainPanel::UpdateGame(wxCommandEvent& event)
{
    // Pobierz obiekt przycisku, kt�ry zosta� naci�ni�ty
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());

    // Sprawd�, czy uda�o si� pobra� obiekt przycisku
    if (button) {
        // Sprawd�, czy istnieje etykieta odpowiadaj�ca temu przyciskowi w mapie
        if (buttonLabelMap.find(button) != buttonLabelMap.end()) {
            // Pobierz etykiet� odpowiadaj�c� przyciskowi
            wxStaticText* label = buttonLabelMap[button];

            // Pobierz aktualn� warto�� etykiety
            wxString labelText = label->GetLabel();

            // Pobierz liczb� z tekstu etykiety
            int quantity;
            labelText.AfterLast(' ').ToInt(&quantity);

            // Pobierz nazw� gry z tekstu etykiety
            wxString gameName = labelText.BeforeFirst(',').substr(11);
 
            //W p�tli jest aktualizowany odpowiedni obiekt Game z wektora, a nast�pnie na tej podstawie aktuazlizowany jest laebl
            for (int i = 0; i < gamesVector.size(); i++) {

                if ( gamesVector[i].GetName() == gameName) {

                    //wxLogMessage(wxString(gamesVector[i].GetName().c_str()));
                    //jeszcze setQuantity powinno aktualiziowa� pliki txt
                    gamesVector[i].SetQuantity(gamesVector[i].GetQuantity()-1);

                    wxString newLabelText = labelText.BeforeLast(' ') + wxString::Format(" %ld", gamesVector[i].GetQuantity());
                    label->SetLabel(newLabelText);
                    break; // Znaleziono gr�, przerywamy p�tl�
                }
               
            }


            label->Refresh();
        }
    }

}

//Funkcja dodaje do gamesPanel labele z grami i przyciski do wypo�yczenia
void MainPanel::LoadGames()
{
    //liczba gier
    int n = GameCRUD::countGames();

    for (int i = 0; i < n; i++) {
        // Tworzenie nowej gry na podstawie pliku i dodawanie jej do wektora
        Game game = CreateGameBasedOnFile(i);

        gamesVector.push_back(game); // Dodawanie gry do wektora


        // Pobierz nazw� i liczb� sztuk
        wxString gameNameWx = game.GetName();
        std::string gameName = std::string(gameNameWx.ToStdString());
        int gameQuantity = game.GetQuantity();

        //int x = rand() % (100); // Losowa pozycja x na panelu
        //int y = rand() % (200); // Losowa pozycja y na panelu

        wxString labelText = wxString::Format("Nazwa gry: %s, ilo�� sztuk: %d", gameName, gameQuantity);
        wxStaticText* gameLabel = new wxStaticText(gamesPanel, wxID_ANY, labelText, wxPoint(10, 70 + i * 20));
        //wxStaticText* gameLabel = new wxStaticText(gamesPanel, wxID_ANY, labelText, wxPoint(x, y));
        wxButton* hireBtn = new wxButton(gamesPanel, wxID_ANY, "Wypo�ycz", wxPoint(250, 70+ i* 20));
        hireBtn->Bind(wxEVT_BUTTON, &MainPanel::UpdateGame, this, wxID_ANY, wxID_ANY);

        // Dodaj przycisk i etykiet� do kontenera
        buttonLabelMap[hireBtn] = gameLabel;

        // Mo�esz dostosowa� pozycj� i inne w�a�ciwo�ci etykiety, je�li to konieczne
    }

    // Konwertujemy fileCount na string i aktualizujemy etykiet�
    wxString fileCountStr = wxString::Format("%d", n);
    label->SetLabel("Liczba r�nych gier: " + fileCountStr);
}

//Ta funkcja tworzy obiekt typu Game na podstawie plik�w json
Game MainPanel::CreateGameBasedOnFile(int i)
{
    std::string name;
    int quantity;

    wxString parentDir = wxGetCwd();
    wxString gamesDir = parentDir + "/Games";

    wxArrayString files;
    wxDir::GetAllFiles(gamesDir, &files, wxEmptyString, wxDIR_FILES);

    if (i >= 0 && i < files.GetCount()) {
        wxString filePath = files[i];
        wxTextFile file(filePath);

        if (file.Exists() && file.Open()) {
            wxString fileName = wxFileNameFromPath(filePath);
            //cut the .json extension from the name
            std::string truncatedFileName = fileName.ToStdString().substr(0, fileName.length() - 5);

            wxString fileContents = GameCRUD::readGame(truncatedFileName);

            json jsonData = json::parse(fileContents);

            name = jsonData["name"];
            quantity = jsonData["quantity"];
  
            file.Close();
        }
    }

    Game game(name, quantity);

    return game;
}

