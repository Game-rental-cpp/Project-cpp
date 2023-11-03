// MainFrame.cpp
#include "MainFrame.h"
#include<fstream>
#include <filesystem>

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    // Tworzenie przycisków
    goBackBtn = new wxButton(this, wxID_ANY, "Wróæ");
    loginBtn = new wxButton(this, wxID_ANY, "Zaloguj / Zarejestruj");
    myAccBtn = new wxButton(this, wxID_ANY, "Moje konto");

    //Pokazuj odpowiednie przyciski w zale¿noœci czy user jest zalogowany czy nie
    goBackBtn->Hide();
    if (IsLogged())
        loginBtn->Hide();
    else myAccBtn->Hide();

    // Tworzenie i dodawanie MainPanel
    mainPanel = new MainPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(410, 300));
    loginPanel = new LoginPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(410, 300));
    myAccPanel = new MyAccPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(410, 300));

    //Dpmyœlnie ukryte
    loginPanel->Hide();
    myAccPanel->Hide();

    // Przypisanie funkcji obs³ugi zdarzeñ do przycisków
    goBackBtn->Bind(wxEVT_BUTTON, &MainFrame::OnGoBack, this);
    loginBtn->Bind(wxEVT_BUTTON, &MainFrame::OnLogin, this);
    myAccBtn->Bind(wxEVT_BUTTON, &MainFrame::OnMyAcc, this);



    //mainPanel->SetWindowStyleFlag(wxALIGN_CENTER_HORIZONTAL);

    //// style
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Odstêp 10 pikseli od górnej krawêdzi
    sizer->AddSpacer(10);

    // wyœrodkowanie w poziomie
    sizer->Add(goBackBtn, 0, wxALIGN_CENTER_HORIZONTAL);
    sizer->Add(loginBtn, 0, wxALIGN_CENTER_HORIZONTAL);
    sizer->Add(myAccBtn, 0, wxALIGN_CENTER_HORIZONTAL);

    sizer->AddSpacer(20);

    sizer->Add(mainPanel, 0, wxALIGN_CENTER_HORIZONTAL);
    sizer->Add(loginPanel, 0, wxALIGN_CENTER_HORIZONTAL);
    sizer->Add(myAccPanel, 0, wxALIGN_CENTER_HORIZONTAL);

    // Przypisanie sizeru do ramki
    this->SetSizer(sizer);
}


// Funkcja obs³ugi zdarzenia po naciœniêciu przycisku "Wróæ"
void MainFrame::OnGoBack(wxCommandEvent & event)
{
    goBackBtn->Hide();
    //
    if (IsLogged()) {
        loginBtn->Hide();
        myAccBtn->Show();
    } else {
        loginBtn->Show();
        myAccBtn->Hide();
    }

    //pokazywanie / ukrywanie panelów
    mainPanel->Show();
    loginPanel->Hide();
    myAccPanel->Hide();

    // Przerysuj okno, aby zastosowaæ zmiany widoku
    this->Layout();

    //Poni¿sza funkcja jest zdefiniowana w osobnym pliku, aby zapewniæ przejrzystoœæ kodu.
    mvcShowcase();
}

// Funkcja obs³ugi zdarzenia po naciœniêciu przycisku "Zaloguj / zarejestruj"
void MainFrame::OnLogin(wxCommandEvent& event)
{
    goBackBtn->Show();
    loginBtn->Hide();
    myAccBtn->Hide();

    loginPanel->Show();
    myAccPanel->Hide();
    mainPanel->Hide();
 
    this->Layout();
}

// Funkcja obs³ugi zdarzenia po naciœniêciu przycisku "Moje konto"
void MainFrame::OnMyAcc(wxCommandEvent& event)
{
    goBackBtn->Show();
    loginBtn->Hide();
    myAccBtn->Hide();

    myAccPanel->Show();
    loginPanel->Hide();
    mainPanel->Hide();

    this->Layout();

}


bool MainFrame::IsLogged() const {
    // Pobieramy œcie¿kê do pliku MainFrame.cpp
        wxString parentDir = wxGetCwd();

    // £¹czymy œcie¿kê do katalogu "Users"
    wxString loggedFile = parentDir + "/Users/_logged.txt";

    // SprawdŸ, czy plik istnieje
    if (wxFileExists(loggedFile)) {
        // Otwórz plik do odczytu
        wxFile file(loggedFile, wxFile::read);

        //int l = file.Length();
        //std::string ll = std::to_string(l);
        //wxLogMessage("%s", ll.c_str());
        int len = file.Length();
        file.Close();

        // SprawdŸ, czy plik jest pusty
        if (len == 0)
            return false; // Plik jest pusty, wiêc u¿ytkownik nie jest zalogowany
        else return true; //Plik nie jest pusty, u¿ytkownik jest zalogowany
        
    }

    return false; // Plik nie istnieje
}
