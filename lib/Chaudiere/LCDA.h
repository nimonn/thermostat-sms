#ifndef LCDA_H
#define LCDA_H

#include <Constantes.h>

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Timer.h>
#include <Etat.h>

class LCDA {
  private:
    LiquidCrystal_I2C lcd;
  	Timer timer;         // Fabrique de Timer
  	int timerEventLCD;   // Numero du Timer pour l'extinction de l'écran LCD
  	void (*callback)(void);

  public:
    LCDA(void (*callback)(void));
    ~LCDA();
    void printL1(String msg, int duration);
    void printL2(String msg, int duration);
    void printTemperature(Etat *etat, boolean etatSim, int duration);
    void printRelais(Etat *etat, int duration);
    void printPowerAlerte(int duration);
    void printPowerRestore(int duration);
	  void update();
	  void callbackLCD();

};

#endif
