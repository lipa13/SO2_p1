# Problem jedzących filozofów (ang. Dining philosophers problem)
Program napisany w języku C++ rozwiązujący problem jedzących filozofów ***metodą z użyciem hierarchii zasobów.***

## Instrukcja uruchomienia programu
###  1. Pobierz program  
   Aby pobrać projekt na swój komputer, masz dwie opcje:

#### A) Pobierz jako ZIP
- Kliknij zielony przycisk **Code** (na górze po prawej).  
- Wybierz opcję **Download ZIP**.  
- Rozpakuj pobrany plik na swoim komputerze.
   
#### B) Użyj git clone
- Otwórz terminal.  
- Wpisz: 
```
git clone https://github.com/lipa13/SO2_p1.git
```
###  2.  Otwórz w konsoli lokalizację katalogu z projektem
###  3.  Skompiluj program
Skompilować program można również na dwa sposoby. Do użycia sposobu z użyciem *Makefile*, należy uprzednio zainstalować program *make*.
#### A) Kompilacja z użyciem *Makefile*
```
make
```
#### B) Ręczna kompilacja
```
g++ -std=c++20 -o SO2_p1.exe main.cpp
```
###  4.  Uruchom program z liczbą filozofów podaną w argumencie
```
./SO2_p1 [tu podaj liczbe filozofów]
```
> ⚠️ **Uwaga:** *Program został zaprojektowany tak, aby działał w nieskończoność.*  
> W każdej chwili można przerwać jego działanie, naciskając kombinację klawiszy ***Ctrl + C***.
## Opis problemu
Problem jedzących filozofów to klasyczne zagadnienie z dziedziny informatyki dotyczące synchronizacji procesów. W problemie tym N filozofów siedzi przy okrągłym stole. Każdy filozof wykonuje jedną z dwóch czynności: albo je, albo rozmyśla. Przed każdym z filozofów znajduje się miska z jedzeniem, a pomiędzy każdą sąsiadującą parą filozofów znajduje się jeden widelec. Każdy filozof musi mieć w posiadaniu oba widelce, żeby móc jeść. Dodatkowo, filozofowie nigdy nie rozmawiają ze sobą, co może prowadzić do zakleszczenia, gdy każdy z filozofów chwyci lewy widelec i będzie czekał na prawy (lub na odwrót), uniemożliwiając innym filozofom dostęp do potrzebnych zasobów.
### Metoda z użyciem hierarchii zasobów
Metoda z użyciem hierarchii zasobów to jedno z rozwiązań problemu jedzących filozofów, polegające na uporządkowaniu zasobów (widelców) według ustalonej hierarchii, np. przez nadanie im unikalnych numerów od 1 do N. Kluczową zasadą tej metody jest to, że filozof zawsze najpierw podnosi widelec o niższym numerze, a następnie ten o wyższym. Zwalnianie widelców odbywa się w odwrotnej kolejności. Dzięki temu nie dochodzi do sytuacji, w której każdy filozof czeka na widelec zajęty przez innego – czyli do zakleszczenia. Ustalona kolejność sprawia, że filozofowie nie blokują się nawzajem i mogą bezpiecznie korzystać z widelców.
### Tworzone wątki w programie
Przy każdym uruchomieniu programu tworzonych jest N wątków reprezentujących filozofów, zgodnie z argumentem podanym na uruchomieniu.
Każdy z wątków działa w nieskończonej pętli wykonując poniższe prace:
1. Filozof myśli
2. Filozof podnosi dwa widelce w odpowiedniej kolejności, by uniknąć zakleszczenia
3. Filozof je
4. Filozof odkłada widelce  

Wątki te działają współbieżnie i są niezależne od siebie, jednak korzystają z wspólnych zasobów (widelców), które są reprezentowane jako muteksy. Główny wątek programu odpowiada za utworzenie wszystkich wątków filozofów oraz oczekuje na ich zakończenie poprzez wywołanie metody `join()` dla każdego z nich. Dzięki temu główny wątek nie kończy działania i program cały czas symuluje zachowanie filozofów siedzących przy stole.
### Sekcje krytyczne i ich rozwiązanie

W programie występują dwie główne sekcje krytyczne, czyli fragmenty kodu, do których dostęp musi być kontrolowany, aby uniknąć problemów wynikających z jednoczesnego dostępu wielu wątków do wspólnych zasobów.

Można wyróżnić dwie sekcje krytyczne:

1. Dotycząca korzystania z widelców. 

Każdy widelec reprezentowany jest przez muteks, a filozof może rozpocząć jedzenie tylko wtedy, gdy uda mu się zablokować dwa odpowiednie muteksy (czyli „podnieść” oba widelce). Aby uniknąć zakleszczenia, wprowadzono zasadę hierarchii zasobów – filozofowie zawsze podnoszą najpierw widelec o niższym numerze, a dopiero potem ten o wyższym. Dzięki temu nie może powstać cykliczne oczekiwanie, a więc zakleszczenie jest niemożliwe.


2. Dotycząca wypisywania komunikatów w konsoli.   

Ponieważ wiele wątków może jednocześnie próbować wypisywać tekst, zastosowano dodatkowy muteks (`cout_mutex`), który chroni operacje wypisywania. Dzięki temu każda wiadomość jest wypisywana w całości, bez mieszania się z innymi komunikatami z pozostałych wątków.
