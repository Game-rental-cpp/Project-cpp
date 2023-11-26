// MainFrame.cpp
#include "MainFrame.h"
#include <fstream>
#include <filesystem>
#include "json.hpp"
#include "Style.h"

using json = nlohmann::json;

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    // Creating buttons
    goBackBtn = new wxButton(this, wxID_ANY, "Wróæ", wxDefaultPosition, wxSize(80, 40));
    loginBtn = new wxButton(this, wxID_ANY, "Zaloguj / Zarejestruj", wxDefaultPosition, wxSize(170, 40), wxBORDER_RAISED);
    myAccBtn = new wxButton(this, wxID_ANY, "Moje konto", wxDefaultPosition, wxSize(100, 40));

    //Show appropriate buttons depending on whether the user is logged in or not
    goBackBtn->Hide();
    if (UserCRUD::isLogged())
        loginBtn->Hide();
    else myAccBtn->Hide();

    // Creating and adding panels
    mainPanel = new MainPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(410, 500));
    loginPanel = new LoginPanel(this, wxID_ANY, wxPoint(20, 200), wxSize(410, 500));
    myAccPanel = new MyAccPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(410, 500));

    //default hidden
    mainPanel->Hide();
    loginPanel->Hide();
    myAccPanel->Hide();

    mainPanel->Show();

    // Assigning event handling functions to buttons
    goBackBtn->Bind(wxEVT_BUTTON, &MainFrame::OnGoBack, this);
    loginBtn->Bind(wxEVT_BUTTON, &MainFrame::OnLogin, this);
    myAccBtn->Bind(wxEVT_BUTTON, &MainFrame::OnMyAcc, this);

    //change cursor on hover
    loginBtn->Bind(wxEVT_ENTER_WINDOW, &MainFrame::OnMouseHover, this);
    goBackBtn->Bind(wxEVT_ENTER_WINDOW, &MainFrame::OnMouseHover, this);
    myAccBtn->Bind(wxEVT_ENTER_WINDOW, &MainFrame::OnMouseHover, this);
    //loginBtn->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::OnMouseHover, this);

    //nav button style
    loginBtn->SetFont(SetTheFont(10).MakeBold());
    loginBtn->SetBackgroundColour(COLOR_BACKGROUND_LOGINBTN);
    loginBtn->SetForegroundColour(COLOR_TEXT_LOGINBTN);

    myAccBtn->SetFont(SetTheFont(10).MakeBold());
    myAccBtn->SetBackgroundColour(COLOR_BACKGROUND_PANEL);
    myAccBtn->SetForegroundColour(COLOR_TEXT_BTN);

    goBackBtn->SetFont(SetTheFont(10).MakeBold());
    goBackBtn->SetBackgroundColour(COLOR_BACKGROUND_PANEL);
    goBackBtn->SetForegroundColour(COLOR_TEXT_BTN);


    //mainPanel->SetWindowStyleFlag(wxALIGN_CENTER_HORIZONTAL);

    //// style
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Odstêp 10 pikseli od górnej krawêdzi
    sizer->AddSpacer(10);

    // wyœrodkowanie w poziomie
    //sizer->Add(goBackBtn, 0, wxALIGN_LEFT | wxLEFT, 40);
    sizer->Add(goBackBtn, 0, wxALIGN_CENTER_HORIZONTAL);
    sizer->Add(loginBtn, 0, wxALIGN_CENTER_HORIZONTAL);
    sizer->Add(myAccBtn, 0, wxALIGN_CENTER_HORIZONTAL);

    sizer->AddSpacer(10);


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

        this->SetBackgroundColour(COLOR_BACKGROUND_FRAME); // Set background color (optional)

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


void MainFrame::OnMouseHover(wxMouseEvent& event) {
    ChangeCursor(event);
}