// MainFrame.cpp
#include "MainFrame.h"
#include<fstream>
#include <filesystem>

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    // Tworzenie przycisk�w
    goBackBtn = new wxButton(this, wxID_ANY, "Wr��");
    loginBtn = new wxButton(this, wxID_ANY, "Zaloguj / Zarejestruj");
    myAccBtn = new wxButton(this, wxID_ANY, "Moje konto");

    //Pokazuj odpowiednie przyciski w zale�no�ci czy user jest zalogowany czy nie
    goBackBtn->Hide();
    if (IsLogged())
        loginBtn->Hide();
    else myAccBtn->Hide();

    // Tworzenie i dodawanie MainPanel
    mainPanel = new MainPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(410, 300));
    loginPanel = new LoginPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(410, 300));
    myAccPanel = new MyAccPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(410, 300));

    //Dpmy�lnie ukryte
    loginPanel->Hide();
    myAccPanel->Hide();

    // Przypisanie funkcji obs�ugi zdarze� do przycisk�w
    goBackBtn->Bind(wxEVT_BUTTON, &MainFrame::OnGoBack, this);
    loginBtn->Bind(wxEVT_BUTTON, &MainFrame::OnLogin, this);
    myAccBtn->Bind(wxEVT_BUTTON, &MainFrame::OnMyAcc, this);



    //mainPanel->SetWindowStyleFlag(wxALIGN_CENTER_HORIZONTAL);

    //// style
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Odst�p 10 pikseli od g�rnej kraw�dzi
    sizer->AddSpacer(10);

    // wy�rodkowanie w poziomie
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


// Funkcja obs�ugi zdarzenia po naci�ni�ciu przycisku "Wr��"
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

    //pokazywanie / ukrywanie panel�w
    mainPanel->Show();
    loginPanel->Hide();
    myAccPanel->Hide();

    // Przerysuj okno, aby zastosowa� zmiany widoku
    this->Layout();

    //Poni�sza funkcja jest zdefiniowana w osobnym pliku, aby zapewni� przejrzysto�� kodu.
    mvcShowcase();
}

// Funkcja obs�ugi zdarzenia po naci�ni�ciu przycisku "Zaloguj / zarejestruj"
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

// Funkcja obs�ugi zdarzenia po naci�ni�ciu przycisku "Moje konto"
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
    // Pobieramy �cie�k� do pliku MainFrame.cpp
        wxString parentDir = wxGetCwd();

    // ��czymy �cie�k� do katalogu "Users"
    wxString loggedFile = parentDir + "/Users/_logged.txt";

    // Sprawd�, czy plik istnieje
    if (wxFileExists(loggedFile)) {
        // Otw�rz plik do odczytu
        wxFile file(loggedFile, wxFile::read);

        //int l = file.Length();
        //std::string ll = std::to_string(l);
        //wxLogMessage("%s", ll.c_str());
        int len = file.Length();
        file.Close();

        // Sprawd�, czy plik jest pusty
        if (len == 0)
            return false; // Plik jest pusty, wi�c u�ytkownik nie jest zalogowany
        else return true; //Plik nie jest pusty, u�ytkownik jest zalogowany
        
    }

    return false; // Plik nie istnieje
}
