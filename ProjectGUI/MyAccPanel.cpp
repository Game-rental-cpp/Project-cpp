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

    //za�aduj informacje o zalogowanym userze
    //ta funkcja wywo�uje si� tylko podczas pierwszego wy�wietlenia si� myAccPanel
    LoadUser();
}

//OnPanelShow wykonuje si� dopiero za drugim i ka�dym kolejnym wy�wietleniem myAccPanel na ekranie;
void MyAccPanel::OnPanelShow(wxShowEvent& event)
{
    //Wykonaj je�li MyAccPanel zosta� wy�wietlony na ekranie
    if (event.IsShown()) {

       //je�li login jest pusty to znaczy, �e kto� dopiero si� zalogowa�, wi�c trzeba za�adowac info z pliku
        if (login == "") {

            LoadUser();
            //ukryj label z napisem "wylogowano pomy�lnie"
            //wy�wietl userPanel
        }

        Layout(); // Zaktualizuj uk�ad
    }

    event.Skip();
}

void MyAccPanel::LoadUser() {
    //wyszukaj w pliku /Users/_logged.txt kto jest zalogowany i pobierz login z tego pliku
    // stw�rz obiekt user1 i w�� do niego stringa wzi�tego z _logged.txt
    //User user1("login_wziety_z__logged.txt");
    // nast�pnie przypisz user1 do globalnego obiektu user 
    //user=user1;
    
    //zmie� warto�� globalnej zmiennej login
    //login = login_wziety_z__logged.txt;
}

void MyAccPanel::LogOut() {
    //ukryj userPanel
    //wy�wietl label z napisem "wylogowano pomy�lnie"
    login = "";
    //user.reset();
}