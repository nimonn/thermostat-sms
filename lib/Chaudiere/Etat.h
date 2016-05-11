#ifndef ETAT_H
#define ETAT_H

#include <Constantes.h>

#include <DHT22.h>
#include <Tension.h>
#include <Relais.h>
#include <Arduino.h>
#include <inttypes.h>

class Etat {
  private:
    DHT22 *dht22; // Temperature + humidité
    Tension *tension; // Détecteur de tension
    Relais *relais; // Le relais NC
  	char temperatureStr[7];
    char humiditeStr[7];

  public:
    Etat(uint8_t pinTemperature, uint8_t pinTension, uint8_t pinRelaisOut);
    ~Etat();
  	void update();
  	void switchRelais();

    float getTemperature();
  	float getHumidite();
  	char* getTemperatureStr();
  	char* getHumiditeStr();
  	boolean isPowerOn();
  	boolean getEtatRelais();
};

inline float Etat::getTemperature() {
	return float(dht22->getTemperatureCInt())/10;
}

inline float Etat::getHumidite() {
	return float(dht22->getHumidityInt())/10;
}

inline char* Etat::getTemperatureStr() {
	return temperatureStr;
}

inline char* Etat::getHumiditeStr() {
	return humiditeStr;
}

inline boolean Etat::isPowerOn() {
	return tension->isPowerOn();
}

inline boolean Etat::getEtatRelais() {
	return relais->getEtat();
}

inline void Etat::switchRelais() {
	relais->switchEtat();
}


#endif
