#include "SmsA.h"



SmsA::SmsA() : started(false) {
  phone_num[0]='\0';
  sms_text_in[0]='\0';
};


void SmsA::sendSms(Etat *etat) {
  snprintf(sms_text_out, sizeof sms_text_out,
        "T: %s H: %s\nRelais %s\nCourant %s",
         etat->getTemperatureStr(),
         etat->getHumiditeStr(),
         etat->getEtatRelais()?"actif":"inactif",
         etat->isPowerOn()?"ON":"OFF");

  DEBUG_PRINTLN(F("Envoie sms : "));
  DEBUG_PRINTLN(sms_text_out);

  #ifndef NO_SMS_SEND
    this->SendSMS(PHONE_NUMBER, sms_text_out);
  #endif
}


void SmsA::sendSms(String msg) {
  msg.toCharArray(sms_text_out, sizeof(sms_text_out));

  DEBUG_PRINTLN(F("Envoie sms : "));
  DEBUG_PRINTLN(sms_text_out);

  #ifndef NO_SMS_SEND
    this->SendSMS(PHONE_NUMBER, sms_text_out);
  #endif
}


boolean SmsA::authorized(char *phone_num_sms) {
  return (strstr(phone_num, PHONE_NUMBER));
}


void SmsA::initGSM(int baudrate) {
  DEBUG_PRINTLN(F("GSM Starting ...."));
  //Start configuration of shield with baudrate.
  if (gsm.begin(baudrate)){
    DEBUG_PRINTLN(F("GSM READY"));
    started=true;
  } else {
    DEBUG_PRINTLN(F("GSM IDLE"));
  }

  if(started){
    //Enable this two lines if you want to send an SMS.
    //if (sms.SendSMS("3471234567", "Arduino SMS"))
      //Serial.println("\nSMS sent OK");
  }
}


String SmsA::getInstruction() {
  String inst = "";
  // there is new SMS => read it
  if(started) {
    //Read if there are unread messages on SIM card.
    byte position = this->IsSMSPresent(SMS_UNREAD);
    delay(50);

    if (position > 0 && position <= 20) {
      char ret_val = this->GetSMS(position, phone_num, sms_text_in, 120);
      DEBUG_PRINT(F("Envoi du sms: "));
      DEBUG_PRINTLN(ret_val!=GETSMS_UNREAD_SMS?F("OK"):F("FAILED !!"));
      delay(50);
        DEBUG_PRINT(F("Sms recu : "));
        DEBUG_PRINT(F("position="));
        DEBUG_PRINT(position);
        DEBUG_PRINT(F(", de="));
        DEBUG_PRINT(phone_num);
        DEBUG_PRINT(F(", msg="));
        DEBUG_PRINTLN(sms_text_in);

      if (authorized(phone_num)) {
        inst = String(sms_text_in);
      }
      ret_val = this->DeleteSMS(position);
      DEBUG_PRINT(F("Retour suppression: "));
      DEBUG_PRINTLN(ret_val==1?F("OK"):F("FAILED !!"));

    }
    delay(200);
  }
  return inst;
}
