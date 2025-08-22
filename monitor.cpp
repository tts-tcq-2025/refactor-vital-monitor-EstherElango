#include "monitor.h"

// Helper function: checks if a value is inside a given range
bool isVitalNormal(float value, float min, float max) {
    return value >= min && value <= max;
}

// Main function: checks if all vitals are OK
int vitalsOk(float temperature, float pulseRate, float spo2) {
    if (!isVitalNormal(temperature, 95, 102)) return 0;
    if (!isVitalNormal(pulseRate, 60, 100))   return 0;
    if (!isVitalNormal(spo2, 90, 100))        return 0;
    return 1;  // everything is OK
}
