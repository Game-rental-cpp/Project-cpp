// MainFrame.cpp
#include "MainFrame.h"
#include <fstream>
#include <filesystem>
#include "json.hpp"


using json = nlohmann::json;

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    // Tworzenie przycisk�w
    goBackBtn = new wxButton(this, wxID_ANY, "Wr��");
    loginBtn = new wxButton(this, wxID_ANY, "Zaloguj / Zarejestruj");
    myAccBtn = new wxButton(this, wxID_ANY, "Moje konto");

    //Pokazuj odpowiednie przyciski w zale�no�ci czy user jest zalogowany czy nie
    goBackBtn->Hide();
    if (UserCRUD::isLogged())
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


    //We have some json object
    json data = {
       {"name", "John"},
       {"age", 30},
       {"city", "New York"}
    };

    // convert to string
        std::string jsonStr = data.dump();

    // print the string
    //wxLogMessage(wxString(jsonStr.c_str()));
    
}




////////////////////////////////////////////////////////////////////////////////////////////////////
// Funkcja obs�ugi zdarzenia po naci�ni�ciu przycisku "Wr��"
void MainFrame::OnGoBack(wxCommandEvent & event)
{
    goBackHandle(goBackBtn, loginBtn, myAccBtn, mainPanel, loginPanel, myAccPanel);
    //MainFrame_Controller::goBackHandle(goBackBtn, loginBtn, myAccBtn, mainPanel, loginPanel, myAccPanel);

    // Przerysuj okno, aby zastosowa� zmiany widoku
    this->Layout();
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
