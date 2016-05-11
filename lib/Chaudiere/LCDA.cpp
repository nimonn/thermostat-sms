#include "LCDA.h"

LCDA::LCDA(void (*callb)(void)) : lcd(LiquidCrystal_I2C(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE)), timerEventLCD(0), callback (callb) {
  lcd.begin(16,2);    // initialize the lcd for 16 chars 2 lines, turn on backlight
}

void LCDA::printL1(String msg, int duration) {
  timer.stop(timerEventLCD);
  timerEventLCD = timer.after(duration, callback);
  lcd.setBacklight(HIGH);
  lcd.clear();
  lcd.home();
  lcd.print(msg);
}

void LCDA::printL2(String msg, int duration) {
  timer.stop(timerEventLCD);
  timerEventLCD = timer.after(duration, callback);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,1);
  lcd.print(msg);
}

void LCDA::printTemperature(Etat *etat, boolean etatSim, int duration) {
  timer.stop(timerEventLCD);
  timerEventLCD = timer.after(duration, callback);
  lcd.setBacklight(HIGH);
  lcd.clear();
  lcd.home();
  lcd.print(LCD_TEMP_H);
  lcd.print(etat->getTemperature());
  lcd.print(LCD_TEMP_U);
  lcd.setCursor(0,1);
  lcd.print(LCD_HUMI_H);
  lcd.print(etat->getHumidite());
  lcd.print(LCD_HUMI_U);
  lcd.setCursor(11,0);
  lcd.print(LCD_ETAT);
  lcd.setCursor(11,1);
  lcd.print(etat->isPowerOn()?LCD_OUI:LCD_NON);
  lcd.print(LCD_SEP);
  lcd.print(etat->getEtatRelais()?LCD_OUI:LCD_NON);
  lcd.print(LCD_SEP);
  lcd.print(etatSim?LCD_OUI:LCD_NON);
}


void LCDA::printRelais(Etat *etat, int duration) {
  timer.stop(timerEventLCD);
  timerEventLCD = timer.after(duration, callback);
  lcd.setBacklight(HIGH);
  lcd.clear();
  lcd.home();
  lcd.print(etat->getEtatRelais()?LCD_RELAIS_ON:LCD_RELAIS_OFF);
}


void LCDA::printPowerAlerte(int duration) {
  timer.stop(timerEventLCD);
  timerEventLCD = timer.after(duration, callback);
  lcd.setBacklight(HIGH);
  lcd.clear();
  lcd.home();
  lcd.print(ALERTE_DEBUT);
  lcd.setCursor(0,1);
  lcd.print(COURANT_OFF);
}

void LCDA::printPowerRestore(int duration) {
  timer.stop(timerEventLCD);
  timerEventLCD = timer.after(duration, callback);
  lcd.setBacklight(HIGH);
  lcd.clear();
  lcd.home();
  lcd.print(ALERTE_FIN);
  lcd.setCursor(0,1);
  lcd.print(COURANT_ON);
}

void LCDA::update() {
  timer.update();
}

void LCDA::callbackLCD(){
   lcd.setBacklight(LOW);
   lcd.clear();
   timer.stop(timerEventLCD);
}
