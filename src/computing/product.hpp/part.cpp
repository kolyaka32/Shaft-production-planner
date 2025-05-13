#include "part.hpp"


Part::Part(Material _material, float _diameter, float _length)
: material(_material),
diameter(_diameter),
length(length) {

}

time Part::calculateThermalTime() {
    return 1 + diameter/2/25 + material.recristalisationTemp/20;
}

time Part::calculateProcessTime() {
    return calculateThermalTime();
}
