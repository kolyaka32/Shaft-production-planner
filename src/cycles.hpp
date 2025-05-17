#pragma once


// Types of posible cycles to run
enum class Cycle {
    None,
    ProductPlanner,
    FactoryPlaner,
    Default = ProductPlanner,
};
