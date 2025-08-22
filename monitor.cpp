#include "monitor.h"

// Constructor: initialize thresholds for vitals
Monitor::Monitor() {
    thresholds["temperature"] = {95, 102};
    thresholds["pulseRate"]   = {60, 100};
    thresholds["spo2"]        = {90, 100};
}

// Generic check for any vital
bool Monitor::isVitalNormal(const std::string& vitalName, float value) const {
    auto it = thresholds.find(vitalName);
    if (it == thresholds.end()) {
        // Unknown vital → treat as OK for now
        return true;
    }
    const VitalThreshold& t = it->second;
    return value >= t.min && value <= t.max;
}

// Check if all standard vitals are within range
bool Monitor::vitalsOk(float temperature, float pulseRate, float spo2) const {
    if (!isVitalNormal("temperature", temperature)) return false;
    if (!isVitalNormal("pulseRate",   pulseRate))   return false;
    if (!isVitalNormal("spo2",        spo2))        return false;
    return true;
}
