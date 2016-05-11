#ifndef CONSTANTES_H
#define CONSTANTES_H

//#define NO_SMS_SEND // Pas d'envoi de sms pour tests
#define DEBUG_ON    // LOG de trace pour tests

#ifdef DEBUG_ON
 #define DEBUG_PRINT(x)     Serial.print (x)
 #define DEBUG_PRINTDEC(x)  Serial.print (x, DEC)
 #define DEBUG_PRINTLN(x)   Serial.println (x)
#else
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINTDEC(x)
 #define DEBUG_PRINTLN(x)
#endif

#define ALERTE_DEBUT   F("Alerte: ")
#define ALERTE_FIN     F("Retour normal: ")
#define COURANT_ON     F("courant ON")
#define COURANT_OFF    F("courant OFF")

#define LCD_OUI        F("O")
#define LCD_NON        F("N")
#define LCD_RELAIS_ON  F("Relais ON")
#define LCD_RELAIS_OFF F("Relais OFF")
#define LCD_SEP        F("|")
#define LCD_ETAT       F("C|R|G")
#define LCD_TEMP_H     F("T: ")
#define LCD_TEMP_U     F("C")
#define LCD_HUMI_H     F("H: ")
#define LCD_HUMI_U     F("%")

#endif
