#include "Etat.h"

Etat::Etat(uint8_t pinTemperature, uint8_t pinTension, uint8_t pinRelaisOut) {
    dht22 = new DHT22(pinTemperature);
		tension = new Tension(pinTension);
		relais = new Relais(pinRelaisOut, true);
}

void Etat::update(){
	dht22->readData();
	tension->readData();

	dtostrf(getTemperature(),3, 1, temperatureStr);
	dtostrf(getHumidite(),3, 1, humiditeStr);
}
