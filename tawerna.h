#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

const string WALUTA = "MGD";

#ifndef PROJEKT_KLASY_H
#define PROJEKT_KLASY_H

class Danie
{
    friend class MenuGlowne;
    void menu_dan();
public:
    short int kategoria {};
    string nazwa {};
    short int cena {};
    unsigned short int czasWykonaniaMin {};
    vector<string> skladniki {};
    Danie(short int kategoria, string nazwa, short int cena, unsigned short int czasWykonaniaMin)
        : kategoria(kategoria),
          nazwa(nazwa),
          cena(cena),
          czasWykonaniaMin(czasWykonaniaMin)
    {
        cout << "Tworze danie " << nazwa << " za " << cena << WALUTA << ", czas wykonania: " << czasWykonaniaMin << " min" << endl;
    }
};


class MenuGlowne
{
public:
    int menu();

};

class Pozycja {
public:
    Pozycja(Danie danie, unsigned short int ilosc) : danie(danie), ilosc(ilosc)
    {
        cout << "Tworze pozycje " << ilosc << "x " << danie.nazwa << endl;
    }
    Danie danie;
    unsigned short int ilosc {};
};

class Zamowienie {
public:
    int numer {};
    string imieKlienta {};
    string adres {};
    bool naWynos = false;
    int stolik {};
    time_t preferowanyCzas {};
    vector<Pozycja> pozycje {};
    int zliczKoszt();
    int czasZamowienia();
};

void wypisz(const Danie &danie, string end);
void wypisz(const Zamowienie &zamowienie);
void wypisz(const Pozycja &pozycja, string end);
void wypisz(const vector<Danie> &dania);






#endif //PROJEKT_KLASY_H