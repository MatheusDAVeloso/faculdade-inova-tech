#ifndef I_CO2_SENSOR_H
#define I_CO2_SENSOR_H

/** Interface for reading a CO2 sensor. Concentration values use ppm. */
class ICo2Sensor {
public:
  virtual ~ICo2Sensor() = default;

  /** Returns true when the sensor was successfully activated. */
  virtual bool isActive() const = 0;

  /** Returns true when a valid CO2 reading is available. */
  virtual bool isReading() const = 0;

  /** Returns the latest CO2 reading in ppm, or 0 when none is available. */
  virtual float getPpm() const = 0;
};

#endif  // I_CO2_SENSOR_H
