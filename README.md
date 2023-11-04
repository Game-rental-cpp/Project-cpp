
# Board game rental app
## App description
Will be soon.
## Do zespołu:

Każdy ma (a jak nie to będzie mieć) przydzielony zestaw plików, na których będzie pracować. Żeby uniknąć konfliktów nie tykaj plików, kóre nie należą do ciebie, ale jeśli musisz to zrobić, powiadom resztę. Żeby kod był czytelny staramy się używać wzorca MVC, czyli tam gdzie to możliwe oddzielamy logikę od warstwy graficznej. Spójrz na plik MainFrame.cpp. Jest w nim wywoływana funkcja mvcShowcase(), która jest zdefiniowana w pliku Logic.cpp, a nie w MainFrame.cpp. Jest to przykład zastosowania archiktektury mvc.

### praca z gitem

Masz już sklonowane repo? Otwórz folder Project-cpp, kliknij prawym i wybierz opcję *git bash here*. Jeśli jej nie widzisz kliknij w pokaż więcej opcji. Wpisz w konsoli __pwd__ i powinna ci się wyświwietlić *ścieżka/do/twojego/projektu/Project-cpp*. Jeśli masz wątpliwości, możesz jeszcze wpisać __ls__ i powinien ci się wyświetlić m.in. plik ProjectGUI.sln. oraz readme.md.

Nasz projekt posiada trzy branche zdalne, są to main, dev i test. Was najbardziej będzie interesować dev. Jeśli jeszcze na nim nie jesteś, przełącz się na niego używając komendy __git checkout dev__. Będziesz za jego pośrednictwem wypychać zmiany na zdalne repozytorium, a ja ja potem będe scalał z main. Nigdy nie pisz kodu bezpośrednio na branchu zdalnym! Od tego są branche lokalne. Będąc na branchu dev utwórz branch lokalny i przełącz się na niego komendą __git checkout -b nazwa_brancha__. Najlepiej nazywać go tak samo jak feature nad którym pracujesz, np. zapisdDoPliku. Czyli na każdy feature przypadać będzie osobny branch. Gdyby branchy było już za dużo możesz usunąć te, których już nie potrzebujesz komendą __git branch --delete nazwa_brancha_do_usuniecia__. Teraz możesz dokonywać zmian w projekcie. Na dobry początek znajdź plik *readme.md* w eksploratorze rozwiązań w Visual Studio. Jeśli go nie widzisz kliknij prawym na *drzewko eksploratora > dodaj > istniejący element > readme.md*. Na samym końcu tego pliku zapisz swoje imię i nazwisko. Przypuśćmy, że chcesz te zmiany wypchnąć na GH. W tym celu musisz:

0. Sprawdź 3 razy czy na pewno wszystko dobrze działa, nie ma błędów kompilacji itp.

1. Zatwierdzić zmiany wpisując komendę __git add -A__, a następnie __git commit -m"krótki opis commita"__ np. __git commit -m"write a name"__. Commity róbcie często i gęsto, podziękujecie sobie za to w przyszłości. Treść commitów powinna być zapisana w trybie rozkazującym. Dlaczego? Nie wiem, taka jest konwencja.

2. Przełączyć się na branch zdalny. Podczas normalnej pracy będzie to dev. Użyj do tego celu komendy __git checkout nazwa_brancha_zdalnego__.

3. Zaciągnij zmiany, które ktoś inny mógł w międzyczasie wprowadzić do zdalnego repozytorium komendą __git pull__.

4. Przełacz się z powrotem na twój branch lokalny komendą __git checkout nazwa_brancha_lokalnego__ lub krócej __git checkout -__.

5. Będąc na odpowienim branchu lokalnym wpisz komendę __git rebase nazwa_brancha_zdalnego__.

6. Módl się żeby nie było konfliktów. 🙏

6.5 Jeśli chcesz, możesz wpisać komendę __git log__ lub lepiej __git log --oneline__, żeby zobaczyć jak rebase wpłynął na kolejność commitów.

7. Przełącz się na branch zdalny komendą __git checkout nazwa_brancha_zdalnego__ lub krócej __git checkout -__.

8. Wpisz komendę __git merge nazwa_brancha_lokalnego__. Zwróć uwagę, że nie używamy komendy rebase na branchach zdalnych - to ważne.

9. Wypchnij zmiany na GH komendą __git push__. NIE UŻYWAJ FLAGI -f ANI --force !

10. Zmień branch na lokalny, żeby przez przypadek nie pisać nic na branchu zdalnym.

11. Prawdopodobnie będziesz musieć jeszcze stworzyć na GitHubie pull request. W tym celu kliknij w taki duży zielony przycisk przy kodzie.

#### Na koniec jeszcze kilka wskazówek.

Przed rozpoczęciem pracy zawsze upewnij się, że jesteś na odpowiednim branchu i że konsola gita działa we właściwym miejscu, tj. *ścieżka/do/twojego/projektu/Project-cpp*, a nie np. *ścieżka/do/twojego/projektu/Project-cpp/ProjectGUI*.

W większości przypadków przed użyciem komendy checkout trzeba zacommitować zmiany. Jeśli nie masz pewności kiedy należy to zrobić, a kiedy nie, wpisz komendę git status. Jeśli wyświetli ci się komunikat *nothing to commit, working tree clean* to nie muszisz nic commitować. 

Może się zdarzyć, że po przełaczaniu się na inny branch VisualStudio wyświetli ci jakiś komunikat, wtedy kliknij pierwszą opcję z lewej.

Jeśli chcesz wyświetlić listę branchy, wpisz komendę __git branch__. Branch z gwiazdką to ten, na którym się teraz znajdujesz.

##### Miejsce na podpisy:
##### - Mikołaj Karaman
##### -
