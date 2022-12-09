#include "tawerna.h"
void Danie::menu_dan()
{


}
int MenuGlowne::menu()
{
    cout << "1. Dania" << endl;
    cout << "2. Dostawa" << endl;
    cout << "Wybierz opcje: " << endl;
    char wybor = cin.get();
    switch (wybor)

    {
        case '1':
            break;
    }

    return 0;
}

int Zamowienie::zliczKoszt() 
{
    int koszt = 0;
    for (int i = 0; i < pozycje.size(); i++)
    {
        koszt += pozycje[i].ilosc * pozycje[i].danie.cena;
    }

    return koszt; 
}

int Zamowienie::czasZamowienia()
{
    int czasZam = 0;
    for (int i = 0; i < pozycje.size(); i++)
    {
        if (czasZam < pozycje[i].danie.czasWykonaniaMin)
            czasZam = pozycje[i].danie.czasWykonaniaMin;
    }
    return czasZam;
}

void wypisz(const Danie &danie, string end="\n\n")
{
    cout << danie.nazwa << " (" << danie.cena << WALUTA << ", " << danie.czasWykonaniaMin << " min)" << end;
}

void wypisz(const vector<Danie> &dania)
{
    cout << "Wektor z daniami (" << dania.size() << "):\n";
    size_t count = 0;
    for (auto &danie : dania) {
        cout << "\t[" << count++ << "]: ";
        wypisz(danie, "\n");
    }

    cout << endl;
}


void wypisz(const Pozycja &pozycja,  string end="\n\n") {
    cout << pozycja.ilosc << "x ";
    wypisz(pozycja.danie, end="\n");
}

void wypisz(const Zamowienie &zamowienie)
{
    cout << "Zamowienie nr. " << zamowienie.numer << ", ";
    cout << (zamowienie.naWynos ? "na wynos" : "na miejscu");
    cout << ": \n";

    size_t count = 0;

    for (auto &pozycja : zamowienie.pozycje) {
        cout << "\t[" << count++ << "]: ";
        wypisz(pozycja, "\n");
    }
}

