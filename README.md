# Problem jedzących filozofów (ang. Dining philosophers problem)
Program napisany w języku C++ rozwiązujący problem jedzących filozofów **metodą z użyciem hierarchii zasobów.**

## Instrukcja uruchomienia programu
###  1. Pobierz program  
   Aby pobrać projekt na swój komputer, masz dwie opcje:

#### A) Pobierz jako ZIP:  
- Kliknij zielony przycisk **Code** (na górze po prawej).  
- Wybierz opcję **Download ZIP**.  
- Rozpakuj pobrany plik na swoim komputerze.
   
#### B) Użyj git clone: 
- Otwórz terminal.  
- Wpisz: 
```
git clone https://github.com/lipa13/SO2_p1.git
```
###  2.  Otwórz w konsoli lokalizację katalogu z projektem
###  3.  Skompiluj program
Skompilować program można również na dwa sposoby. Do użycia sposobu z użyciem *Makefile*, należy uprzednio zainstalować program *make*.
#### A) Kompilacja z użyciem Makefile:
```
make
```
#### B) Ręczna kompilacja:
```
g++ -std=c++20 -o SO2_p1.exe main.cpp
```
###  4.  Uruchom program z liczbą filozofów podaną w argumencie
```
./SO2_projekt1 [tu podaj liczbe filozofów]
```