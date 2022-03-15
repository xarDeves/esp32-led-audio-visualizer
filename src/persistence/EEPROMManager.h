#pragma once

#include "EEPROM.h"

#define EEPROM_SIZE 128

//add comments
//refactor input params as struct for arbitary amount of data ?
namespace EEPROMManager{
    
    static void writeWifiCredentials(String ssid, String pass){

        if (!EEPROM.begin(EEPROM_SIZE)) {
            Serial.println("failed to init EEPROM");
            return;
        }

        int i = 2;
        int charCount = 0;

        int ssidLen = ssid.length() + 2;
        int passLen = pass.length();

        EEPROM.write(0, ssidLen);
        EEPROM.write(1, passLen);

        for (i; i < ssidLen; i++) {
            EEPROM.write(i, ssid[charCount]);
            charCount++;
        }
        charCount=0;
        for (i; i < passLen + ssidLen; i++) {
            EEPROM.write(i, pass[charCount]);
            charCount++;
        }

        EEPROM.commit();
    }

    static void readWifiCredentials(String &ssid, String &pass){

        Serial.println("-----------reading from EEPPROM-----------");
        
        if (!EEPROM.begin(EEPROM_SIZE)) {
            Serial.println("failed to init EEPROM");
            return;
        }

        int ssidLen = EEPROM.read(0);
        int passLen = EEPROM.read(1);

        int i = 2;

        for (i; i < ssidLen; i++) {
            ssid += (char)EEPROM.read(i);
        }
        Serial.println("-----------");
        for (i; i < passLen + ssidLen; i++) {
            pass += (char)EEPROM.read(i);
        }

        Serial.println(ssid);
        Serial.println(pass);

        Serial.println("-----------done reading from EEPPROM-----------");
    }

};