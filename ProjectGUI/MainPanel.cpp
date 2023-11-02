// MainPanel.cpp
#include "MainPanel.h"
#include <wx/dir.h>
#include <string>

MainPanel::MainPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    // Tworzenie przycisku
    button = new wxButton(this, wxID_ANY, "Przycisk w MainPanel", wxPoint(10, 10));

    // Tworzenie etykiety
    label = new wxStaticText(this, wxID_ANY, "To jest etykieta w MainPanel", wxPoint(10, 50));

    // Przypisanie funkcji obs�ugi zdarzenia wxShowEvent
    Bind(wxEVT_SHOW, &MainPanel::OnPanelShow, this);

    LoadGames();

}

void MainPanel::OnPanelShow(wxShowEvent& event)
{
    if (event.IsShown()) {
        // Panel zosta� pokazany na ekranie
        LoadGames();

    }
    else {
        // Panel zosta� ukryty
    }
    event.Skip();
}

void MainPanel::LoadGames()
{

    // Tworzymy wektor na obiekty gier
    //std::vector<Game> games;

    int n = CountGames();

    for (int i = 0; i < n; i++) {
        // Tworzenie nowej gry na podstawie pliku i dodawanie jej do wektora
        Game game = CreateGameBasedOnFile(i);


        // Pobierz nazw� i liczb� sztuk
        wxString gameNameWx = game.GetName();
        std::string gameName = std::string(gameNameWx.ToStdString());
        int gameQuantity = game.GetQuantity();

        int x = rand() % (100); // Losowa pozycja x na panelu
        int y = rand() % (200); // Losowa pozycja y na panelu

        // Tworzenie etykiety z nazw� i ilo�ci� gier
        wxString labelText = wxString::Format("Nazwa gry: %s, ilo�� sztuk: %d", gameName, gameQuantity);
        wxStaticText* gameLabel = new wxStaticText(this, wxID_ANY, labelText, wxPoint(x, y));
        //wxStaticText* gameLabel = new wxStaticText(this, wxID_ANY, labelText, wxPoint(10, 70 + i * 20));
        // Mo�esz dostosowa� pozycj� i inne w�a�ciwo�ci etykiety, je�li to konieczne
    }

    // Konwertujemy fileCount na string i aktualizujemy etykiet�
    wxString fileCountStr = wxString::Format("%d", n);
    label->SetLabel("Liczba r�nych gier: " + fileCountStr);
}


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
            wxString fileContents;
            //pobierz zawarto�� pliku
            for (size_t lineIdx = 0; lineIdx < file.GetLineCount(); ++lineIdx) {
                fileContents += file.GetLine(lineIdx);
                fileContents += "\n";
            }

            // Rozbij zawarto�� pliku na linie
            wxArrayString lines = wxSplit(fileContents, '\n');

            for (const wxString& line : lines) {
                wxArrayString parts = wxSplit(line, ':');
                if (parts.GetCount() == 2) {
                    wxString key = parts[0].Strip(wxString::both);
                    wxString value = parts[1].Strip(wxString::both);

                    if (key == "name") {
                        name = value.ToStdString();
                    }
                    else if (key == "quantity") {
                        value.ToInt(&quantity);
                    }
                }
            }

            file.Close();
        }
    }

    Game game(name, quantity);

    return game;
}



int MainPanel::CountGames() {
    // Pobieramy �cie�k� do pliku MainPanel.cpp
    wxString parentDir = wxGetCwd();

    // ��czymy �cie�k� do katalogu "Games"
    wxString gamesDir = parentDir + "/Games";

    // Liczymy ilo�� plik�w w katalogu "Games"
    int fileCount = 0;
    wxDir dir(gamesDir);
    if (dir.IsOpened()) {
        wxString filename;
        bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
        while (cont) {
            fileCount++;
            cont = dir.GetNext(&filename);
        }
    }
    return fileCount;
}