#ifndef TEST_CO2_SENSOR_H
#define TEST_CO2_SENSOR_H

#include "../ICo2Sensor.h"

/** Simulated sensor used to exercise the manager without CO2 hardware. */
class TestCo2Sensor : public ICo2Sensor {
public:
  bool initialize() {
    active_ = true;
    readingAvailable_ = true;
    ppm_ = 420.0f;
    return active_;
  }

  bool isActive() const override {
    return active_;
  }

  bool isReading() const override {
    return readingAvailable_;
  }

  float getPpm() const override {
    return readingAvailable_ ? ppm_ : 0.0f;
  }

private:
  bool active_ = false;
  bool readingAvailable_ = false;
  float ppm_ = 0.0f;
};

#endif  // TEST_CO2_SENSOR_H
