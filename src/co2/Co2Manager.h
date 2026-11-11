#ifndef CO2_MANAGER_H
#define CO2_MANAGER_H

#include "ICo2Sensor.h"
#include "Co2SensorType.h"
#include "sensors/TestCo2Sensor.h"

class Co2Manager {
public:
  /**
   * Returns an initialized sensor owned by the caller, or nullptr on failure.
   * The caller must delete the returned sensor when it is no longer needed.
   */
  ICo2Sensor* getSensor(Co2SensorType type) {
    switch (type) {
      case Co2SensorType::Test: {
        TestCo2Sensor* sensor = new TestCo2Sensor();
        if (sensor == nullptr) {
          return nullptr;
        }
        if (!sensor->initialize()) {
          delete sensor;
          return nullptr;
        }
        return sensor;
      }

      default:
        return nullptr;
    }
  }
};

#endif  // CO2_MANAGER_H
