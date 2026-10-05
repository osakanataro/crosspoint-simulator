#pragma once

// Host stand-in for the FreeInk SDK's Rtc (freeink-sdk/libs/hardware/Rtc).
// The OST firmware's HalClock and ClockActivity carry Rtc::DateTime values, so
// the type must exist on the host. The clock itself is the host's wall clock.

#include <Arduino.h>

#include <cstdint>
#include <ctime>

namespace freeink {

class Rtc {
 public:
  struct DateTime {
    uint16_t year = 2000;
    uint8_t month = 1;  // 1-12
    uint8_t day = 1;    // 1-31
    uint8_t hour = 0;   // 0-23
    uint8_t minute = 0;
    uint8_t second = 0;
    uint8_t weekday = 0;  // 0=Sunday .. 6=Saturday
  };

  bool begin() {
    begun_ = true;
    return true;
  }
  bool present() const { return begun_; }

  // UTC, like the hardware RTC the firmware reads.
  bool now(DateTime& out) {
    const std::time_t t = std::time(nullptr) + offsetSeconds_;
    std::tm utc{};
#if defined(_WIN32)
    if (gmtime_s(&utc, &t) != 0) return false;
#else
    if (!gmtime_r(&t, &utc)) return false;
#endif
    out.year = static_cast<uint16_t>(utc.tm_year + 1900);
    out.month = static_cast<uint8_t>(utc.tm_mon + 1);
    out.day = static_cast<uint8_t>(utc.tm_mday);
    out.hour = static_cast<uint8_t>(utc.tm_hour);
    out.minute = static_cast<uint8_t>(utc.tm_min);
    out.second = static_cast<uint8_t>(utc.tm_sec);
    out.weekday = static_cast<uint8_t>(utc.tm_wday);
    return true;
  }

  // Setting the clock only shifts the simulated time; the host clock is untouched.
  bool set(const DateTime& dt) {
    std::tm utc{};
    utc.tm_year = dt.year - 1900;
    utc.tm_mon = dt.month - 1;
    utc.tm_mday = dt.day;
    utc.tm_hour = dt.hour;
    utc.tm_min = dt.minute;
    utc.tm_sec = dt.second;
#if defined(_WIN32)
    const std::time_t target = _mkgmtime(&utc);
#else
    const std::time_t target = timegm(&utc);
#endif
    if (target == static_cast<std::time_t>(-1)) return false;
    offsetSeconds_ = static_cast<int64_t>(target) - static_cast<int64_t>(std::time(nullptr));
    return true;
  }

  bool adjust(int32_t seconds, DateTime* out = nullptr) {
    offsetSeconds_ += seconds;
    return out ? now(*out) : true;
  }

 private:
  bool begun_ = false;
  int64_t offsetSeconds_ = 0;
};

}  // namespace freeink

using Rtc = freeink::Rtc;
