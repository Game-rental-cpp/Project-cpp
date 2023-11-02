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

    // Przypisanie funkcji obs³ugi zdarzenia wxShowEvent
    Bind(wxEVT_SHOW, &MainPanel::OnPanelShow, this);

    // Tutaj wywo³ujemy funkcjê do wczytywania gier na podstawie plików
    LoadGamesFromFiles();
}

void MainPanel::OnPanelShow(wxShowEvent& event)
{
    if (event.IsShown()) {
        // Panel zosta³ pokazany na ekranie
        LoadGamesFromFiles();
    }
    else {
        // Panel zosta³ ukryty
    }
    event.Skip();
}

void MainPanel::LoadGamesFromFiles()
{
    // Tworzymy wektor na obiekty gier
    std::vector<Game> games;

    // Pobieramy œcie¿kê do bie¿¹cego katalogu, w którym znajduje siê wykonywalny plik aplikacji
    wxString parentDir = wxGetCwd();

    // £¹czymy œcie¿kê do katalogu "Games"
    wxString gamesDir = parentDir + "/Games";

    // Liczymy iloœæ plików w katalogu "Games"
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

    // Konwertujemy fileCount na string i aktualizujemy etykietê
    wxString fileCountStr = wxString::Format("%d", fileCount);
    label->SetLabel("Liczba plików w folderze: " + fileCountStr);
    // fileCount to teraz liczba plików w folderze "Games" znajduj¹cym siê na tym samym poziomie co Twoja aplikacja
}
