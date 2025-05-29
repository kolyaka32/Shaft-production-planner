#include "submenuCycle.hpp"
// Saving objects
#include "../factory/factory.hpp"
#include "../product/productProcess.hpp"


SubmenuCycle::SubmenuCycle(Window& window)
: CycleTemplate(window),
settings(window),
selectProductButton(window, 0, 0, 160, 50, {"Product", "Изделие"}),
selectProcessButton(window, 160, 0, 160, 50, {"Process", "Процесс"}),
selectFactoryButton(window, 320, 0, 160, 50, {"Factory", "Цех"}),
saveButton(window, 800, 10, 150, 40, {"Save", "Сохранить"}),
loadButton(window, 980, 10, 150, 40, {"Load", "Загрузить"}),
saveInfo(window, 700, 10, {"Saved", "Сохранено"}) {}

void SubmenuCycle::save() {
    // Create save file
    std::ofstream fout("factory.cfg");

    // Writing file name
    fout << "factory.cfg" << '\n';

    // Saving static data
    ProductProcess::save(fout);
    Factory::save(fout);
}

void SubmenuCycle::load() {
    // Openning file for loading from
    std::ifstream fin("factory.cfg");

    // Skipping first line (with file name)
    std::string line;
    std::getline(fin, line);

    // Reading data
    ProductProcess::load(fin);
    std::getline(fin, line);
    Factory::load(fin);
}
