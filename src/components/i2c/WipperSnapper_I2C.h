/*!
 * @file WipperSnapper_I2C.h
 *
 * This component initiates I2C operations
 * using the Arduino generic TwoWire driver.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Copyright (c) Brent Rubell 2021 for Adafruit Industries.
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */
#ifndef WipperSnapper_Component_I2C_H
#define WipperSnapper_Component_I2C_H

#include "Wippersnapper.h"
#include <Wire.h>

#include "drivers/WipperSnapper_I2C_Driver.h"
#include "drivers/WipperSnapper_I2C_Driver_AHTX0.h"

// forward decl.
class Wippersnapper;

/**************************************************************************/
/*!
    @brief  Class that provides an interface with the I2C bus.
*/
/**************************************************************************/
class WipperSnapper_Component_I2C {
public:
  WipperSnapper_Component_I2C(
      wippersnapper_i2c_v1_I2CBusInitRequest *msgInitRequest);
  ~WipperSnapper_Component_I2C();
  bool isInitialized();

  wippersnapper_i2c_v1_I2CBusScanResponse scanAddresses();
  bool
  initI2CDevice(wippersnapper_i2c_v1_I2CDeviceInitRequest *msgDeviceInitReq);
  // TODO: Update Implementation
  // THIS NEEDS AN UPDATE REQUEST
  bool updateI2CDevice(
      wippersnapper_i2c_v1_I2CDeviceDeinitRequest *msgDeviceUpdateReq);
  bool deinitI2CDevice(
      wippersnapper_i2c_v1_I2CDeviceDeinitRequest *msgDeviceDeinitReq);

  void update();

private:
  bool _isInit;
  int32_t _portNum;
  TwoWire *_i2c = nullptr;
  std::vector<WipperSnapper_I2C_Driver *> drivers;
  // Sensor drivers
  WipperSnapper_I2C_Driver_AHTX0 *_ahtx0 = nullptr;
};
extern Wippersnapper WS;

#endif // WipperSnapper_Component_I2C_H