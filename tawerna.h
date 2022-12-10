#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <map>
#include <numeric>
#include <iterator>
#include <sstream>
#include <algorithm>
#include "ftxui/component/captured_mouse.hpp"      // for ftxui
#include "ftxui/component/component.hpp"           // for Menu
#include "ftxui/component/component_options.hpp"   // for MenuOption
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"
#include "ftxui/component/component.hpp"  // for Renderer, CatchEvent, Horizontal, Menu, Tab
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/event.hpp"               // for Event
#include "ftxui/component/mouse.hpp"               // for Mouse
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/canvas.hpp"                    // for Canvas
#include "ftxui/screen/color.hpp"  // for Color, Color::Red, Color::Blue, Color::Green, ftxui

using namespace std;
using namespace ftxui;

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
    string h {};
    string m {};
    string dz {};
    string mc {};
    string ro {};
    int stolik {};
    vector<Pozycja> pozycje {};
    int zliczKoszt();
    int czasZamowienia();
};

void wypisz(const Danie &danie, string end);
void wypisz(const Zamowienie &zamowienie);
void wypisz(const Pozycja &pozycja, string end);
void wypisz(const vector<Danie> &dania);






#endif //PROJEKT_KLASY_H