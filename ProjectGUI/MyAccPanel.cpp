// MyAccPanel.cpp
#include "MyAccPanel.h"
#include <string>
#include <string>
#include "UserNormal.h"
#include "UserPremium.h"

bool shouldRefresh= true;


MyAccPanel::MyAccPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    // Tworzenie przycisku
    button = new wxButton(this, wxID_ANY, "Przycisk w MyAccPanel", wxPoint(10, 10));
    //button->Bind(wxEVT_BUTTON, &MyAccPanel::LoadUser, this);
    button->Bind(wxEVT_BUTTON, &MyAccPanel::ChangeToPremium, this);

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

        if (user) {
            // Przyk³adowe u¿ycie informacji o u¿ytkowniku
            std::string userInfo = "Login: " + user->getLogin() + "\nGames: " + user->stringifyGames();
            wxLogMessage("%s", userInfo);
        }

       //jeœli login jest pusty to znaczy, ze ktos dopiero siê zalogowal, wiec trzeba zasadowac info z pliku
        if (shouldRefresh== true) {

            //LoadUser();
            //ukryj label z napisem "wylogowano pomyslnie"
            //wyswietl userPanel
        }

        Layout(); // Zaktualizuj uklad
    }

    
    event.Skip();
}

void MyAccPanel::ChangeToPremium(wxCommandEvent& event) {
    //wyszukaj w pliku /Users/_logged.txt kto jest zalogowany i pobierz login z tego pliku
  
    //if (isPremium())
    // userPtr = new UserNormal("login");
    // userPtr = new UserPremium("login");

   // Zwolnij zasoby starego u¿ytkownika
    std::vector<User::UserGame> vec = user->getUserGames();

    delete user;

    // Utwórz nowego u¿ytkownika typu UserPremium, ale nadal u¿ywaj¹c istniej¹cego obiektu
    user = new (user) UserPremium("login_premium");
    user->setUserGames(vec);

    shouldRefresh = false;
}

void MyAccPanel::LogOut() {
    //ukryj userPanel
    //wyswietl label z napisem "wylogowano pomyslnie"
    shouldRefresh= true;
    //user.reset();
}