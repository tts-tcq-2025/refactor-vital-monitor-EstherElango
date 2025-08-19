#include <iostream>
#include <assert.h>
#include <thread>
#include <chrono>
#include <string>
#include <vector>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

struct VitalThreshold {
    float min;
    float max;
};

// ✅ Pure function (testable without I/O)
bool isVitalNormal(float value, VitalThreshold threshold) {
    return value >= threshold.min && value <= threshold.max;
}

// ✅ I/O function separated from logic
void blinkAlert(const std::string& message) {
    cout << message << "\n";
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

// ✅ Wrapper to check vitals
int vitalsOk(float temperature, float pulseRate, float spo2) {
    VitalThreshold tempRange  = {95, 102};
    VitalThreshold pulseRange = {60, 100};
    VitalThreshold spo2Range  = {90, 100}; // upper bound added for clarity

    if(!isVitalNormal(temperature, tempRange)) {
        blinkAlert("Temperature is critical!");
        return 0;
    }
    if(!isVitalNormal(pulseRate, pulseRange)) {
        blinkAlert("Pulse Rate is out of range!");
        return 0;
    }
    if(!isVitalNormal(spo2, spo2Range)) {
        blinkAlert("Oxygen Saturation is out of range!");
        return 0;
    }
    return 1;
}

// ✅ Strong tests
void testVitals() {
    cout << "\nVitals test\n";

    // Normal case
    assert(vitalsOk(98.6, 72, 95) == 1);

    // Temperature tests
    assert(isVitalNormal(94.9, {95,102}) == false);  // below min
    assert(isVitalNormal(95,   {95,102}) == true);   // boundary
    assert(isVitalNormal(102,  {95,102}) == true);   // boundary
    assert(isVitalNormal(102.1,{95,102}) == false);  // above max

    // Pulse tests
    assert(isVitalNormal(59,   {60,100}) == false);  // below min
    assert(isVitalNormal(60,   {60,100}) == true);   // boundary
    assert(isVitalNormal(100,  {60,100}) == true);   // boundary
    assert(isVitalNormal(101,  {60,100}) == false);  // above max

    // SpO2 tests
    assert(isVitalNormal(89,   {90,100}) == false);  // below min
    assert(isVitalNormal(90,   {90,100}) == true);   // boundary
    assert(isVitalNormal(100,  {90,100}) == true);   // boundary

    // Integration tests
    assert(vitalsOk(94, 72, 95)   == 0); // temp fail
    assert(vitalsOk(98.6, 55, 95) == 0); // pulse fail
    assert(vitalsOk(98.6, 72, 85) == 0); // spo2 fail
    assert(vitalsOk(94, 55, 85)   == 0); // multiple fail

    cout << "All vital tests executed successfully (failures expose bugs)\n";
}

// ✅ Main entry point
int main() {
    testVitals();
    return 0;
}
