#pragma once

#include <FS.h>
#include <SPIFFS.h>
#include "NetInfo.h"
//#include "EngineInfo.h"

namespace EEPROMManager{

    static void readWifiCredentials(NetInfo::info &info){

        SPIFFS.begin(true);

        File file = SPIFFS.open("/netInfo.txt", "r");
        file.read((byte*)&info, sizeof(info));
        file.close();

        SPIFFS.end();
    }

    static void writeWifiCredentials(NetInfo::info info){

        SPIFFS.begin(true);

        File file = SPIFFS.open("/netInfo.txt", "w");
        file.write((byte*)&info, sizeof(info));
        file.close();

        SPIFFS.end();
    }
}
