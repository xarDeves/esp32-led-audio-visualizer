#pragma once

#include "EEPROM.h"
#include "networking/NetInfo.h"

#define EEPROM_SIZE 156

namespace EEPROMManager{
    
    static void writeWifiCredentials(NetInfo::info &info){

        if (!EEPROM.begin(EEPROM_SIZE)) {
            Serial.println("failed to init EEPROM");
            return;
        }

        EEPROM.put(0, info);
        EEPROM.commit();
    }

    static void readWifiCredentials(NetInfo::info &info){
        
        if (!EEPROM.begin(EEPROM_SIZE)) {
            Serial.println("failed to init EEPROM");
            return;
        }

        EEPROM.get(0, info);
    }

};