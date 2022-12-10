#include "tawerna.h"

vector<Danie> wszystkieDania;
Zamowienie zamowienie;
vector<shared_ptr<ComponentBase>> guziki;
map<string, shared_ptr<ComponentBase>> danieNaGuzikDodaj;
map<string, shared_ptr<ComponentBase>> danieNaGuzikUsun;

string otwarcie = "12:00";
string zamkniecie = "21:00";

int dayofweek(int date, int month, int year)
{
    static int t[] = {0, 3, 2, 5, 0, 3,
                      5, 1, 4, 6, 2, 4};
    year -= month < 3;
    return (year + year / 4 - year / 100 +
            year / 400 + t[month - 1] + date) %
           7;
}
bool restaurantIsClosed(int weekday)
{
    return weekday == 0 || weekday == 6;
}

bool isBetween(
        const std::string &now,
        const std::string &lo,
        const std::string &hi)
{
    return (now >= lo) && (now <= hi);
}

void zamowDanie(Danie danie)
{
	
	Pozycja *znaleziona = NULL;
	for (auto& pozycja : zamowienie.pozycje)
	{
		if (pozycja.danie.nazwa == danie.nazwa)
			znaleziona = &pozycja;
	}
	if (znaleziona == NULL) 
	{
		Pozycja pozycja(danie, 1);
		zamowienie.pozycje.emplace_back(pozycja);
		return;
	}
	znaleziona->ilosc+=1;
}
void usunDanie(Danie danie)
{
	Pozycja* znaleziona = NULL;
	size_t poz = 0;
	for (auto& pozycja : zamowienie.pozycje)
	{
		if (pozycja.danie.nazwa == danie.nazwa)
			{
				znaleziona = &pozycja;
				break;
			}
		poz++;
	}
	if (znaleziona == NULL)
		return;
	if (znaleziona->ilosc == 1)
		{
			zamowienie.pozycje.erase(zamowienie.pozycje.begin() + poz);
			return;
		}
	znaleziona->ilosc -= 1;
}


vector<Danie> wczytajDaniazPliku(string sciezka)
{
	vector<Danie> dania;
	ifstream file;
	file.open(sciezka, ios::in);
	if (!file.is_open())
    {
        std::cout << "Blad odczytu pliku\n";
        file.close();
        return dania;
    }

    string line;
    while (getline(file, line))
    {
        int kategoria = 0;
        string nazwa;
        int cena = 0;
        int czasPodania = 0;
        vector <string> skladniki;

        string temp = "";
        int it = 0;

        for (it; it < line.length(); it++)
        {

            if (line[it] == ';')
            {
                kategoria = stoi(temp);
                temp = "";
                it++;
                break;
            }
            temp += line[it];
        }
        for (it; it < line.length(); it++)
        {

            if (line[it] == ';')
            {
                nazwa = temp;
                temp = "";
                it++;
                break;
            }
            temp += line[it];
        }

        for (it; it < line.length(); it++)
        {
            if (line[it] == ';')
            {
                cena = stoi(temp);
                temp = "";
                it++;
                break;
            }
            temp += line[it];
        }

        for (it; it < line.length(); it++)
        {
            if (line[it] == ';')
            {
                czasPodania = stoi(temp);
                temp = "";
                it++;
                break;
            }
            temp += line[it];
        }

        for (it; it < line.length(); it++)
        {
            if (line[it] == ',')
            {
                skladniki.push_back(temp);
                temp = "";
                it++;
            }
            temp += line[it];
        }
        skladniki.push_back(temp);

        Danie danie(kategoria, nazwa, cena, czasPodania);
        danie.skladniki = skladniki;
        dania.push_back(danie);
    }
    file.close();

	return dania;
}


string sprawdzGodzineIdate() {
	int godz = -1, min = -1, dzien = -1, miesiac = -1, rok = -1;

	stringstream(zamowienie.h) >> godz;
	stringstream(zamowienie.m) >> min;
	stringstream(zamowienie.dz) >> dzien;
	stringstream(zamowienie.mc) >> miesiac;
	stringstream(zamowienie.ro) >> rok;


	if (godz < 0 || godz >= 24)
		return "podaj prawidłową godzinę";

	if (min < 0 || min > 59)
		return "podaj prawidłową minutę";

	if (miesiac == 1 || miesiac == 3 || miesiac == 5 || miesiac == 7 || miesiac == 8 || miesiac == 10 || miesiac == 12)
	{
		if (dzien < 1 || dzien > 31)
			return "Podaj właściwy dzień";
	}
	else if (miesiac == 2)
	{
		if (dzien < 1 || dzien > 28)
			return "Podaj właściwy dzień";
	}
	else if (miesiac == 4 || miesiac == 6 || miesiac == 9 || miesiac == 11)
	{
		if (dzien < 1 || dzien > 30)
			return "Podaj właściwy dzień";
	}
	else
		return "Podaj właściwy miesiąc";

    if (rok < 2022 || rok > 2023)
        return "Rok poza zakresem";



    return "";
}

string sprawdzOtwarcie()
{
    if (sprawdzGodzineIdate() != "")
        return "";

    string h = zamowienie.h;
    if (h.length() == 1)
        h = "0" + h;

    string m = zamowienie.m;
    if (m.length() == 1)
        m = "0" + m;

    string czas = h + ":" + m;

    if (!isBetween(czas, otwarcie, zamkniecie))
        return "Przepraszamy, nie obsługujemy  o tej godzinie :c";

    int dzien = -1, miesiac = -1, rok = -1;

    stringstream(zamowienie.dz) >> dzien;
    stringstream(zamowienie.mc) >> miesiac;
    stringstream(zamowienie.ro) >> rok;

    if (restaurantIsClosed(dayofweek(dzien, miesiac, rok)))
        return "Przepraszamy, nie jesteśmy otwarci w weekendy :c";

    return "";
}

auto test = Button("dupa", [] {}, ButtonOption::Ascii());

void inicjalizujGuziki()
{
    for (auto& danie : wszystkieDania) {
        auto dodaj = Button("+", [&] { zamowDanie(danie); }, ButtonOption::Ascii());
        auto usun = Button("-", [&] { usunDanie(danie); }, ButtonOption::Ascii());

        guziki.emplace_back(dodaj);
        guziki.emplace_back(usun);

        danieNaGuzikDodaj[danie.nazwa] = dodaj;
        danieNaGuzikUsun[danie.nazwa] = usun;
    }
}

vector<shared_ptr<Node>> renderujKarteDan()
{
    vector<shared_ptr<Node>> karta;
    for (auto& danie : wszystkieDania)
    {
        string cena = to_string(danie.cena) + " " + WALUTA;

        auto dodaj = danieNaGuzikDodaj[danie.nazwa];
        auto usun = danieNaGuzikUsun[danie.nazwa];

        karta.emplace_back(hbox({
                                        text(" " + danie.nazwa + string(150, '.')) | flex,
                                        text(cena) | align_right,
                                        dodaj->Render(),
                                        usun->Render()
                                }));

    }

    return karta;
}

vector<shared_ptr<Node>> renderujKoszyk()
{
    vector<shared_ptr<Node>> koszyk;
    for (auto& pozycja : zamowienie.pozycje)
    {
    string cena = to_string(pozycja.ilosc) + " x " + to_string(pozycja.danie.cena) + " " + WALUTA + " = " + to_string(pozycja.danie.cena * pozycja.ilosc) + " " + WALUTA;

        koszyk.emplace_back(hbox({
                                        text(pozycja.danie.nazwa + string(150, '.')) | flex,
                                        text(cena) | align_right,
                                }));

        string skladniki = pozycja.danie.skladniki[0];
        for (int i = 1; i < pozycja.danie.skladniki.size(); i++)
        {
            skladniki += ", " + pozycja.danie.skladniki[i];
        };
        koszyk.emplace_back(paragraph("   " + skladniki));
    }
    koszyk.emplace_back(text("RAZEM: " + to_string(zamowienie.zliczKoszt()) + " " + WALUTA) | align_right);

    return koszyk;
}



int main() {

	wszystkieDania = wczytajDaniazPliku("karta_dan.csv");

    inicjalizujGuziki();
    auto kartaDan = renderujKarteDan();
    int wybrane_okno = 0;
    auto screen = ScreenInteractive::Fullscreen();

    auto exit = Button("Wyjdź",  screen.ExitLoopClosure(), ButtonOption::Ascii());

    auto input = Input(&(zamowienie.imieKlienta), "Podaj imię");
    auto adres = Input(&(zamowienie.adres), "Podaj adres");
    auto godz = Input(&(zamowienie.h), "HH")  | size(WIDTH, EQUAL, 4) |  center;
    auto min = Input(&(zamowienie.m), "MM") | size(WIDTH, EQUAL, 4) |  center;
    auto d = Input(&(zamowienie.dz), "dz.") | size(WIDTH, EQUAL, 4) |  center;
    auto mc = Input(&(zamowienie.mc), "mc") | size(WIDTH, EQUAL, 4) |  center;
    auto r = Input(&(zamowienie.ro), "rok") | size(WIDTH, EQUAL, 6) |  center;

    vector<string> stoliki;
    for (int i = 1; i <= 7; i++) {
        stoliki.emplace_back(string(1, '0'+i));
    }
    auto stolik = Dropdown(&stoliki, &(zamowienie.stolik));

    auto wynosCheckbox = Checkbox("Zamów na wynos", &(zamowienie.naWynos), CheckboxOption::Simple());
    auto guzik_formularz2 = Button("Dalej", [&] { wybrane_okno = 1; }, ButtonOption::Simple());
    auto guzik_karta = Button("Przejdz do karty dań", [&] {
        if (!zamowienie.naWynos || (sprawdzGodzineIdate().empty() && sprawdzOtwarcie().empty()))
            wybrane_okno = 2;

        }, ButtonOption::Simple());
    auto guzik_podsumowanie = Button(" ZAMÓW ", screen.ExitLoopClosure(), ButtonOption::Simple());

    auto okno_witaj = Renderer([&] {
        return vbox({
            vbox({
                text("KARCZMA POD SUPERNOWĄ") | center,
            }) | borderRounded | size(WIDTH, LESS_THAN, 90) | size(WIDTH, GREATER_THAN, 61) | center,
            hbox({
                window(text("Formularz") | hcenter, vbox({
                    window(text("Twoje imię"), input->Render()),
                    wynosCheckbox->Render(),
                    guzik_formularz2->Render()
                })) | size(WIDTH, EQUAL, 31)
            }) | center | flex,
        });
    });


    auto okno_formularz2 = Renderer([&] {
        auto form =  zamowienie.naWynos
        ? window(text("Formularz"),
                   vbox({
                       window(text("Twój adres"), adres->Render()),
                       text("Preferowany czas zamówienia") | center,
                       hbox({
                           godz->Render(),
                           text(":  "),
                           min->Render()
                       }) | center,
                       hbox({
                           d->Render(),
                           text("/  "),
                           mc->Render(),
                           text("/  "),
                           r->Render(),
                       }) | center,
                       paragraphAlignCenter(sprawdzGodzineIdate()),
                       paragraphAlignCenter(sprawdzOtwarcie()),
                   })
            )
        : window(text("Formularz"),
                   vbox({
                       text("Wybierz stolik:"),
                       stolik->Render(),
                   })
            );
        return vbox({
            form | size(WIDTH, EQUAL, 31) | center | flex,
            guzik_karta->Render() | center
        }) | flex;
    });

    auto okno_karta = Renderer([&] {
        return vbox({
            window(text("Karta dań") | center, vbox(renderujKarteDan())),
            vbox(renderujKoszyk()),
            guzik_podsumowanie->Render() | center
        });
    });

    auto okno = Container::Tab({
        okno_witaj,
        okno_formularz2,
        okno_karta
    }, &wybrane_okno);


    vector<shared_ptr<ComponentBase>> komponenty_v {
        input | flex | borderRounded,
        wynosCheckbox,
        guzik_formularz2,
        stolik,
        guzik_karta,
        adres,
        min,
        godz,
        d,
        mc,
        r,
        guzik_podsumowanie,
        test,
        exit | align_right
    };

    for (auto& g : guziki) {
        komponenty_v.emplace_back(g);
    }

    auto komponenty = Container::Vertical(komponenty_v);
    auto renderer = Renderer(komponenty, [&] {
        return window(exit->Render() | align_right, okno->Render());
    });

    screen.Loop(renderer);

	return 0;
}