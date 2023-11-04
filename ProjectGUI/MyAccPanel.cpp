// MyAccPanel.cpp
#include "MyAccPanel.h"
#include <string>

std::string login = "";
//User user;

MyAccPanel::MyAccPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    // Tworzenie przycisku
    button = new wxButton(this, wxID_ANY, "Przycisk w MyAccPanel", wxPoint(10, 10));

    // Tworzenie etykiety
    label = new wxStaticText(this, wxID_ANY, "To jest etykieta w MyAccPanel", wxPoint(10, 50));

    //za³aduj informacje o zalogowanym userze
    //ta funkcja wywo³uje siê tylko podczas pierwszego wyœwietlenia siê myAccPanel
    LoadUser();
}

//OnPanelShow wykonuje siê dopiero za drugim i ka¿dym kolejnym wyœwietleniem myAccPanel na ekranie;
void MyAccPanel::OnPanelShow(wxShowEvent& event)
{
    //Wykonaj jeœli MyAccPanel zosta³ wyœwietlony na ekranie
    if (event.IsShown()) {

       //jeœli login jest pusty to znaczy, ¿e ktoœ dopiero siê zalogowa³, wiêc trzeba za³adowac info z pliku
        if (login == "") {

            LoadUser();
            //ukryj label z napisem "wylogowano pomyœlnie"
            //wyœwietl userPanel
        }

        Layout(); // Zaktualizuj uk³ad
    }

    event.Skip();
}

void MyAccPanel::LoadUser() {
    //wyszukaj w pliku /Users/_logged.txt kto jest zalogowany i pobierz login z tego pliku
    // stwórz obiekt user1 i w³ó¿ do niego stringa wziêtego z _logged.txt
    //User user1("login_wziety_z__logged.txt");
    // nastêpnie przypisz user1 do globalnego obiektu user 
    //user=user1;
    
    //zmieñ wartoœæ globalnej zmiennej login
    //login = login_wziety_z__logged.txt;
}

void MyAccPanel::LogOut() {
    //ukryj userPanel
    //wyœwietl label z napisem "wylogowano pomyœlnie"
    login = "";
    //user.reset();
}