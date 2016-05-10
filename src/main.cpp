#include <Arduino.h>

#include <MemoryFree.h>

#include <SmsA.h>

#include <Etat.h>
#include <LCDA.h>
#include <Button.h>

#define PIN_IN_BUTTON_RELAIS 3   // Pin d'entrée du bouton relais
#define PIN_OUT_RELAIS       4   // Pin de sortie activer/desactiver le relais
#define PIN_IN_BUTTON_LCD    2   // Pin d'entrée du bouton ecran LCD
#define PIN_IN_ALERTE_LED    5   // Pin de sortie de la led indiquant une alerte
#define PIN_A_TEMPERATURE    A2  // Pin analogique d'entrée de la sonde de température/humidité
#define PIN_A_TENSION        A3  // Pin analogique d'entrée du détecteur de tension
// PIN 4 et 5 analogiques utilisées par l'écran LCD
// PIN 9 analogique utilisée par le shield GSM pour démarrage software
// PIN 0 et 1 utilisés par LCD ?


Etat *etat; // Gestion des états du système (température/humidité, relais, courant)
LCDA *lcda; // Gestion de l'écran LCD
SmsA smsa;  // Gestion des sms

uint8_t loopGsm = 0;

Button *buttonRelais; // Bouton relais
Button *buttonLcd;    // Bouton lcd

boolean alertMode = false;


/**
 * Callback pour extinction LCD
 */
void callbackLCD(){
  lcda->callbackLCD();
}

/**
 * Vérifie si un bouton est pressé.
 */
void checkButtons() {
  if (buttonRelais->isPressed()) {
    DEBUG_PRINTLN(F("buttonRelais->isPressed()"));
    etat->switchRelais();
    lcda->printRelais(etat, 5000);
    delay(200);

  } else if (buttonLcd->isPressed()) {
    DEBUG_PRINTLN(F("buttonLcd->isPressed()"));
    lcda->printTemperature(etat, smsa.isStarted(), 5000);
    delay(200);
  }
}

/**
 * Vérifie si une instruction via sms est reçu.
 */
void checkSmsInstruction() {
  if(smsa.isStarted()){
    //Read if there are unread messages on SIM card.
    String instr = smsa.getInstruction();
      DEBUG_PRINT(F("instr: "));
      DEBUG_PRINTLN(instr);

      if (instr.equalsIgnoreCase(F("etat"))) {
        smsa.sendSms(etat);
        delay(200);

      } else if (instr.equalsIgnoreCase(F("stop"))) {
        if (etat->getEtatRelais()) {
          etat->switchRelais();
          lcda->printRelais(etat, 5000);
          smsa.sendSms(F("Relais OFF"));
          delay(200);
        }
      } else if (instr.equalsIgnoreCase(F("start"))) {
        if (!etat->getEtatRelais()) {
          etat->switchRelais();
          lcda->printRelais(etat, 5000);
          smsa.sendSms(F("Relais ON"));
          delay(200);
        }
      }

    delay(200);
    Serial.println(F("-----------------------------------------------------------------"));
  }
}



/**
 * Vérifie si une coupure de courant est détectée.
 */
 void checkPower() {
  if (!etat->isPowerOn()) {
    // Activation mode alerte
    if (!alertMode) {
      DEBUG_PRINTLN(F("Coupure de courant"));
      alertMode = true;
      lcda->printPowerAlerte(5000);
      digitalWrite(PIN_IN_ALERTE_LED, HIGH);
      smsa.sendSms(F("Coupure de courant"));
    }
  } else {
    // Desactivation mode alerte
    if (alertMode) {
      DEBUG_PRINTLN(F("Courant retablit"));
      alertMode = false;
      lcda->printPowerRestore(5000);
      digitalWrite(PIN_IN_ALERTE_LED, LOW);
      smsa.sendSms(F("Courant retablit"));
    }
  }
}




void setup() {
  Serial.begin(9600); // start serial communication
  DEBUG_PRINTLN(F("Start..."));

  lcda = new LCDA(callbackLCD); // Créer la configuration du LCD
  lcda->printL1(F("Init LCD..."), 5000);
  lcda->printL2(F("LCD OK"), 5000);
  delay(1000);

  lcda->printL1(F("Init GSM..."), 5000);
  smsa.initGSM(9600);
  lcda->printL2(F("GSM OK"), 5000);
  delay(1000);

  pinMode(PIN_IN_ALERTE_LED, OUTPUT);
  digitalWrite(PIN_IN_ALERTE_LED, LOW);
  delay(500);

  buttonRelais = new Button(PIN_IN_BUTTON_RELAIS);
  buttonLcd    = new Button(PIN_IN_BUTTON_LCD);

  etat = new Etat(PIN_A_TEMPERATURE, PIN_A_TENSION, PIN_OUT_RELAIS);
  lcda->printL1(F("Fin de l'init"), 5000);
  DEBUG_PRINTLN(F("Started"));
}



void loop(){
  etat->update();
  lcda->update();

  checkPower();
  checkButtons();

  loopGsm++;
  if (loopGsm > 50) {
    checkSmsInstruction();
    loopGsm = 0;
    DEBUG_PRINT(F("freeMemory()="));
    DEBUG_PRINTLN(freeMemory());
  }


  delay(200);
}
