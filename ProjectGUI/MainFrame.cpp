// MainFrame.cpp
#include "MainFrame.h"
#include <fstream>
#include <filesystem>
#include "json.hpp"


using json = nlohmann::json;

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    // Tworzenie przycisków
    goBackBtn = new wxButton(this, wxID_ANY, "Wróæ");
    loginBtn = new wxButton(this, wxID_ANY, "Zaloguj / Zarejestruj");
    myAccBtn = new wxButton(this, wxID_ANY, "Moje konto");

    //Pokazuj odpowiednie przyciski w zale¿noœci czy user jest zalogowany czy nie
    goBackBtn->Hide();
    if (UserCRUD::isLogged())
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
// Funkcja obs³ugi zdarzenia po naciœniêciu przycisku "Wróæ"
void MainFrame::OnGoBack(wxCommandEvent & event)
{
    goBackHandle(goBackBtn, loginBtn, myAccBtn, mainPanel, loginPanel, myAccPanel);
    //MainFrame_Controller::goBackHandle(goBackBtn, loginBtn, myAccBtn, mainPanel, loginPanel, myAccPanel);

    // Przerysuj okno, aby zastosowaæ zmiany widoku
    this->Layout();
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
