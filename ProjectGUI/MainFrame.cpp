// MainFrame.cpp
#include "MainFrame.h"
#include "Style.h"


MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size) {

    // Creating buttons
    goBackBtn = new wxButton(this, wxID_ANY, "Wróæ", wxDefaultPosition, wxSize(80, 40));
    loginBtn = new wxButton(this, wxID_ANY, "Zaloguj / Zarejestruj", wxDefaultPosition, wxSize(170, 40), wxBORDER_RAISED);
    myAccBtn = new wxButton(this, wxID_ANY, "Moje konto", wxDefaultPosition, wxSize(100, 40));

    goBackBtn->Hide();
    MainFrame_Logic::HideButton(loginBtn, myAccBtn); //hide one of the buttons

    // Creating and adding panels
    mainPanel = new MainPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(410, 500));
    loginPanel = new LoginPanel(this, wxID_ANY, wxPoint(20, 200), wxSize(410, 500));
    myAccPanel = new MyAccPanel(this, wxID_ANY, wxPoint(10, 100), wxSize(410, 500));

    
        //wxLogMessage(wxString::Format("%s", UserCRUD::ReadUser("userek123")));

    MainFrame_Logic::CreateUser();

    // Default hidden
    mainPanel->Hide(); //temporarily hide to trigger the OnPanelShow 
    loginPanel->Hide();
    myAccPanel->Hide();
    mainPanel->Show(); 

    // Create an instance of the controller and bind events
    MainFrame_Controller* controller = new MainFrame_Controller(this, goBackBtn, loginBtn, myAccBtn, mainPanel, loginPanel, myAccPanel);
    controller->BindEvents();
   
    // Navigation button style
    loginBtn->SetFont(SetTheFont(10).MakeBold());
    loginBtn->SetBackgroundColour(COLOR_BACKGROUND_LOGINBTN);
    loginBtn->SetForegroundColour(COLOR_TEXT_LOGINBTN);

    myAccBtn->SetFont(SetTheFont(10).MakeBold());
    myAccBtn->SetBackgroundColour(COLOR_BACKGROUND_PANEL);
    myAccBtn->SetForegroundColour(COLOR_TEXT_BTN);

    goBackBtn->SetFont(SetTheFont(10).MakeBold());
    goBackBtn->SetBackgroundColour(COLOR_BACKGROUND_PANEL);
    goBackBtn->SetForegroundColour(COLOR_TEXT_BTN);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Space of 10 pixels from the top edge
    sizer->AddSpacer(10);

    // Center horizontally
    sizer->Add(goBackBtn, 0, wxALIGN_CENTER_HORIZONTAL);
    sizer->Add(loginBtn, 0, wxALIGN_CENTER_HORIZONTAL);
    sizer->Add(myAccBtn, 0, wxALIGN_CENTER_HORIZONTAL);

    sizer->AddSpacer(10);

    sizer->Add(mainPanel, 0, wxALIGN_CENTER_HORIZONTAL);
    sizer->Add(loginPanel, 0, wxALIGN_CENTER_HORIZONTAL);
    sizer->Add(myAccPanel, 0, wxALIGN_CENTER_HORIZONTAL);

    // Assign sizer to the frame
    this->SetSizer(sizer);
    this->SetBackgroundColour(COLOR_BACKGROUND_FRAME); // Set background color (optional)
}
