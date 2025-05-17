#include "submenuCycle.hpp"


SubmenuCycle::SubmenuCycle(Window& window)
: CycleTemplate(window),
selectProductButton(window, 0, 0, 160, 50, {"Product", "Изделие"}),
selectFactoryButton(window, 160, 0, 160, 50, {"Factory", "Цех"}) {}
