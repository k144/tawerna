#include "tawerna.h"

vector<Danie> wszystkieDania;
Zamowienie zamowienie;

int main() {
    wszystkieDania = {
            Danie("Kebs", 25, 15),
            Danie("Onion Orbits", 12, 10),
            Danie("Tatar awatar", 17, 10)
    };

    zamowienie.numer = 2137;
    zamowienie.pozycje.emplace_back(wszystkieDania[0], 1);
    zamowienie.pozycje.emplace_back(wszystkieDania[1], 2);

    wypisz(wszystkieDania);
    wypisz(zamowienie);

    return 0;
}
