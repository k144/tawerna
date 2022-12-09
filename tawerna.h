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
    string nazwa {};
    short int cena {};
    unsigned short int czasWykonaniaMin {};
    vector<string> skladniki {};
    Danie(string nazwa, short int cena, unsigned short int czasWykonaniaMin)
        : nazwa(nazwa),
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
};
//Zrobiłem paragon na voidzie z tego wzgledu ze nie jest wymagany zrobienia go w stringu
//i tak jest najprosciej (wedlug mnie)
void paragon()
{
    Zamowienie zamowienie;
    fstream plik;
    plik.open("paragon.txt", ios::in | ios::out);
    if (plik.is_open()) {
        plik << zamowienie.numer;
        plik << zamowienie.imieKlienta;
        plik << zamowienie.adres;
        plik << zamowienie.naWynos;
        plik << zamowienie.stolik;
        plik << zamowienie.preferowanyCzas;
        plik << zamowienie.zliczKoszt();
    }
    plik.close();

}
//tu zrobilem void do wyswietlenie paragonu. Mozna zostawic tak jak jest ze samo paragon()
//or zrobic tak jak ania ze kazda zmienna osobno sie wyswietla. To zostawiam Tobie do wybrania
void pokazParagon()
{
    Zamowienie zamowienie;
    fstream plik;
    plik.open("paragon.txt", ios::in);
    if (plik.is_open())
    {
        paragon();
    }
    plik.close();

}
void wypisz(const Danie &danie, string end);
void wypisz(const Zamowienie &zamowienie);
void wypisz(const Pozycja &pozycja, string end);
void wypisz(const vector<Danie> &dania);






#endif //PROJEKT_KLASY_H