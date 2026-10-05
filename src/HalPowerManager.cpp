#include "HalPowerManager.h"

#include "HalGPIO.h"

HalPowerManager powerManager;

void HalPowerManager::begin() {}
void HalPowerManager::startDeepSleep(HalGPIO &gpio) const { gpio.startDeepSleep(); }
void HalPowerManager::setPowerSaving(bool enable) {}
uint16_t HalPowerManager::getBatteryPercentage() const { return 100; }

HalPowerManager::Lock::Lock() {}
HalPowerManager::Lock::~Lock() {}

uint16_t HalPowerManager::getBatteryMillivolts() const {
  // A healthy mid-charge cell; the simulator has no gauge to read.
  return 3900;
}
