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

    // Tutaj wywo�ujemy funkcj� do wczytywania gier na podstawie plik�w
    LoadGamesFromFiles();
}

void MainPanel::OnPanelShow(wxShowEvent& event)
{
    if (event.IsShown()) {
        // Panel zosta� pokazany na ekranie
        LoadGamesFromFiles();
    }
    else {
        // Panel zosta� ukryty
    }
    event.Skip();
}

void MainPanel::LoadGamesFromFiles()
{
    // Tworzymy wektor na obiekty gier
    std::vector<Game> games;

    // Pobieramy �cie�k� do bie��cego katalogu, w kt�rym znajduje si� wykonywalny plik aplikacji
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

    // Konwertujemy fileCount na string i aktualizujemy etykiet�
    wxString fileCountStr = wxString::Format("%d", fileCount);
    label->SetLabel("Liczba plik�w w folderze: " + fileCountStr);
    // fileCount to teraz liczba plik�w w folderze "Games" znajduj�cym si� na tym samym poziomie co Twoja aplikacja
}
