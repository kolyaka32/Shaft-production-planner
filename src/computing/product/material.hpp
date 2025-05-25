#pragma once

// Class represemting material of creating part
class Material {
public:
    Material(float recrist, float density);
    const Material& operator=(const Material& _mat);

    // Properties of material
    float recristalisationTemp;
    float density;

    // Standart materials to use
    static const Material machineSteel;
    static const Material alloys;
    static const Material heatResistantSteel;
};
