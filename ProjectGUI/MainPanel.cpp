// MainPanel.cpp
#include "MainPanel.h"
#include "MainPanel_Logic.h"
#include "MainPanel_Controller.h"
#include "Style.h"
#include "UserCRUD.h"
//for some reason code works without including <vector> and "GameCRUD.h"
#include <vector>
#include "GameCRUD.h"
#include "UserNormal.h"
#include "UserPremium.h"



std::vector<Game> gamesVector1; 
//

//How many different games
int gameCount1 = GameCRUD::countGames();

MainPanel::MainPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    //Convert gameCount into string
    wxString gameCountStr = wxString::Format("%d", gameCount1);
    // Creating a label
    //Witaj w wypo¿yczalni gier planszowych! Mamy do zaoferowania n ró¿nych gier. Wybierz któr¹œ z listy i kliknij "Wypo¿ycz"
    label = new wxStaticText(this, wxID_ANY, "Witaj w wypo¿yczalni gier planszowych!", wxPoint(10, 10));
    label->SetForegroundColour(COLOR_LBL);
    label->SetFont(SetTheFont(15, true));

    label2 = new wxStaticText(this, wxID_ANY, "Wybierz coœ z listy i kliknij \"wypo¿ycz\".", wxPoint(10, 40));
    label2->SetForegroundColour(COLOR_LBL);
    label2->SetFont(SetTheFont(13, true));


    /////////
    wxArrayString sortOptions;
    sortOptions.Add("Alfabetycznie (A-Z)");
    sortOptions.Add("Alfabetycznie (Z-A)");
    sortOptions.Add("Liczba wypo¿yczeñ");
    sortOptions.Add("Ocena");

    int y = 70; //height
    sortChoice = new wxChoice(this, wxID_ANY, wxPoint(10, y+3), wxSize(146, 175), sortOptions);
    sortChoice->SetSelection(0);
    //sortChoice->Bind(wxEVT_CHOICE, &MainPanel::OnChoice, this);
    sortChoice->SetFont(SetTheFont(11));  
    ////////////

    searchInput = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(GetClientSize().GetWidth() - 10 - 30 - 190, y), wxSize(190, 30), wxBORDER_RAISED);
    searchInput->SetHint("Wyszukaj grê...");
    //searchInput->Connect(wxEVT_TEXT, wxCommandEventHandler(MainPanel::OnSearchChange), nullptr, this);
    searchInput->SetFont(SetTheFont());

    resetBtn = new wxButton(this, wxID_ANY, "X", wxPoint(GetClientSize().GetWidth() - 10 - 30, y-1), wxSize(30, 31), wxBORDER_NONE);
    resetBtn->SetBackgroundColour(RED);
    resetBtn->SetForegroundColour(COLOR_TEXT_BTN);
    //resetBtn->Bind(wxEVT_BUTTON, &MainPanel::OnResetButtonClick, this, wxID_ANY, wxID_ANY);
    resetBtn->SetFont(SetTheFont());
    //resetBtn->Bind(wxEVT_ENTER_WINDOW, &MainPanel::OnMouseHover, this);

    /////////////

    gamesVector1= MainPanel_Logic::fulfillGamesVector(gameCount1);

    // Create an instance of the controller and bind events
    MainPanel_Controller* controller = new MainPanel_Controller(this, searchInput, resetBtn, sortChoice);
    controller->BindEvents();

    //Bind(wxEVT_SHOW, &MainPanel_Controller::OnShowPanel, this);
}
