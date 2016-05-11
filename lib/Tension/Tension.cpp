

#include "Tension.h"


  Tension::Tension(uint8_t pin) : _pin(pin) {
  }

  void Tension::readData() {
    unsigned long currentTime = millis();
    if(currentTime - _lastReadTime > 2000) {
      _lastReadTime = currentTime;
      _lastTension = analogRead(_pin);
    }
  }

  float Tension::getTension() {
    return _lastTension * (5.0 / 1023.0);;
  }

  boolean Tension::isPowerOn() {
    return _lastTension>1; // Pour éviter les parasites
  }
