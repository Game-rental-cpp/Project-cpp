# Board game rental app

## App description

This app is a simulation of a board game rental shop written ic C++. To run this app you need to install a C++ compiler and wxWidgets library version 3.2.3 (it's used to build the graphical user interface). If you struggle to install it, follow [this](https://www.youtube.com/watch?v=ONYW3hBbk-8&list=PLFk1_lkqT8MbVOcwEppCPfjGOGhLvcf9G&index=2) guide. If you want to collaborate, preferred IDE is Visual Studio. 

#### Main features:

- sign in/sign up
- enhance account to premium version
- sort and filter games
- rate games

## Do zespołu:

Każdy ma (a jak nie to będzie mieć) przydzielony zestaw plików, na których będzie pracować. Żeby uniknąć konfliktów nie tykaj plików, kóre nie należą do ciebie, ale jeśli musisz to zrobić, powiadom resztę. Żeby kod był czytelny staramy się używać wzorca MVC (model, view, controller), czyli tam gdzie to możliwe oddzielamy logikę od warstwy wizualnej.

### praca z gitem

Nasz projekt posiada trzy branche zdalne, są to main, dev i test. Was najbardziej będzie interesować dev. Jeśli jeszcze na nim nie jesteś, przełącz się na niego używając komendy **git checkout dev**. Będziesz za jego pośrednictwem wypychać zmiany na zdalne repozytorium. Nigdy nie pisz kodu bezpośrednio na branchu współdzielonym! Od tego są branche lokalne utworzone przez ciebie. Będąc na branchu dev utwórz branch lokalny i przełącz się na niego komendą **git checkout -b nazwa_brancha**. Najlepiej nazywać go tak samo jak feature nad którym pracujesz, np. zapisdDoPliku. Czyli na każdy feature przypadać będzie osobny branch. Gdyby branchy było już za dużo możesz usunąć te, których już nie potrzebujesz komendą **git branch --delete nazwa_brancha_do_usuniecia**. Teraz możesz dokonywać zmian w projekcie. Na dobry początek znajdź plik _readme.md_ w eksploratorze rozwiązań w Visual Studio. Jeśli go nie widzisz kliknij prawym na _drzewko eksploratora > dodaj > istniejący element > readme.md_. Na samym końcu tego pliku zapisz swoje imię i nazwisko. Przypuśćmy, że chcesz te zmiany wypchnąć na GH. W tym celu musisz:

0. Sprawdźić 3 razy czy na pewno wszystko dobrze działa, nie ma błędów kompilacji itp.

1. Zatwierdzić zmiany wpisując komendę **git add -A**, a następnie **git commit -m"krótki opis commita"** np. **git commit -m"write a name"**. Commity róbcie często i gęsto, podziękujecie sobie za to w przyszłości.

2. Przełączyć się na branch współdzielony. Podczas normalnej pracy będzie to dev. Użyj do tego celu komendy **git checkout nazwa_brancha_wspoldzielonego**.

3. Zaciągnij zmiany, które ktoś inny mógł w międzyczasie wprowadzić do zdalnego repozytorium komendą **git pull**. Jeśli widzisz komunikat _Already up to date_ możesz przejść do kroku 8.

4. Przełacz się z powrotem na twój branch lokalny komendą **git checkout nazwa_brancha_lokalnego** lub krócej **git checkout -**.

5. Będąc na odpowienim branchu lokalnym wpisz komendę **git rebase nazwa_brancha_wspoldzielonego**.

6. Módl się żeby nie było konfliktów. 🙏

6.5 Jeśli chcesz, możesz wpisać komendę **git log** lub lepiej **git log --oneline**, żeby zobaczyć jak rebase wpłynął na kolejność commitów.

7. Przełącz się na branch współdzielony komendą **git checkout nazwa_brancha_wspoldzielonego** lub krócej **git checkout -**.

8. Wpisz komendę **git merge nazwa_brancha_lokalnego**. Zwróć uwagę, że nie używamy komendy rebase na branchach współdzielonych - to ważne.

9. Wypchnij zmiany na GH komendą **git push**. NIE UŻYWAJ FLAGI -f ANI --force !

10. Zmień branch, żeby przez przypadek nie pisać nic na branchu współdzielonym.

#### Na koniec jeszcze kilka wskazówek.

Przed rozpoczęciem pracy zawsze upewnij się, że jesteś na odpowiednim branchu.

W większości przypadków przed użyciem komendy checkout trzeba zacommitować zmiany. Jeśli nie masz pewności kiedy należy to zrobić, a kiedy nie, wpisz komendę git status. Jeśli wyświetli ci się komunikat _nothing to commit, working tree clean_ to nie muszisz nic commitować.

Może się zdarzyć, że po przełaczaniu się na inny branch Visual Studio wyświetli ci jakiś komunikat, wtedy kliknij pierwszą opcję z lewej.

Jeśli chcesz wyświetlić listę branchy, wpisz komendę **git branch**. Branch z gwiazdką to ten, na którym się teraz znajdujesz.

##### Miejsce na podpisy:

##### - Mikołaj Karaman

##### -
