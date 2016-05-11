#ifndef RELAIS_H
#define RELAIS_H

#include <Constantes.h>

#include "Arduino.h"
#include <Button.h>


class Relais {
  private:
    uint8_t _pin;
    boolean _etat;

  public:
    Relais(uint8_t pin, boolean isNC);
    void switchEtat();
    boolean getEtat();
  };

inline Relais::Relais(uint8_t pin, boolean isNC) : _pin(pin), _etat(isNC) {
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, _etat?HIGH:LOW);
}

inline void Relais::switchEtat () {
  _etat=!_etat;
  digitalWrite(_pin, _etat?HIGH:LOW);
}
inline boolean Relais::getEtat() {
  return _etat;
}

#endif
