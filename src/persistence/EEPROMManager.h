#pragma once

#include "EEPROM.h"
#include "networking/NetInfo.h"

namespace EEPROMManager{
    
    static void writeWifiCredentials(NetInfo::info &info){

        EEPROM.begin(info.size);

        EEPROM.put(0, info);
        EEPROM.commit();
    }

    static void readWifiCredentials(NetInfo::info &info){

        EEPROM.begin(info.size);

        EEPROM.get(0, info);
    }

};