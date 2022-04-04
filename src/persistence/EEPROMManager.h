#pragma once

#include "EEPROM.h"
#include "NetInfo.h"
//#include "EngineInfo.h"

namespace EEPROMManager{

    /*static void readEngineInfo(EngineInfo::info &info){

        EEPROM.begin(info.size);

        EEPROM.get(NetInfo::info::size, info);
    }

    static void writeEngineInfo(EngineInfo::info &info){

        EEPROM.begin(info.size);

        EEPROM.put(NetInfo::info::size, info);
        EEPROM.commit();
    }*/

    static void readWifiCredentials(NetInfo::info &info){

        EEPROM.begin(sizeof(info));

        EEPROM.get(0, info);
    }

    static void writeWifiCredentials(NetInfo::info &info){

        EEPROM.begin(sizeof(info));

        EEPROM.put(0, info);
        EEPROM.commit();
    }

}
