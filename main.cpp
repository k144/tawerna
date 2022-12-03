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

    vector<string> entries = {
        "zupa",
        "eeeee",
        "dźwig",
    };
    int selected = 0;
    auto menu = Menu(&entries, &selected);

    auto exit = Button("Wyjdź",  screen.ExitLoopClosure(), ButtonOption::Ascii());

    string imie = "";
    auto input = Input(&imie, "Podaj imię");

    string xd = "";
    auto xdd = Input(&xd, "ddd");

    auto component = Container::Vertical({
        input | flex | borderRounded,
        xdd,
        exit | align_right,
        menu,
    });

    auto component_renderer = Renderer(component, [&] {
        return window(exit->Render() | align_right, vbox({
            vbox({
                text("KARCZMA POD SUPERNOWĄ") | center,
                text("siema " + imie),
                text("wybrałeś pozycję " + entries[selected] + " (" + std::to_string(selected) + ")")
                
            }) | borderRounded | size(WIDTH, LESS_THAN, 90) | size(WIDTH, GREATER_THAN, 61) | center,
            hbox({
                window(text("Formularz") | hcenter, vbox({
                    window(text("Twoje imię"), input->Render()),
                    xdd->Render()

                })) | size(WIDTH, EQUAL, 31),
                window(text("Menu") | hcenter, menu->Render())
            }) | center | flex,
            hbox({
                text(" Dzisiaj mamy: [data]"),
            })
        }));
    });

    screen.Loop(component_renderer);

    return 0;
}