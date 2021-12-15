/*!
 * @file Wippersnapper_ESP32_nvs.cpp
 *
 * Provisioning helper for the ESP32's non-volatile-storage (NVS)
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
#if defined(ARDUINO_FEATHER_ESP32)
#include "Wippersnapper_ESP32_nvs.h"

/****************************************************************************/
/*!
    @brief    Initializes the ESP32's non-volatile-storage (nvs) at an
                "wsNamespace" namespace location.
*/
/****************************************************************************/
Wippersnapper_ESP32_nvs::Wippersnapper_ESP32_nvs() {
  // init. nvs, read-only
  nvs.begin("wsNamespace", false);
}

/****************************************************************************/
/*!
    @brief    De-initializes the ESP32's non-volatile-storage (nvs).
*/
/****************************************************************************/
Wippersnapper_ESP32_nvs::~Wippersnapper_ESP32_nvs() { nvs.end(); }

/****************************************************************************/
/*!
    @brief    Reads and validates credentials from nvs' "wsNamespace"
                namespace.
    @returns  True if credentials were found, False otherwise.
*/
/****************************************************************************/
bool Wippersnapper_ESP32_nvs::validateNVSConfig() {
  _ssid = nvs.getString("wsNetSSID", "");
  _ssidPass = nvs.getString("wsNetPass", "");
  _aioUser = nvs.getString("wsAIOUser", "");
  _aioPass = nvs.getString("wsAIOKey", "");
  _aioURL = nvs.getString("wsAIOURL", "");

  // validate config properly set in partition
  if (_ssid == "" || _ssidPass == "" || _aioUser == "" || _aioPass == "") {
    // TODO: Possibly LED blink/some external error handling around this
    return false;
  }
  return true;
}

/****************************************************************************/
/*!
    @brief    Sets Wippersnapper configuration using nvs configuration
    @returns  True if credentials set successfully, False otherwise.
*/
/****************************************************************************/
bool Wippersnapper_ESP32_nvs::setNVSConfig() {
  WS._network_ssid = _ssid.c_str();
  WS._network_pass = _ssidPass.c_str();
  WS._username = _aioUser.c_str();
  WS._key = _aioPass.c_str();
  WS._mqttBrokerURL = _aioURL.c_str();
  return true;
}

#endif // ARDUINO_ARCH_ESP32