
#ifndef TENSION_H
#define TENSION_H

#include <Constantes.h>

#include "Arduino.h"


class Tension {
  private:
    uint8_t _pin;
    unsigned long _lastReadTime;
    uint8_t _lastTension;

  public:
    Tension(uint8_t pin);
    void readData();
    float getTension();
    boolean isPowerOn();
  };


#endif
