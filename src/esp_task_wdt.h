#pragma once

#include "esp_err.h"

#include <cstdint>

inline esp_err_t esp_task_wdt_reset() { return ESP_OK; }
inline esp_err_t esp_task_wdt_init(int, bool) { return ESP_OK; }
inline esp_err_t esp_task_wdt_add(void *) { return ESP_OK; }
inline esp_err_t esp_task_wdt_delete(void *) { return ESP_OK; }
inline esp_err_t esp_task_wdt_status(void *) { return ESP_OK; }

// ESP-IDF 5 configuration form of the task watchdog. The host runs no watchdog,
// so reconfiguring it only has to accept the struct.
struct esp_task_wdt_config_t {
  uint32_t timeout_ms = 0;
  uint32_t idle_core_mask = 0;
  bool trigger_panic = false;
};
inline esp_err_t esp_task_wdt_reconfigure(const esp_task_wdt_config_t *) { return ESP_OK; }
