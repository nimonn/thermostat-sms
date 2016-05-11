#ifndef SMSA_H
#define SMSA_H

#include <Constantes.h>
#include <Phone.h>

#include <SoftwareSerial.h>
#include <Arduino.h>
#include <SIM900.h>
#include <Etat.h>
#include <sms.h>


class SmsA : public SMSGSM {
  public:
    SmsA();
    void initGSM(int baudrate);
    void sendSms(Etat *etat);
    void sendSms(String msg);
    String getInstruction();
    boolean isStarted();
  private:
    boolean started;// Le shield GSM est inactif

    char sms_text_out[120]; // Dernier SMS envoyé
    char phone_num[20];     // Dernier numéro du sms reçu
    char sms_text_in[100];  // Dernier SMS reçu

    boolean authorized(char* phone_num);
};

inline boolean SmsA::isStarted() { return started; }


#endif
