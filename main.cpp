#include <SFML/Graphics.hpp>
#include "TGUI/TGUI.hpp"
#include <iostream>
#include "Algorithm.h"

using namespace std;
using namespace sf;

void btnPress(tgui::GuiSFML& gui) {
    Algorithm algo;

    tgui::ComboBox::Ptr box = gui.get<tgui::ComboBox>("ComboBox1");
    tgui::Label::Ptr finished = gui.get<tgui::Label>("finished");
    tgui::Label::Ptr start = gui.get<tgui::Label>("start");
    tgui::Label::Ptr end = gui.get<tgui::Label>("end");
    tgui::Label::Ptr startip = gui.get<tgui::Label>("startip");
    tgui::Label::Ptr endip = gui.get<tgui::Label>("endip");
    tgui::Label::Ptr time = gui.get<tgui::Label>("time");
    tgui::Label::Ptr sum = gui.get<tgui::Label>("sum");

    if(box->getSelectedItem() == "Kruskal's Minimum Spanning Tree")
    {
        cout << "Running Kruskal's" << endl;
        algo.runKruskal();
        start->setText(to_string(algo.start));
        end->setText(to_string(algo.end));
        startip->setText(algo.startIP);
        endip->setText(algo.endIP);
        time->setText(to_string(algo.time) + " milliseconds");
        sum->setText(to_string(algo.sum));
    }
    else if(box->getSelectedItem() == "Prim's Minimum Spanning Tree")
    {
        cout << "Running Prim's" << endl;
        algo.runPrim();
        start->setText(to_string(algo.start));
        end->setText(to_string(algo.end));
        startip->setText(algo.startIP);
        endip->setText(algo.endIP);
        time->setText(to_string(algo.time) + " milliseconds");
        sum->setText(to_string(algo.sum));
    }
}

int main()
{
    sf::RenderWindow window{{800, 600}, ""};

    tgui::GuiSFML gui{window};
    gui.loadWidgetsFromFile("form.txt");

    tgui::Button::Ptr startBtn = gui.get<tgui::Button>("startBtn");

    startBtn->onClick(&btnPress, ref(gui));

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();

            gui.handleEvent(event);
        }

        window.clear();
        gui.draw();
        window.display();
    }

    return 0;
}