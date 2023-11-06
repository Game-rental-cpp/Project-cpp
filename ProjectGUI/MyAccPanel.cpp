// MyAccPanel.cpp
#include "MyAccPanel.h"
#include <string>
#include <string>


bool shouldRefresh= true;
//User* userPtr = nullptr;

MyAccPanel::MyAccPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    // Tworzenie przycisku
    button = new wxButton(this, wxID_ANY, "Przycisk w MyAccPanel", wxPoint(10, 10));

    // Tworzenie etykiety
    label = new wxStaticText(this, wxID_ANY, "To jest etykieta w MyAccPanel", wxPoint(10, 50));





    //debugowanie
   /* if(isLogged())
        wxLogMessage("ktos jest zalogowany");
    else
        wxLogMessage("nikt nie jest zalogowany");*/

    Bind(wxEVT_SHOW, &MyAccPanel::OnPanelShow, this);
}










//OnPanelShow wykonuje siê za ka¿dym wyswietleniem i ukryciem myAccPanel na ekranie;
void MyAccPanel::OnPanelShow(wxShowEvent& event)
{
    //Wykonaj jesli MyAccPanel zostal wyswietlony na ekranie
    if (event.IsShown()) {

       //jeœli login jest pusty to znaczy, ze ktos dopiero siê zalogowal, wiec trzeba zasadowac info z pliku
        if (shouldRefresh== true) {

            LoadUser();
            //ukryj label z napisem "wylogowano pomyslnie"
            //wyswietl userPanel
        }

        Layout(); // Zaktualizuj uklad
    }

    
    event.Skip();
}

void MyAccPanel::LoadUser() {
    //wyszukaj w pliku /Users/_logged.txt kto jest zalogowany i pobierz login z tego pliku
  
    //if (isPremium())
    // userPtr = new UserNormal("login");
    // userPtr = new UserPremium("login");

    
    shouldRefresh = false;
}

void MyAccPanel::LogOut() {
    //ukryj userPanel
    //wyswietl label z napisem "wylogowano pomyslnie"
    shouldRefresh= true;
    //user.reset();
}