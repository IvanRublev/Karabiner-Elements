#pragma once

#include "boost_defs.hpp"

#include <CoreFoundation/CoreFoundation.h>
#include <boost/optional.hpp>
#include <cmath>

class system_preferences final {
public:
  class values {
  public:
<<<<<<< HEAD
    values(void) : keyboard_fn_state_(system_preferences::get_keyboard_fn_state()),
                   standalone_key_milliseconds_(system_preferences::get_standalone_key_milliseconds()) {
    }

    bool get_keyboard_fn_state(void) const { return keyboard_fn_state_; }
    uint32_t get_standalone_key_milliseconds(void) const { return standalone_key_milliseconds_; }

    bool operator==(const system_preferences::values& other) const {
      return keyboard_fn_state_ == other.keyboard_fn_state_ &&
             standalone_key_milliseconds_ == other.standalone_key_milliseconds_;
    }
    bool operator!=(const system_preferences::values& other) const { return !(*this == other); }

  private:
    bool keyboard_fn_state_;
    uint32_t standalone_key_milliseconds_;
  };

  static boost::optional<bool> get_bool_property(CFStringRef _Nonnull key, CFStringRef _Nonnull application_id) {
    boost::optional<bool> value = boost::none;
    if (auto v = CFPreferencesCopyAppValue(key, application_id)) {
      if (CFBooleanGetTypeID() == CFGetTypeID(v)) {
        value = CFBooleanGetValue(static_cast<CFBooleanRef>(v));
      }
      CFRelease(v);
    }
    return value;
  }

  static boost::optional<float> get_float_property(CFStringRef _Nonnull key, CFStringRef _Nonnull application_id) {
    boost::optional<float> value = boost::none;
    if (auto v = CFPreferencesCopyAppValue(key, application_id)) {
      if (CFNumberGetTypeID() == CFGetTypeID(v)) {
        float vv;
        if (CFNumberGetValue(static_cast<CFNumberRef>(v), kCFNumberFloatType, &vv)) {
          value = vv;
        }
      }
      CFRelease(v);
    }
    return value;
  }

  /// "Use all F1, F2, etc. keys as standard function keys."
  static bool get_keyboard_fn_state(void) {
    if (auto value = system_preferences::get_bool_property(CFSTR("com.apple.keyboard.fnState"), CFSTR("Apple Global Domain"))) {
      return *value;
    }
    // default value
    return false;
  }

  static uint32_t get_standalone_key_milliseconds(void) {
    if (auto value = system_preferences::get_float_property(CFSTR("StandaloneKey"), CFSTR("Apple Global Domain"))) {
      return convert_key_repeat_system_preferences_value_to_milliseconds(*value);
    }
    // default value
    return 200;
  }

  static uint32_t convert_key_repeat_system_preferences_value_to_milliseconds(float value) {
    // The unit is 1/60 second.
    return static_cast<uint32_t>(round(value * 1000 / 60));
  }
};
