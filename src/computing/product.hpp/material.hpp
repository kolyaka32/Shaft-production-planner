#pragma once


// Special type for time
typedef float time;  // Time in minutes

// Class represemting material of creating part
class Material {
public:
    Material(float recrist);

    // Properties of material
    const float recristalisationTemp;


    // Standart materials to use
    static const Material machineSteel;
    static const Material alloys;
    static const Material headResistantSteel;
};
