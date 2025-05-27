#pragma once

#include <fstream>
#include <string>
#include "productionStep.hpp"
#include "productionSemiproduct.hpp"

//
class ProductProcess {
 private:
    // Getted options
    static int stepCount;
    static int startStep;
    static Material material;
    static unsigned materialIndex;

    // Target part
    static float targetRoughness;
    static float targetDiameter;
    static float targetLength;

    // Blank part
    static float blankRoughness;
    static float blankDiameter;
    static float blankLength;

    // Drawable objects
    ProductionStep steps[4];
    ProductionSemiproduct semiproducts[5];
    GUI::WarningBox warningLowLength, warningLowDiameter;  // Red warnings - unavaliable to produce
    GUI::WarningBox warningHighLength, warningHighDiameter;  // Yellow warnings - ineffecient to produce
    GUI::WarningBox warningHighBlankRoughness;  // Yellow warnings - Too low start roughness - ineffient

 protected:
    static float getCutRoughDistance(float diameter);
    static float getCutMainDistance(float diameter);
    static float getCutTrimmingDistance(float diameter);
    static float getCutFinishingDistance(float diameter);
    static float getInputDiameter(unsigned step, float outDiameter);
    static float getInputLength(unsigned step, float outLength);
    static int getStepCount(float rougness);
    static void updateMaterialProperties();

 public:
    ProductProcess(Window& window);
    void setMaterial(unsigned index);
    void setTargetRoughness(float roughness);
    void setTargetLength(float length);
    void setTargetDiameter(float diameter);
    void setBlankRoughness(float roughness);
    void setBlankLength(float length);
    void setBlankDiameter(float diameter);
    std::string getTargetRoughness();
    std::string getTargetLength();
    std::string getTargetDiameter();
    std::string getBlankRoughness();
    std::string getBlankLength();
    std::string getBlankDiameter();
    static int getMachineCount();
    unsigned getMaterial();
    void updateProcessParameters();
    void draw(Window& window);
    static void save(std::ofstream& fout);
    static void load(std::ifstream& fin);
};
