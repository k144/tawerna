#include <iostream>
#include <vector>
#include <string>
#include <chrono>   
#include <thread>
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
#include <memory>  // for shared_ptr, __shared_ptr_access


int main(void) {
    using namespace ftxui;
    using namespace std;

    auto screen = ScreenInteractive::Fullscreen();
    int wybrane_okno = 0;


    string imie = "";
    auto podaj_imie = Input(&imie, "");

    string nazwisko = "";
    auto podaj_nazwisko = Input(&nazwisko, "nazwisko");

    auto guzik_karta_dan = Button("Przejdź do karty dań", [&] {
        if (imie == "") return;
        wybrane_okno = 1;
    });

    auto guzik_koszyk = Button("Przejdź do koszyka", [&] {
        wybrane_okno = 2;
    });

    auto okno_witaj = Renderer([&] {
        return vbox(
            text("Witaj w Karczmie pod Supernową") | center | size(HEIGHT, EQUAL, 3),
            paragraphAlignCenter("srutututu jakis opis Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.") | size(WIDTH, LESS_THAN, 60) | center,
            text(""),
            window(text("Twoje imie:"), podaj_imie->Render())
            | size(WIDTH, EQUAL, 40)
            | center,
            text(""),
            guzik_karta_dan->Render() | center
        );
    });


    auto okno_karta_dan = Renderer([&] {
        return vbox({
           text("karta dań"),
           guzik_koszyk->Render()
        });
    });

    auto okno_koszyk = Renderer([&] {
        return vbox({
        });
    });

    auto okno = Container::Tab({
       okno_witaj,
       okno_karta_dan,
       okno_koszyk
    }, &wybrane_okno);

    auto exit = Button("Wyjdź",  screen.ExitLoopClosure(), ButtonOption::Ascii());
    auto komponenty = Container::Vertical({
        okno,
        exit,
        podaj_imie,
        guzik_karta_dan,
        podaj_nazwisko,
        guzik_koszyk,
    });

    auto renderer = Renderer(komponenty, [&] {
        return window(exit->Render() | align_right,
            okno->Render()
        );
    });

    screen.Loop(renderer);

    return 0;
}