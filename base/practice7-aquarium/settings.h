#pragma once

#include "utils.h"

class Settings final : private NonCopyable {
public:
  static const int FISH_COUNT_MIN = 1;
  static const int FISH_COUNT_DEFAULT = 10;
  static const int FISH_COUNT_MAX = 50;

  static const int SPEED_MIN = 50;
  static const int SPEED_DEFAULT = 200;
  static const int SPEED_MAX = 350;

private:
  int _fish_count { FISH_COUNT_DEFAULT };
  int _speed { SPEED_DEFAULT };

public:
  int fish_count() const noexcept {
    return _fish_count;
  }

  int speed() const noexcept {
    return _speed;
  }

  void set_fish_count(const int fish_count) {
    VALIDATE_RANGE(fish_count, FISH_COUNT_MIN, FISH_COUNT_MAX);

    _fish_count = fish_count;
  }

  void set_speed(const int speed) {
    VALIDATE_RANGE(speed, SPEED_MIN, SPEED_MAX);

    _speed = speed;
  }
};
